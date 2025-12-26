#include <Arduino.h>
#include "Melody.h"

class Sound {
  private:
    int pinBuz;

  public:
    void begin(int pin) {
      pinBuz = pin;
      pinMode(pinBuz, OUTPUT);
    }

    void buzz() {
      tone(pinBuz, 1000);
      delay(50);
      noTone(pinBuz);
    }

    void playStartup() {
      int melody[] = {
        NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, 
        NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,
        NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,
        NOTE_B4, 16,  NOTE_B5, 16,  NOTE_FS5, 16,   NOTE_DS5, 16,  NOTE_B5, 32,  
        NOTE_FS5, -16, NOTE_DS5, 8,  NOTE_DS5, 32, NOTE_E5, 32,  NOTE_F5, 32
      };

      int notes = sizeof(melody) / sizeof(melody[0]) / 2;
      int tempo = 105;
      int wholenote = (60000 * 4) / tempo;
      int divider = 0, noteDuration = 0;

      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
        divider = melody[thisNote + 1];
        if (divider > 0) {
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; 
        }

        tone(pinBuz, melody[thisNote], noteDuration * 0.9);
        delay(noteDuration);
        noTone(pinBuz);
      }
    }
};