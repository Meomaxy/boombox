#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int speaker = 8;
const int selectButton = 7;
const int playButton = 6;

int tempo = 80;
const int LETTER_TO_NOTE[] = {9, 11, 0, 2, 4, 5, 7};

unsigned int notes[7][12];

bool selectButtonDown = false;
bool playButtonDown = false;
int selectedSong = 0;

char* songList[][2] = {
  {"Mary Had a Little Lamb", 
       "T80 L4 O3 EDCDEEE2 DDD2 EGG2 EDCDEEEEDDEDC1"},
  {"Twinkle Twinkle", 
       "T50 L4 O3 CCGGAAG2 FFEEDDC2 GGFFEED2 GGFFEED2 CCGGAAG2 FFEEDDC2"},
  {"Minuet in G", 
       "T40 L4 O4 DL8O3GABO4CL4DO3GGO4EL8CDEF#L4GO3GG"
       "O4CL8DCO3BAB4O4CO3BAGF#4GABGBA2."
       "O4D4L8O3GABO4CL4DO3GGO4EL8CDEF#L4GO3GG"
       "O4C4L8DCO3BAB4O4CO3BAGA4BAGF#G2."},
  {"Imperial March",
   	   "T40L4O3 GGGE-8.B-16 GE-8.B-16G2 O4DDDE-8.O3B-16"
       "G-E-8.B-16G2 O4GO3G8.G16O4GG-8.F16 E16D#16E8P8O3G#8O4C#C8.O3B16"
       "B-16A16B-8P8E-8G-E-8.G-16 B-G8.B-16O4D2 O4GO3G8.G16O4GG-8.F16"
       "E16D#16E8P8O3G#8O4C#C8.O3B16 B-16A16B-8P8E-8G-E-8.B-16"
       "GE-8.B-16G2"},
};
const int numSongs = sizeof(songList) / sizeof(songList[0]);

void setup(){
  lcd.begin(16,2);
  pinMode(speaker, OUTPUT);
  pinMode(selectButton, INPUT);
  pinMode(playButton, INPUT);
  
  updateDisplay(selectedSong, false);
  
  // precompute note frequencies
  const double c3 = 261.63;
  const double semitone =  pow(2.0, 1.0/12.0);
  for (int octave = 0; octave < 7; octave++) {
    double f = c3 * pow(2.0, -3 + octave);
    for (int i=0; i<12; i++) {
      notes[octave][i] = (unsigned int)f;
      f *= semitone;
    }
  }
}

boolean isButtonPress(bool buttonDown, int pinNum) {
  if (buttonDown) {
    if(digitalRead(pinNum) == LOW ) {
      delay(50);  // debounce delay
      if(digitalRead(pinNum) == LOW) { 
        return false;
      }
    }
  } else {
    if(digitalRead(pinNum) == HIGH ) {
      delay(50);  // debounce delay
      if(digitalRead(pinNum) == HIGH) { 
        return true;
      }
    }
  }
  
  return buttonDown;
}
  
  
void loop() {
  bool oldSelectButtonDown = selectButtonDown;
  bool oldPlayButtonDown = playButtonDown;

  selectButtonDown = isButtonPress(selectButtonDown, selectButton);
  if (selectButtonDown && !oldSelectButtonDown) {
    playNote(100, 3, 0, 32, false);
    selectSong();
  }
  
  playButtonDown = isButtonPress(playButtonDown, playButton);
  if (playButtonDown && !oldPlayButtonDown) {
    updateDisplay(selectedSong, true);
    playSong(songList[selectedSong][1]);
    updateDisplay(selectedSong, false);
  }
}

void playNote(int tempo, int octave, int note, int duration, bool isDotted) {
  int noteDuration = (60000 / tempo) / duration;
  if (isDotted) {
    noteDuration = noteDuration * 3 / 2;
  }
  int toneDuration = noteDuration * 3 / 4;
  if (note >= 0) {
	  tone(speaker, notes[octave][note], toneDuration);
  }
  delay(noteDuration);
}

// Plays a song in the form of a string. The format of the string is based on the
// PLAY statement in IBM ADVANCED BASIC: 
//   https://archive.org/details/IBMBASICAV1.10Manual/page/n315/mode/2up
//
// Implements:
//   A to G with optional #, +, or -:
//       Plays the indicated note in the current octave. A number sign (#) 
//       or plus sign (+) afterwards indicates a sharp, a minus sign (-)
//       indicates a flat. The #, +, or - is not allowed unless it corresponds
//       to a black key on a piano. For example, B# is an invalid note.
//
//   O n: 
//       Octave. Sets the current octave for the following notes. There are
//       7 octaves, numbered 0 to 6. Each octave goes from C to B. Octave 3
//       starts with middle C. Octave 4 is the default octave.
//
//   L n:
//       Sets the length of the following notes. The actual note length is 1/n.
//       n may range from 1 to 64. The following table may help explain this:
//
//       Length   Equivalent
//         L1     whole note
//         L2     half note
//         L3     one of a triplet of three half notes (1/3 of a 4 beat measure)
//         L4     quarter note
//         L5     one of a quintuplet (1/5 of a measure)
//         L6     one of a quarter note triplet
//         .
//         .
//         .
//         L64    sixty-fourth note
//
//       The length may also follow the note when you want to change the length
//       only for the note. For example, A16 is equivalent to LIGA.
//
//   P n:
//       Pause (rest). n may range from 1 to 64, and figures the length of the 
//       pause in the same way as L (length).
//
//   (dot or period):
//       After a note, causes the note to be played as a dotted note. That is,
//       its length is multiplied by 3/2. Dots may also appear after a pause (P)
//       to scale the pause length in the same way.
//
//   T n:
//       Tempo. Sets the number of quarter notes in a minute. n may range from
//       32 to 255. The default is 120.
//
void playSong(char *songStr) {
  int tempo = 120;
  int length = 4;
  int octave = 4;
  int note = -1;
  
  char *p = songStr;
  while (*p != '\0') {
    // skip whitespace
    while (*p == ' ' || *p == ',') {
      ++p;
    }
    int nextLength = length;
    bool isDotted = false;
    char c = toupper(*p);
    switch (c) {
      case 'L':
        // set length
        ++p;  // skip the L
        length = (int)strtol(p, &p, 10);  // Set new length (allowed 1-64)
        nextLength = 0;  // No note to play
      	break;

      case 'O':
        // set octave
        ++p;  // skip the 0
        octave = (int)strtol(p, &p, 10);  // Set new octave (allowed 0-7)
        nextLength = 0;  // No note to play
      	break;

      case 'T':
        // set tempo
        ++p;  // skip the T
        tempo = (int)strtol(p, &p, 10);  // Set new tempo
        nextLength = 0;  // No note to play
      	break;
      
      case 'P':
        // Pause (i.e. rest)
        note = -1;
        ++p;  // skip the P
        // check for optional length
        if (isdigit(*p)) {
          nextLength = (int)strtol(p, &p, 10);
        }
        // check for optional dot
        if (*p == '.') {
          isDotted = true;
	      ++p;
        }
      	break;

      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case 'E':
      case 'F':
      case 'G':
      	note = LETTER_TO_NOTE[c - 'A'];
        ++p;  // skip the note
      	if ((*p == '#' || *p == '+') && note < 11) {
          // up half step for sharp. Ignore B#.
          note++;
          ++p;
      	} else if (*p == '-' && note > 0) {
          // up half step for flat. Ignore C flat.
          note--;
          ++p;
      	}
        // check for optional length
        if (isdigit(*p)) {
          nextLength = (int)strtol(p, &p, 10);
        }
        // check for optional dot
        if (*p == '.') {
          isDotted = true;
	      ++p;
        }
      	break;
      
      default:
        // should not happen, but just ignore next char if it does
        ++p;
        break;
    }
    if (nextLength > 0) {
      playNote(tempo, octave, note, nextLength, isDotted);
    }
  }
}

void updateDisplay(int songNum, bool isPlaying) {  
  static char buffer[17];  // static because screen flickers otherwise
  
  lcd.setCursor(0,0);
  if (isPlaying) {
    lcd.print("Playing song:");
  } else {
    lcd.print(" Select song:");
  }

  sprintf(buffer, "%16s", songList[songNum][0]);
  lcd.setCursor(0,1);
  lcd.print(buffer);
}

void selectSong() {
  selectedSong++;
  selectedSong %= numSongs;
  updateDisplay(selectedSong, false);
}

