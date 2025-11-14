#include <Arduino.h>
#include "buzzer_control.h"
#include "motor_control.h"

#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466   // ← ini yang bikin error tadi
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988


// Lagu 1: Selamat Ulang Tahun (versi agak panjang)
int melody1[] = {
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4,
  NOTE_C4, NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4
};
int durasi1[] = {
  300,300,600,600,600,900,
  300,300,600,600,600,900,
  300,300,600,600,600,600,900,
  300,300,600,600,600,1200
};

// Lagu 2: Do Re Mi Fa Sol La Si Do (naik-turun)
int melody2[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5,
  NOTE_B4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4
};
int durasi2[] = {
  400,400,400,400,400,400,400,600,
  400,400,400,400,400,400,800
};

// Variabel global
int *currentMelody = nullptr;
int *currentDurasi = nullptr;
int currentLen = 0;
int currentIndex = 0;
unsigned long lastNoteTime = 0;
bool playing = false;

void buzzerPlay(int songID) {
  if (songID == 1) {
    currentMelody = melody1;
    currentDurasi = durasi1;
    currentLen = sizeof(melody1) / sizeof(int);
  } else if (songID == 2) {
    currentMelody = melody2;
    currentDurasi = durasi2;
    currentLen = sizeof(melody2) / sizeof(int);
  } else {
    currentMelody = nullptr;
    return;
  }

  currentIndex = 0;
  playing = true;
  lastNoteTime = 0;
}

void buzzerStop() {
  noTone(BUZZER_PIN);
  playing = false;
}

// Dipanggil terus di loop utama
void buzzerLoop() {
  if (!playing || currentMelody == nullptr) return;

  unsigned long now = millis();
  if (now - lastNoteTime >= (unsigned long)(currentDurasi[currentIndex] * 1.3)) {
    currentIndex++;
    if (currentIndex >= currentLen) {
      buzzerStop();
      return;
    }
    tone(BUZZER_PIN, currentMelody[currentIndex], currentDurasi[currentIndex]);
    lastNoteTime = now;
  }
}
/*void playMelody(int *melody, int *durasi, int len) {
  for (int i = 0; i < len; i++) {
    tone(BUZZER_PIN, melody[i], durasi[i]);
    delay(durasi[i] * 1.3); // jeda antar nada
  }
  noTone(BUZZER_PIN);
}

void buzzerPlay(int songID) {
  if (songID == 1) {
    int len1 = sizeof(melody1) / sizeof(int);
    playMelody(melody1, durasi1, len1);
  } else if (songID == 2) {
    int len2 = sizeof(melody2) / sizeof(int);
    playMelody(melody2, durasi2, len2);
  }
}

void buzzerStop() {
  noTone(BUZZER_PIN);
}*/
