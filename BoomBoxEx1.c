#include "pitch.h"

#define speakerPIN 6
#define GameShowPIN 5
#define AnimatedSongPIN 3

void setup() {
  pinMode(GameShowPIN, INPUT);
  pinMode(AnimatedSongPIN, INPUT);
}

void loop() {
  GameShowSong();
  AnimatedSong();
}

void AnimatedSong() {
  int note[] = {
    C5, E5, G5, A5, G5, FS5, G5, E5, G5, A5, G5, FS5, G5, E5, G5, G5, E5, F5, F5, D5, C5, E5, G5,
    A5, G5, FS5, G5, E5, C6, G5, G5, E5, A5, G5, G5, G5, F5, D5, D5, D5, E5, 0, C5, E5, G5, 0,
    F5, E5, D5, C5, 0, C5, E5, G5, A5, F5, G5, E5, F5, D5, E5, C5, C6, C6, C6, B5, A5, A5, B5,
    C6, D6, E6, D6, C6, C5, D5, E5, F5, D5, E5, C5, D5, B4, C5, A4, C5, A4, B4, E4, C5, C5, B4,
    A4, B4, B4, C5, A4, B4, 0, B4, A4, C5, 0, B4, A4, B4, A4, B4, A4, D5, 0, C5, E5, G5, A5, G5,
    FS5, G5, E5, E5, G5, A5, G5, FS5, G5, E5, G5, F5, D5, D5, D5, E5, 0, C5, E5, G5, 0, F5, E5,
    D5, C5, 0, C5, E5, G5, A5, F5, G5, E5, F5, D5, E5, C5, C6, B5, C6, D6, E6, D6, C6, 0
  };
  int duration[] = {
    500, 500, 375, 125, 250, 250, 250, 250, 125, 125, 125, 125, 250, 250, 375, 125, 375, 250,
    250, 250, 500, 500, 375, 125, 250, 250, 250, 250, 125, 125, 125, 125, 125, 125, 250, 500,
    500, 250, 125, 125, 125, 125, 125, 125, 500, 125, 125, 125, 125, 125, 125, 125, 125, 63, 63,
    63, 63, 63, 63, 63, 63, 250, 250, 125, 63, 63, 250, 125, 125, 125, 125, 250, 250, 250, 125,
    125, 63, 63, 63, 63, 63, 63, 63, 63, 250, 125, 125, 250, 250, 125, 125, 125, 125, 250, 250,
    125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 500, 500,
    375, 125, 250, 250, 250, 125, 125, 125, 125, 125, 125, 250, 250, 500, 500, 250, 125, 125,
    125, 125, 125, 125, 500, 125, 125, 125, 125, 125, 125, 125, 125, 63, 63, 63, 63, 63, 63, 63,
    63, 250, 250, 125, 125, 125, 125, 250, 250, 250, 250
  };

  int AnimatedTotal = sizeof(note) / sizeof(note[0]);
  
  for (int i = 0; i < AnimatedTotal; i++) {
    if (digitalRead(GameShowPIN) == LOW) {
      GameShowSong;
    } else {
      tone(speakerPIN, note[i], duration[i]);
      delay(1.3 * duration[i]);
    }
  }
  delay(1000);
}

void GameShowSong() {
  int note[] = {
    CS5, CS5, 0, 0, DS5, 0, DS5, DS5, B4, B4, 0, 0, B4, 0, B4, DS5, CS5, CS5, 0, 0, DS5, 0, DS5,
    DS5, B4, B4, 0, 0, C4, C4, A4, A4, A4, A4, B4, B4, B4, G4, F4, G4, F4, C5, A4, F4, F4, A4, A4,
    A4, A4, B4, B4, B4, B4, GS4, FS4, GS4, FS4, GS4, 0, 0, FS4, AS4, AS4, AS4, AS4, B4, B4, B4,
    GS4, FS4, GS4, FS4, CS5, AS4, AS4, G4, FS4, 0, FS4, FS4, GS4, 0, GS4, 0, E2, E2, E2, E2, FS2,
    FS2, DS5, E5, F5, FS5, DS5, FS5, F5, D5, F5, E5, CS5, E5, DS5, E5, F5, FS5, DS5, FS5, GS5, F5,
    GS5, AS5, FS5, 1500, 1500, 1500, 0
  };
  int duration[] = {
    250, 125, 125, 63, 125, 63, 125, 125, 250, 125, 125, 63, 125, 63, 125, 125, 250, 125, 125, 63,
    125, 63, 125, 125, 250, 125, 125, 250, 125, 125, 125, 63, 125, 125, 313, 125, 125, 125, 125,
    125, 63, 125, 188, 125, 125, 63, 125, 125, 125, 125, 188, 125, 125, 125, 125, 125, 63, 188,
    125, 125, 125, 125, 125, 63, 125, 313, 125, 125, 63, 125, 125, 125, 125, 188, 125, 125, 125,
    125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 63, 63, 63, 188, 125, 125, 125, 188, 188,
    125, 188, 188, 125, 188, 188, 125, 188, 188, 125, 188, 188, 125, 188, 188, 125, 188, 188, 125,
    125, 125, 2000
  };

  int GameShowTotal = sizeof(note) / sizeof(note[0]);

  for (int i = 0; i < GameShowTotal; i++) {
    if (digitalRead(AnimatedSongPIN) == LOW) {
      AnimatedSong;
    } else {
      tone(speakerPIN, note[i], duration[i]);
      delay(1.3 * duration[i]);
    }
  }
  delay(1000);
}
