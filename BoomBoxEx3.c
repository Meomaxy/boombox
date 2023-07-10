//Comments refer to the line above 
#define speaker 8
#define playButton 6
#define selectionButton 7
//Sets speaker as pin 8, the play/pause button as pin 6, and the soong selection button as pin 7
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include "pitches.h"

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

boolean prevValueSelect = false;
int counter = 0;
int counter2 = 0;
boolean Update = true;
//Update allows us to not change the LCD every time there is a note 
int songToPlay = 1;

boolean prevPlayButton = false;
int songs[2] = {1, 2};
void setup() {
  // put your setup code here, to run once:

  pinMode(speaker, OUTPUT);
  pinMode(playButton, INPUT);
  pinMode(selectionButton, INPUT);
  //const int DDDDCLength1 = sizeof(DDDDCNotes) / sizeof(DDDDCNotes[0]);

  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Choose a Song");
  //creates an original message telling the user what to do 
  delay(1000);
}
void loop() {
  const int PROGMEM HTHNotes[] = {
      A2, A2, A2,
      REST, REST, FS2, FS2, G2,
      REST, REST, FS2, FS2, G2,
      REST, FS2, FS2, G2, REST, FS2, REST, A2,
      A2, REST, REST, REST, A2, A2, A2,
      REST, REST, FS2, FS2, G2,
      REST, REST, FS2, FS2, G2,
      REST, FS2, FS2, G2, REST, FS2, REST, A2,
      A2, REST, REST, REST, A2, A2, A2,
      REST, REST, FS2, FS2, G2,
      REST, REST, FS2, FS2, G2,
      REST, FS2, FS2, G2, REST, FS2, REST, A2,
      // first page of sheet music
      /*
        A2, REST, REST, REST, A2, A2, A2,
        REST, REST, FS2, FS2, G2,
        REST, REST, FS2, FS2, G2,
        REST, FS2, FS2, G2, REST, FS2, REST, A2,
        A2, REST, REST, REST, A2, A2, A2,
        REST, REST, FS2, FS2, G2,
        REST, REST, FS2, FS2, G2,
        REST, FS2, FS2, G2, REST, FS2, REST, A2,
        A2, REST, REST, REST, A2, A2, A2,
        REST, REST, FS2, FS2, G2,
        REST, REST, FS2, FS2, G2,
        //REST, FS2, FS2, G2, REST, FS2, REST, A2,
        //second page of sheet music
        
        /*E2, E2, E2, E2, E2, E2, E2,
        E2, E2, E2, E2, E2, E2, E2,
        A2, REST, A2, REST, A2, REST, A2, REST,
        A2, REST, A2, REST, G2, FS2,
        A2, REST, A2, REST, A2, REST, A2, REST,
        A2, REST, A2, REST, G2, FS2,
        A2, REST, A2, REST, A2, REST, A2, REST,
        A2, REST, A2, REST, G2, A2,
        //up to last line on third page
        A2, REST, A2, REST, A2, REST, A2, D2,
        D2,
        D2, REST, A2, A2, A2
      */
  };

  //Creates the array that holds each note in Highway to Hell
  const int PROGMEM HTHDurations[] = {8, 8, 8,
                                      2, 8, 8, 8, 8,
                                      2, 8, 8, 8, 8,
                                      8, 8, 8, 8, 8, 8, 8, 8,
                                      8, 8, 4, 8, 8, 8, 8,
                                      2, 8, 8, 8, 8,
                                      2, 8, 8, 8, 8,
                                      8, 8, 8, 8, 8, 8, 8, 8,
                                      8, 8, 4, 8, 8, 8, 8,
                                      2, 8, 8, 8, 8,
                                      2, 8, 8, 8, 8,
                                      8, 8, 8, 8, 8, 8, 8, 8,
                                      //first page of sheet music 
                                      /* 
                                        8, 8, 4, 8, 8, 8, 8, 
                                        2, 8, 8, 8, 8, 
                                        2, 8, 8, 8, 8, 
                                        8, 8, 8, 8, 8, 8 , 8 , 8, 
                                        8, 8, 4, 8, 8, 8, 8, 
                                        2, 8, 8, 8, 8, 
                                        2, 8, 8, 8, 8, 
                                        8, 8, 8, 8 , 8, 8, 8, 8, 
                                        8, 8, 4, 8, 8, 8, 8, 
                                        2, 8, 8, 8, 8, 
                                        2, 8, 8, 8, 8, 
                                        //8, 8, 8, 8, 8, 8, 8, 8, 
                                        //second page of sheet music 
                                        /*4, 8, 8, 8, 8, 8, 8, 
                                        8, 8, 8, 8, 8, 8, 4, 
                                        8, 8, 8, 8, 8, 8, 8, 8, 
                                        8, 8, 8, 8, 4, 4, 
                                        8, 8, 8, 8, 8, 8, 8, 8, 
                                        8, 8, 8, 8, 4, 4, 
                                        8, 8, 8, 8, 8, 8, 8, 8, 
                                        8, 8, 8, 8, 4, 4, 
                                        //up to last line of third page 
                                        8, 8, 8, 8, 8, 8, 8, 8, 
                                        1, 
                                        4, 8, 8, 8, 8 
                                      */
                                    };
// Creates the Array that contains the durations of each note in Highway to Hell
  const int PROGMEM DDDDCNotes[] = {E3, E3, G3,
                                    G3, E3, E3, A3,
                                    A3, E3, E3, D4,
                                    D4, E3, E3,
                                    E3, E3, G3,
                                    G3, E3, E3, A3,
                                    A3, E3, E3, D4,
                                    D4, E3, E3,
                                    E3, E3, G3,
                                    G3, E3, E3, A3,
                                    A3, E3, E3, D4,
                                    D4, E3, E3,
                                    E3, E3, G3,
                                    G3, E3, E3, A3,
                                    A3, E3, E3, D4,
                                    D4, E3, REST, G4, A4,
                                    // End of Repeat 1
                                    /*
                                      //Beginning of Repeat 2
                                      REST, A4, B4, A4, B4, A4, G4,
                                      A4, A4, B4, B4, REST,
                                      REST, E4, G4, G4, G4, G4, E4, G4,
                                      G4, REST, REST,
                                      REST, A4, A4, G4, A4, G4, A4, G4,
                                      A4, A4, G4, G4, B4, B4, REST,
                                      REST, G4, G4, E4, G4, E4, G4,
                                      G4, REST, REST,
                                      REST, A4, A4, G4, B4, REST, A4,
                                      A4, A4, A4, A4, B4, REST,
                                      REST, G4, G4, G4, G4, E4, G4,
                                      //end of first page
                                      REST, REST, G4, G4,
                                      REST, G4, G4, REST, G4, G4,
                                      REST, NOTE_, NOTE_, REST, NOTE_,
                                      REST, NOTE_, NOTE_, NOTE_, NOTE_, NOTE_,
                                      NOTE_, NOTE_,
                                      NOTE_, REST,
                                      NOTE_, NOTE_, NOTE_, NOTE_, REST,
                                      NOTE_, NOTE_, NOTE_, REST,
                                      NOTE_, NOTE_, NOTE_, NOTE_, REST,
                                      NOTE_, NOTE_, NOTE_, REST,
                                      NOTE_, NOTE_, NOTE_, NOTE_, REST,
                                      NOTE_, NOTE_, NOTE_, REST,
                                      NOTE_, NOTE_, NOTE_, NOTE_, NOTE_,
                                      NOTE_,
                                      NOTE_, NOTE_, NOTE_, REST,
                                      NOTE_, NOTE_, NOTE_, NOTE_, NOTE_,
                                      NOTE_,
                                      NOTE_, NOTE_, NOTE_, REST,
                                    */
                                  };
  // Creates the Array that contains the notes for Dirty Deeds Done Dirt Cheap
  const int PROGMEM DDDDCDurations[] = {2, 3, 4,
                                        4, 3, 3, 4,
                                        4, 3, 3, 4,
                                        4, 3, 2,
                                        2, 3, 4,
                                        4, 3, 3, 4,
                                        4, 3, 3, 4,
                                        4, 3, 2,
                                        2, 3, 4,
                                        4, 3, 3, 4,
                                        4, 3, 3, 4,
                                        4, 3, 2,
                                        2, 3, 4,
                                        4, 3, 3, 4,
                                        4, 3, 3, 4,
                                        8, 3, 8, 8, 4,
                                    /*
                                      4, 8, 8, 8, 8, 8, 8,
                                      8, 4, 8, 4, 4,
                                      8, 8, 8, 8, 8, 8, 8, 8,
                                      4, 4, 2,
                                      8, 8, 8, 8, 8, 8, 8, 8,
                                      8, 16, 16, 8, 8, 4, 4,
                                      8, 8, 8, 8, 8, 8, 4,
                                      4, 4, 2,
                                      8, 8, 8, 8, 4, 8, 8,
                                      8, 8, 16, 6, 4, 4,
                                      8, 8, 8, 8, 16, 6, 4,
                                      //end of page 1
                                      /*
                                        2, 8, 8, 4,
                                        8, 4, 8, 8, 4, 8,
                                        8, 4, 8, 8, 3,
                                        8, 8, 8, 8, 8, 8, 8, 8,
                                        2, 2,
                                        4, 8, 8, 4, 4,
                                        4, 4, 4, 4,
                                        4, 8, 8, 4, 4,
                                        4, 4, 4, 4,
                                        4, 8, 8, 4, 4,
                                        4, 4, 4, 4,
                                        4, 8, 8, 8, 4, 8,
                                        4, 4, 4, 4,
                                        4, 8, 8, 8, 4, 8,
                                        4, 4, 4, 4,
                                        2, 3, 4,
                                        4, 3, 3, 4,
                                        4, 3, 3, 4,
                                        4, 3, 2,
                                        2, 3, 4,
                                        4, 3, 3, 4,
                                        4, 3, 3, 4,
                                        4, 3, 2,
                                        2, 3, 4,
                                        4, 3, 3, 4,
                                        4, 3, 3, 4,
                                        4, 3, 2,
                                        2, 3, 4,
                                        4, 3, 3, 4,
                                        4, 3, 3, 4,
                                        4, 3, 2,
                                        2, 3, 4,
                                        4, 3, 3, 4,
                                        4, 3, 3, 4,
                                        8, 3, 8, 8, 4,
                                        */
                                      };
//Creates the Array the contains the durations of each notes in Dirty Deeds Done Dirt Cheap 

//Commented out sections of songs were commented out due to lack of memory
const int PROGMEM DDDDCLength = sizeof(DDDDCNotes) / sizeof(DDDDCNotes[0]);
const int PROGMEM HTHLength = sizeof(HTHNotes) / sizeof(HTHNotes[0]); //Finds the sizes of the two arrays 
int counter2 = 0;
// put your main code here, to run repeatedly: 
boolean selectionButtonState = digitalRead(selectionButton);
boolean playButtonState = digitalRead(playButton);
//Sets two variables to the states of the two buttons 
if (selectionButtonState && !prevValueSelect)
  //Uses Edge conditions to figure out whether or not to update the LCD 
{
  counter++;
  songToPlay = (counter % 2) + 1;
  Update = true;
}
prevValueSelect = selectionButtonState;
if (songToPlay == 1) {
  if (Update)
    //Only updates the LCD when a new song is to be played to prevent visible updates
  { 
    lcdDo(1);
    Update = !Update;
  }
  if (playButtonState)
  //Checks if the play button has been pressed 
  {
    //Serial.println(HTHLength); 
    for (int i = 0; i < HTHLength; i++)
    //Runs a for loop the amount of times as there are notes in HTHNotes 
    {
      prevPlayButton = playButtonState;
      playButtonState = digitalRead(playButton);
      int duration = 1000 / HTHDurations[i];
      int delay1 = duration + 100;
      note(8, HTHNotes[i], duration);
      //Runs our note function in order to play a note 
      delay(delay1);
      lcdDo(1);
      //Updates the LCD

      if (playButtonState and !prevPlayButton)
      //Edge conditions to make sure the user doesn't immediatly pause and then unpause the song 
      {
        counter2++;
        lcdDo(4);
        //Updates the LCD 
        while (counter2 % 2 == 1)
        //While loop Pauses the song 
        {
          prevPlayButton = playButtonState;
          playButtonState = digitalRead(playButton);
          if (playButtonState && !prevPlayButton) {
            counter2++;
            lcdDo(1);
            break;
            //Unpauses the song by leaving the while loop 
          }
        }
        prevPlayButton = playButtonState;
        playButtonState = digitalRead(playButton);
      }
    }
  }
} else if (songToPlay == 2) {
  if (Update)
    //Only updates the LCD when a new song is to be played to prevent visible updates
  { 
    lcdDo(2);
    Update = !Update;
  }
  if (playButtonState)
  //Checks if the play button has been pressed 
  {
    //Serial.println(DDDDCLength); 
    for (int i = 0; i < DDDDCLength; i++)
      //Runs a for loop the amount of times as there are notes in DDDDCNotes
    { 
      Serial.println(i);
      prevPlayButton = playButtonState;
      playButtonState = digitalRead(playButton);
      int duration = 1000 / DDDDCDurations[i];
      int delay1 = duration + 100;
      note(8, DDDDCNotes[i], duration);
      //Runs our note function in order to play a note 
      delay(delay1);
      lcdDo(2);
      //Updates the LCD 
      if (playButtonState and!prevPlayButton)
      //Edge conditions to make sure the user doesn't immediatly pause and then unpause the song 
      {
        counter2++;
        lcdDo(4);
        while (counter2 % 2 == 1)
        //While loop Pauses the song 
        {
          prevPlayButton = playButtonState;
          playButtonState = digitalRead(playButton);
          if (playButtonState && !prevPlayButton) {
            counter2++;
            lcdDo(1);
            break;
            //Unpauses the song by leaving the while loop 
          }
        }
        prevPlayButton = playButtonState;
        playButtonState = digitalRead(playButton);
      }
    }
  }
}
}
void note(int a, int b, int c)
//note playing function 
{
  tone(a, b, c);
}
void lcdDo(int x)
//LCD displaying functions 
{
  switch (x) {
  case 1:
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Highway To Hell");
    lcd.setCursor(0, 1);
    lcd.setCursor(0, 2);
    delay(50);
    break;
  case 2:
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Dirty Deeds Done");
    lcd.setCursor(0, 1);
    lcd.print("Dirt Cheap");
    lcd.setCursor(0, 2);
    delay(50);
    break;
  default:
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Paused");
    lcd.setCursor(0, 1);
    lcd.setCursor(0, 2);
    delay(30);
    break;
  }
}

More code:
#define REST 0
#define NOTE_ 0
#define B0 31
#define C1 33
#define CS1 35
#define D1 37
#define DS1 39
#define E1 41
#define F1 44
#define FS1 46
#define G1 49
#define GS1 52
#define A1 55
#define AS1 58
#define B1 62
#define C2 65
#define CS2 69
#define D2 73
#define DS2 78
#define E2 82
#define F2 87
#define FS2 93
#define G2 98
#define GS2 104
#define A2 110
#define AS2 117
#define B2 123
#define C3 131
#define CS3 139
#define D3 147
#define DS3 156
#define E3 165
#define F3 175
#define FS3 185
#define G3 196
#define GS3 208
#define A3 220
#define AS3 233
#define B3 247
#define C4 262
#define CS4 277
#define D4 294
#define DS4 311
#define E4 330
#define F4 349
#define FS4 370
#define G4 392
#define GS4 415
#define A4 440
#define AS4 466
#define B4 494
#define C5 523
#define CS5 554
#define D5 587
#define DS5 622
#define E5 659
#define F5 698
#define FS5 740
#define G5 784
#define GS5 831
#define A5 880
#define AS5 932
#define B5 988
#define C6 1047
#define CS6 1109
#define D6 1175
#define DS6 1245
#define E6 1319
#define F6 1397
#define FS6 1480
#define G6 1568
#define GS6 1661
#define A6 1760
#define AS6 1865
#define B6 1976
#define C7 2093
#define CS7 2217
#define D7 2349
#define DS7 2489
#define E7 2637
#define F7 2794
#define FS7 2960
#define G7 3136
#define GS7 3322
#define A7 3520
#define AS7 3729
#define B7 3951
#define C8 4186
#define CS8 4435
#define D8 4699
#define DS8 4978
