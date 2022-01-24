#include "bsp/buttons_bsp.h"

BUTTON_PICO ButtonA_BSP(BTN_A_PICO_PIN),
            ButtonB_BSP(BTN_B_PICO_PIN),
            ButtonStart_BSP(BTN_START_PICO_PIN),
            ButtonSelect_BSP(BTN_SELECT_PICO_PIN);

static BUTTON_PICO *buttons[4] = {&ButtonA_BSP, &ButtonB_BSP, &ButtonSelect_BSP, &ButtonStart_BSP};
BUTTONS_PICO Buttons_BSP(buttons, 4);

BUTTON_PICO::BUTTON_PICO(pin_size_t pinNumber)
{
  this->pinNumber = pinNumber;
  this->checkState = _CK_CHECK;
}

void BUTTON_PICO::init()
{
  pinMode(this->pinNumber, INPUT_PULLUP);
}

void BUTTON_PICO::scan(uint8_t timeout)
{
  static unsigned long check_time = millis();

  if(millis() - check_time >= timeout) {
    switch(this->checkState) {
      case _CK_CHECK: {
        if(digitalRead(this->pinNumber) == LOW) {
          this->checkState = _CK_COMFIRM;
        }
      } break;
      case _CK_COMFIRM: {
        if(digitalRead(this->pinNumber) == LOW) {
          this->checkState = _CK_RELEASE;
          // buttonState = BUTTON_PRESSED
          if(this->callback_pressed != NULL) {
            this->callback_pressed();
          }
        } else {
          this->checkState = _CK_CHECK;
        }
      } break;
      case _CK_RELEASE: {
        if(digitalRead(this->pinNumber) == HIGH) {
          this->checkState = _CK_CHECK;
          // buttonState = BUTTON_RELEASE
          if(this->callback_release != NULL) {
            this->callback_release();
          }
        }
      } break;
    }
    check_time = millis();
  }
}

BUTTON_STATE BUTTON_PICO::getState()
{
  if(_CK_COMFIRM == this->checkState) {
    return BUTTON_PRESSED;
  } else {
    return BUTTON_RELEASE;
  }
}

void BUTTON_PICO::setCallback(void (*callback_pressed)(), void (*callback_release)())
{
  this->callback_pressed = callback_pressed;
  this->callback_release = callback_release;
}

BUTTONS_PICO::BUTTONS_PICO(BUTTON_PICO **buttons, uint8_t buttons_num)
{
  this->buttons = buttons;
  this->buttons_num = buttons_num;
}

void BUTTONS_PICO::init()
{
  for(int i=0; i<this->buttons_num; ++i) {
    this->buttons[i]->init();
  }
}

void BUTTONS_PICO::scan(uint8_t timeout)
{
  static unsigned long check_time = millis();

  if(millis() - check_time >= timeout) {
    for(int i=0; i<this->buttons_num; ++i) {
      this->buttons[i]->scan(0);
    }
    check_time = millis();
  }
}

BUTTON_STATE BUTTONS_PICO::getState(pin_size_t pinNumber)
{
  for(int i=0; i<this->buttons_num; ++i) {
    if(pinNumber == this->buttons[i]->pinNumber) {
      return this->buttons[i]->getState();
    }
  }
}

void BUTTONS_PICO::setCallback(pin_size_t pinNumber, void (*callback_pressed)(), void (*callback_release)())
{
  for(int i=0; i<this->buttons_num; ++i) {
    if(pinNumber == this->buttons[i]->pinNumber) {
      this->buttons[i]->setCallback(callback_pressed, callback_release);
      break;
    }
  }
}
