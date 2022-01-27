#include "bsp/buzzer_bsp.h"

BUZZER_PICO Buzzer_BSP(BUZZER_PICO_PIN);

static TONE tones[115] = {
    {"C0", 16}, {"C#0", 17}, {"D0", 18}, {"D#0", 19}, {"E0", 21}, {"F0", 22}, {"F#0", 23},
    {"G0", 24}, {"G#0", 26}, {"A0", 28}, {"A#0", 29}, {"B0", 31}, {"C1", 33}, {"C#1", 35},
    {"D1", 37}, {"D#1", 39}, {"E1", 41}, {"F1", 44}, {"F#1", 46}, {"G1", 49}, {"G#1", 52},
    {"D2", 73}, {"D#2", 78}, {"E2", 82}, {"F2", 87}, {"F#2", 92}, {"G2", 98}, {"G#2", 104},
    {"A2", 110}, {"A#2", 117}, {"B2", 123}, {"C3", 131}, {"C#3", 139}, {"D3", 147}, {"D#3", 156},
    {"E3", 165}, {"F3", 175}, {"F#3", 185}, {"G3", 196}, {"G#3", 208}, {"A3", 220}, {"A#3", 233},
    {"B3", 247}, {"C4", 262}, {"C#4", 277}, {"D4", 294}, {"D#4", 311}, {"E4", 330}, {"F4", 349},
    {"F#4", 370}, {"G4", 392}, {"G#4", 415}, {"A4", 440}, {"A#4", 466}, {"B4", 494}, {"C5", 523},
    {"C#5", 554}, {"D5", 587}, {"D#5", 622}, {"E5", 659}, {"F5", 698}, {"F#5", 740}, {"G5", 784},
    {"G#5", 831}, {"A5", 880}, {"A#5", 932}, {"B5", 988}, {"C6", 1047}, {"C#6", 1109}, {"D6", 1175},
    {"D#6", 1245}, {"E6", 1319}, {"F6", 1397}, {"F#6", 1480}, {"G6", 1568}, {"G#6", 1661}, {"A6", 1760},
    {"A#6", 1865}, {"B6", 1976}, {"C7", 2093}, {"C#7", 2217}, {"D7", 2349}, {"D#7", 2489}, {"E7", 2637},
    {"F7", 2794}, {"F#7", 2960}, {"G7", 3136}, {"G#7", 3322}, {"A7", 3520}, {"A#7", 3729}, {"B7", 3951},
    {"C8", 4186}, {"C#8", 4435}, {"D8", 4699}, {"D#8", 4978}, {"E8", 5274}, {"F8", 5588}, {"F#8", 5920},
    {"G8", 6272}, {"G#8", 6645}, {"A8", 7040}, {"A#8", 7459}, {"B8", 7902}, {"C9", 8372}, {"C#9", 8870},
    {"D9", 9397}, {"D#9", 9956}, {"E9", 10548}, {"F9", 11175}, {"F#9", 11840}, {"G9", 12544}, {"G#9", 13290},
    {"A9", 14080}, {"A#9", 14917}, {"B9", 15804}
};

BUZZER_PICO::BUZZER_PICO(pin_size_t pinNumber) 
{
  this->pinNumber = pinNumber;
}

void BUZZER_PICO::init(const char *song)
{
  pinMode(this->pinNumber, OUTPUT);
  this->paused = 1;
  if(song) {
    this->stopped = 0;
    this->setSong(song);
  } else {
    this->stopped = 1;
  }
}

void BUZZER_PICO::playNote(const char *note) {
  static int lastnote = 0;
  int freq = 0;
  if(!strcmp(note, "#")) {
    freq = 0;
  } else {
    for(int i=0; i<115; ++i) {
      if(!strcmp(note, tones[i].note)) {
        freq = tones[i].freq;
        break;
      }
    }
  }
  if(freq != lastnote) {
    lastnote = freq;
    tone(this->pinNumber, freq);
  }
}

void BUZZER_PICO::setSong(const char *song)
{
  this->song = song;
  this->p = this->song;
  this->stopped = 0;
}

void BUZZER_PICO::play(int tempo, uint8_t looping, const char *song)
{
  static unsigned long music_tick = millis();
  char note[4];

  if(song && strcmp(song, this->song)) {
    this->setSong(song);
  }

  if(this->paused) {
    return;
  }

  if(millis() - music_tick >= tempo) {
    if(this->p && *(this->p)) {
      sscanf(this->p, "%[^,]", note);
      this->playNote(note);
      this->p = strchr(this->p, ',');
      if(this->p) {
        ++(this->p);
      } else {
        if(looping) {
          this->p = this->song;
        } else {
          this->stopped = 1;
          noTone(this->pinNumber);
        }
      }
    } else {
      if(looping) {
        this->p = this->song;
      } else {
        this->stopped = 1;
        noTone(this->pinNumber);
      }
    }
    music_tick = millis();
  }
}

uint8_t BUZZER_PICO::isStop()
{
  return this->stopped;
}

uint8_t BUZZER_PICO::pause()
{
  if(!this->paused) {
    this->paused = 1;
    this->playNote("#");
    return 0;
  } else {
    this->paused = 0;
    return 1;
  }
}
