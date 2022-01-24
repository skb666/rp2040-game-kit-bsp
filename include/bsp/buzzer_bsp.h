#ifndef BUZZER_BSP_H
#define BUZZER_BSP_H

#include <Arduino.h>

#define BUZZER_PICO_PIN 23

typedef struct {
    char note[4];
    int freq;
} TONE;

class BUZZER_PICO
{
private:
  pin_size_t pinNumber;
  const char *song = NULL;
  const char *p;
  uint8_t stopped, paused;
public:
  BUZZER_PICO(pin_size_t pinNumber);
  void init(const char *song=NULL);
  void playNote(const char *note);
  void setSong(const char *song);
  void play(int tempo=300, uint8_t looping=0, const char *song=NULL);
  uint8_t isStop();
  uint8_t pause();
};

extern BUZZER_PICO Buzzer_BSP;

#endif