#ifndef JOYSTICK_BSP_H
#define JOYSTICK_BSP_H

#include <Arduino.h>

#define JOY_X_PICO_PIN 28
#define JOY_Y_PICO_PIN 29

typedef enum {
  JOY_UP = 0,
  JOY_DOWN,
  JOY_LEFT,
  JOY_RIGHT
} JOY_DIR;

typedef enum
{
  _JOY_CHECK = 0,
  _JOY_POS_COMFIRM,
  _JOY_POS_RELEASE,
  _JOY_NEG_COMFIRM,
  _JOY_NEG_RELEASE,
} JOY_STATE;

class JOYSTICK_PICO
{
private:
  pin_size_t pinX, pinY;
  uint adc_x, adc_y;
  float x, y;
  const uint adc_max = (1 << 10) - 1;
  JOY_STATE checkStateX, checkStateY;
  void (*callback_up_pressed)() = NULL;
  void (*callback_up_release)() = NULL;
  void (*callback_down_pressed)() = NULL;
  void (*callback_down_release)() = NULL;
  void (*callback_left_pressed)() = NULL;
  void (*callback_left_release)() = NULL;
  void (*callback_right_pressed)() = NULL;
  void (*callback_right_release)() = NULL;
public:
  JOYSTICK_PICO(pin_size_t pinX, pin_size_t pinY);
  void init();
  void scan(uint8_t timeout=20);
  float getX();
  float getY();
  void setCallback(JOY_DIR joy_dir, void (*callback_pressed)(), void (*callback_release)()=NULL);
};

extern JOYSTICK_PICO Joystick_BSP;

#endif
