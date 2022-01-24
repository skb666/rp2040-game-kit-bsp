#ifndef LED_BSP_H
#define LED_BSP_H

#include <Arduino.h>

#define LED_PICO_PIN 4

class LED_PICO
{
private:
  pin_size_t pinNumber;
public:
  LED_PICO(pin_size_t pinNumber);
  void init();
  void on();
  void off();
  void toggle();
  void pwmOut(byte val);
};

extern LED_PICO LED_BSP;

#endif