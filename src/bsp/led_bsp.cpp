#include "bsp/led_bsp.h"

LED_PICO LED_BSP(LED_PICO_PIN);

LED_PICO::LED_PICO(pin_size_t pinNumber)
{
  this->pinNumber = pinNumber;
}

void LED_PICO::init()
{
  pinMode(this->pinNumber, GPIO_OUT);
}

void LED_PICO::on()
{
  digitalWrite(this->pinNumber, 1);
}

void LED_PICO::off()
{
  digitalWrite(this->pinNumber, 0);
}

void LED_PICO::toggle()
{
  digitalWrite(this->pinNumber, !digitalRead(this->pinNumber));
}

void LED_PICO::pwmOut(byte val)
{
  analogWrite(this->pinNumber, val);
}
