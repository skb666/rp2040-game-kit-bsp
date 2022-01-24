#ifndef BUTTON_BSP_H
#define BUTTON_BSP_H

#include <Arduino.h>

#define BTN_A_PICO_PIN      6
#define BTN_B_PICO_PIN      5
#define BTN_START_PICO_PIN  7
#define BTN_SELECT_PICO_PIN 8

typedef enum
{
  _CK_CHECK = 0,
  _CK_COMFIRM,
  _CK_RELEASE
} CHECK_STATE;

typedef enum
{
  BUTTON_RELEASE = 0,
  BUTTON_PRESSED,
  BUTTON_NONE
} BUTTON_STATE;

typedef struct {
  pin_size_t pinNumber;
  BUTTON_STATE state;
} BTN_EVEN;

class BUTTON_PICO
{
private:
  pin_size_t pinNumber;
  CHECK_STATE checkState;
  void (*callback_pressed)() = NULL;
  void (*callback_release)() = NULL;
  friend class BUTTONS_PICO;
public:
  BUTTON_PICO(pin_size_t pinNumber);
  void init();
  void scan(uint8_t timeout=10);
  BUTTON_STATE getState();
  void setCallback(void (*callback_pressed)(), void (*callback_release)()=NULL);
};

class BUTTONS_PICO
{
private:
  BUTTON_PICO **buttons;
  uint8_t buttons_num;
public:
  BUTTONS_PICO(BUTTON_PICO **buttons, uint8_t buttons_num);
  void init();
  void scan(uint8_t timeout=10);
  BUTTON_STATE getState(pin_size_t pinNumber);
  void setCallback(pin_size_t pinNumber, void (*callback_pressed)(), void (*callback_release)()=NULL);
};

extern BUTTON_PICO ButtonA_BSP;
extern BUTTON_PICO ButtonB_BSP;
extern BUTTON_PICO ButtonStart_BSP;
extern BUTTON_PICO ButtonSelect_BSP;
extern BUTTONS_PICO Buttons_BSP;

#endif
