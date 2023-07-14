#include "pitches.h"; //so I can put the note into the array rather than the frequency
#include <LiquidCrystal_I2C.h> //LCD
#include <Wire.h> //LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //LCD 

//The notes for the Gamecube start up song
int GCmelody[] = {
  NOTE_FS3, NOTE_CS4, NOTE_E4, NOTE_A4, NOTE_D5, NOTE_A4, NOTE_CS5, NOTE_GS4, NOTE_DS4, NOTE_G4,
  NOTE_FS4, NOTE_CS4, NOTE_E3, NOTE_C4, NOTE_D4, NOTE_G4, NOTE_E5, NOTE_F5, NOTE_AS5, NOTE_F5,
  NOTE_C5, NOTE_A5, NOTE_E5, NOTE_B4, NOTE_B4
};

//The length of the notes for the Gamecube start up song 
int GCnoteduration[] = {
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  2,
};

//The notes for Luigi's Mansion 
int LMmelody[] = {
  0, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, 0, NOTE_C4, NOTE_E4, NOTE_E4, 0, NOTE_B3, 0, 0, 0,
  NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, 0, NOTE_B3, NOTE_D4, 0, NOTE_C4, 0, NOTE_B4, NOTE_AS4, 0,
  NOTE_E3, 0, 0, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_G4, NOTE_E4, 0, NOTE_C4, NOTE_E4, NOTE_FS4,
  NOTE_E4, 0, NOTE_B3, 0, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_F4, NOTE_D4, 0,
  NOTE_C4, NOTE_D4, 0, NOTE_E4, NOTE_D4, 0, NOTE_C4, NOTE_B3, 0, NOTE_A3, 0, 
};

//The length of the notes for Luigi's Mansion 
int LMnoteduration[] = {
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 2, 8, 8, 8, 8, 8, 8, 8, 8, 16, 8, 4, 4, 4, 8, 8, 8, 8, 8, 8,
  8, 2, 8, 8, 8, 8, 2, 8, 8, 8, 8, 2, 2, 8, 8, 8, 2, 8, 8, 8, 8, 16, 8, 16, 16, 8, 16, 16, 8, 4,
};

//The Deflino Plaza notes
int SMSmelody[] = {
  NOTE_B3, NOTE_D4, NOTE_B3, NOTE_G3, NOTE_F3, NOTE_F3, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G3,
  NOTE_E3, NOTE_E3, NOTE_E3, NOTE_G3, NOTE_G3, NOTE_F3, NOTE_F3, NOTE_F3, NOTE_F3, NOTE_E3,
  NOTE_E3, NOTE_G3, NOTE_G3, NOTE_F3, NOTE_F3, NOTE_F3, NOTE_F3, NOTE_E3, NOTE_E3, NOTE_G3,
  NOTE_G3, NOTE_F3, NOTE_F3, NOTE_F3, NOTE_F3, NOTE_E3, NOTE_E3, NOTE_G3, NOTE_G3, NOTE_F3,
  NOTE_F3, NOTE_F3, NOTE_F3, 0, NOTE_F3, NOTE_C4, NOTE_C4, NOTE_E3, NOTE_D3, NOTE_B3, NOTE_B3, 0,
  NOTE_E3, NOTE_C4, NOTE_C4, NOTE_E3, NOTE_D3, NOTE_B3, NOTE_B3, 0, NOTE_E3, NOTE_C4, NOTE_C4,
  NOTE_C4, NOTE_D4, NOTE_F3, NOTE_F3, 0, NOTE_F3, 0, NOTE_G3, 0, 0, NOTE_F3, NOTE_C4, NOTE_C4,
  NOTE_E3, NOTE_D3, NOTE_B3, NOTE_B3, 0, NOTE_E3, NOTE_C4, NOTE_C4, NOTE_E3, NOTE_D3, NOTE_B3,
  NOTE_B3, 0, NOTE_E3, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_F3, NOTE_F3, 0, NOTE_F3, 0,
  NOTE_G3, 0, NOTE_F3, NOTE_C4, NOTE_F3, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, 0, NOTE_D4,
  NOTE_F3, NOTE_D4, NOTE_F3, NOTE_A3, NOTE_F3, NOTE_A3, NOTE_F3, NOTE_A3, NOTE_F3, NOTE_A3, 
  NOTE_B3, NOTE_D4, NOTE_B3, NOTE_D4, NOTE_B3, NOTE_D4, NOTE_B3, NOTE_D4, NOTE_F3, NOTE_A3,
  NOTE_F3, NOTE_A3, NOTE_F3, NOTE_A3, NOTE_F3, NOTE_A3
};

//the duration of the notes for delfino plaza 
int SMSnoteduration[] = {
  8, 8, 8, 8, 8, 8, 8, 8, 8, 2, 4, 
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
  8, 8, 4, 4, 4, 4, 4, 2, 8, 8, 4, 4, 4, 4, 8, 2, 8, 8, 4, 4, 4, 4, 8, 8, 8, 8, 8, 1, 2, 8, 8, 4, 4, 4, 4, 4, 2, 8, 8, 4, 4, 4, 4, 8, 2, 8, 8, 4, 4, 4, 4, 8, 8, 8, 8, 8, 1, 2, 4, 4, 4, 4, 4, 4, 4, 4, 
  4, 2, 2, 2, 
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
};

//int's to simplify code. This way it is easier to read over 
int buttonState8 = digitalRead(8);
int buttonState9 = digitalRead(9);
int buttonState10 = digitalRead(10);
void setup() {
  //the 3 buttons 
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  //the two speakers 
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  //intaliziing the lcd screen and serial monitor 
  lcd.begin(16, 2);
  Serial.begin(9600);

  //When the GameCube turns on the LCD prints "Welcome to GameCube Jukebox" and it plays the Gamecube start up song 
  for (int x = 0; x < 25; x++) {
    lcd.clear();
    lcd.print(" Welcome to");
    lcd.setCursor(0, 1);
    lcd.print("GameCube Jukebox");
    int duration = 500 / GCnoteduration[x];
    tone(4, GCmelody[x], duration);
    delay(duration + 125);
    noTone(4);
    lcd.clear();
  }
  //the lcd code that shows which button plays which song (it looks like it scrolls down) lcd.print("1.GameCube"); 
  lcd.setCursor(0, 1);
  lcd.print("2.Delfino Plaza");
  delay(3500);
  lcd.clear();
  lcd.print("2.Delfino Plaza");
  lcd.setCursor(0, 1);
  lcd.print("3.Luigis Mansion");
  delay(3500);
  lcd.clear();
  lcd.print("3.Luigis Mansion");
  delay(2750);
  lcd.clear();
}
void loop() {
  //When ever a song is not playing this is shown on the screen 
  lcd.setCursor(0, 0); //Need this because otherwise it won't print correctly (Please select overlaps with a song) 
  lcd.print("Please Select");
  lcd.setCursor(0, 1);
  lcd.print(" a Song");

  //if button 1 is pressed it plays the gamecube start up song and prints GameCube on the lcd
  if (digitalRead(10) == HIGH) { 
    for (int x = 0; x < 25; x++) {
      lcd.clear();
      lcd.print(" Gamecube");
      int duration = 500 / GCnoteduration[x];
      tone(4, GCmelody[x], duration);
      if (digitalRead(10) == HIGH) {
        noTone(4);
      }
      delay(duration + 125);
      noTone(4);
    }
  }
  noTone(4); //Had a problem with the speakers turning on when the button is not pressed so this prevents that 

  //if button 2 is pressed it plays Delfino Plaza and prints Delfino Plaza on the lcd
  if (digitalRead(9) == HIGH) { 
    for (int x = 0; x < 67; x++) {
      lcd.clear();
      lcd.print(" Delfino Plaza");
      int duration = 500 / SMSnoteduration[x];
      tone(4, SMSmelody[x], duration);
      delay(duration + 125);
      noTone(4);
    }
  }
  noTone(4); //Prevents same problem as before
  //When button 3 is pressed it plays Luigi's Mansion and prints Luigi's Mansion on the LCD 
  if (digitalRead(8) == HIGH) {
    for (int x = 0; x < 54; x++) {
      lcd.clear();
      lcd.print("Luligi's Mansion");
      int duration = 500 / LMnoteduration[x];
      tone(4, LMmelody[x], duration);
      delay(duration + 125);
      noTone(4);
    }
  }
}
