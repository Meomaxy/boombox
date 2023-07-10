#define REST 0
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define  NOTE_C3  131
#define  NOTE_CS3 139
#define  NOTE_D3  147
#define  NOTE_DS3 156
#define  NOTE_E3  165
#define  NOTE_F3  175
#define  NOTE_FS3 185
#define  NOTE_G3  196
#define  NOTE_GS3 208
#define  NOTE_A3  220
#define  NOTE_AS3 233
#define  NOTE_B3  247
#define  NOTE_C4  262
#define  NOTE_CS4 277
#define  NOTE_D4  294
#define  NOTE_DS4 311
#define  NOTE_E4  330
#define  NOTE_F4  349
#define  NOTE_FS4 370
#define  NOTE_G4  392
#define  NOTE_GS4 415
#define  NOTE_A4  440
#define  NOTE_AS4 466
#define  NOTE_B4  494
#define  NOTE_C5  523
#define  NOTE_CS5 554
#define  NOTE_D5  587
#define  NOTE_DS5 622
#define  NOTE_E5  659
#define  NOTE_F5  698
#define  NOTE_FS5 740
#define  NOTE_G5  784
#define  NOTE_GS5 831
#define  NOTE_A5  880
#define  NOTE_AS5 932
#define  NOTE_B5  988
#define  NOTE_C6  1047
#define  NOTE_CS6 1109

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int speaker = 8;
int selectButton = 7;
int playButton = 6;
bool selection = false;



void setup(){
 lcd.begin(16,2);
 pinMode(speaker, OUTPUT);
 pinMode(selectButton, INPUT);
 pinMode(playButton, INPUT);
  
  lcd.setCursor(0,0);
  lcd.print("Please select");
  lcd.setCursor(0,1);
  lcd.print("a song to play");
}
  
  
void loop(){
  
  //select button switches between happy and angry songs
  //displays your selection on the LCD screen
  if(digitalRead(selectButton) == HIGH){
    selectSong();
    delay(50);
  }
  
  //play button checks what song is selected and then plays the correct subroutine
  if(digitalRead(playButton) == HIGH){
    if(selection == true){
	  playAngry();
    }
    else{
      playHappy();
    }
  }
}
     

void selectSong(){
if(selection == false){
 selection = true;
 lcd.setCursor(0,0);
 lcd.print("   happy        ");
 lcd.setCursor(0,1);
 lcd.print("-> angry      ");
}
else{
  selection = false;
  lcd.setCursor(0,0);
  lcd.print("-> happy        ");
  lcd.setCursor(0,1);
  lcd.print("   angry      ");
}
}

void playHappy(){
  int happyNotes[] = {
    NOTE_C4, NOTE_F4, NOTE_F4,NOTE_F4,NOTE_C4,NOTE_C4,NOTE_C4,NOTE_DS4,NOTE_DS4,NOTE_F4,    //It might seem crazy what I'm 'bout to say
    NOTE_F3,NOTE_GS3, NOTE_AS3,NOTE_GS3,NOTE_C4,NOTE_AS3,NOTE_GS3,NOTE_AS3,NOTE_GS3,NOTE_F3,  //Bass riff
    NOTE_GS4,NOTE_GS4,NOTE_GS4,NOTE_GS4,NOTE_C4,NOTE_C4,NOTE_DS4,NOTE_DS4,NOTE_F4,        //Sunshine is here, you can take a break
    NOTE_F3,NOTE_GS3, NOTE_AS3,NOTE_GS3,NOTE_C4,NOTE_AS3,NOTE_GS3,NOTE_AS3,NOTE_GS3,NOTE_F3,  //Bass riff
    NOTE_F4, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_DS4,NOTE_DS4,NOTE_DS4,NOTE_DS4,NOTE_F4,      //Hot air balloon, that can go to space 
    NOTE_F3,NOTE_GS3, NOTE_AS3,NOTE_GS3,NOTE_C4,NOTE_AS3,NOTE_GS3,NOTE_AS3,   //Bass riff
    NOTE_DS4,NOTE_DS4,NOTE_DS4,NOTE_D4, NOTE_DS4, NOTE_D4, NOTE_C4, NOTE_AS3, NOTE_C4, NOTE_C4,NOTE_AS3, NOTE_GS3,NOTE_F3, //with the air...
    NOTE_GS2, NOTE_AS2, NOTE_GS2,NOTE_C3 //Bass into Chorus 
};

float happyDurations[] = {
  8, 8, 4, 4, 8, 8, 8, 8, 8, 4,
  4, 4, 4, 8, 4, 4, 8, 4, 4, 4,
  8, 4, 4, 8/3, 8, 8, 8, 8, 4,
  4, 4, 4, 8, 4, 4, 8, 4, 4, 4,
  4, 4, 8, 8/3, 8, 8, 8, 8, 4, 
  4, 4, 4, 8, 4, 4, 8, 4,
  8, 8, 8/3, 8, 8, 8, 8/3, 8, 8, 8, 8, 8, 4,
  4, 4, 8, 8
};
  for (int i = 0; i < 73; i++) {
       float noteDuration = 1000 / happyDurations[i];
    	tone(speaker, happyNotes[i], noteDuration);
        float pauseBetweenNotes = 1.3 * noteDuration;
        delay(pauseBetweenNotes);
        }
} 

void playAngry(){
int angryNotes[] = {
  NOTE_C3, NOTE_C4, NOTE_A3, NOTE_A4, NOTE_AS3, NOTE_AS4,0,0,0,
  NOTE_C3, NOTE_C4, NOTE_A3, NOTE_A4, NOTE_AS3, NOTE_AS4,0,0,0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4, NOTE_DS3, NOTE_DS4,0,0,0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4, NOTE_DS3, NOTE_DS4,0,0,
  NOTE_DS3, NOTE_D3, NOTE_CS3, NOTE_C3, NOTE_DS3, NOTE_D3, NOTE_GS2,NOTE_G2, NOTE_CS3,
  NOTE_C3, NOTE_FS3, NOTE_F3, NOTE_E3, NOTE_AS3,NOTE_A3, 
  NOTE_GS3,NOTE_DS3, NOTE_B2, NOTE_AS2, NOTE_A2, NOTE_GS2 
};

float angryDurations[] = {
  4, 4, 4, 4, 4, 4, 2, 2, 2,
  4, 4, 4, 4, 4, 4, 2, 2, 2,
  4, 4, 4, 4, 4, 4, 2, 2, 2,
  4, 4, 4, 4, 4, 4, 2, 2,
  6, 6, 6, 2, 2, 2, 2, 2, 2, 
  6, 6, 6, 6, 6, 6,
  3, 3, 3, 3, 3, 3 
};
  
  for (int i = 0; i < 56; i++) {
      float noteDuration = 450 / angryDurations[i];
      tone(speaker, angryNotes[i], noteDuration);
      float pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
	  }
}
