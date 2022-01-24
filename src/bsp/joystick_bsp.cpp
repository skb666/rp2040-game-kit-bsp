#include "bsp/joystick_bsp.h"

JOYSTICK_PICO Joystick_BSP(JOY_X_PICO_PIN, JOY_Y_PICO_PIN);

JOYSTICK_PICO::JOYSTICK_PICO(pin_size_t pinX, pin_size_t pinY) 
{
  this->pinX = pinX;
  this->pinY = pinY;
}

void JOYSTICK_PICO::init() 
{
  this->checkStateX = _JOY_CHECK;
  this->checkStateY = _JOY_CHECK;
}

void JOYSTICK_PICO::scan(uint8_t timeout) 
{
  static unsigned long last_adc_time = millis();
  if(millis() - last_adc_time >= timeout) {
    // get adc value
    this->adc_x = analogRead(this->pinX);
    this->adc_y = analogRead(this->pinY);
    this->x = (float)this->adc_x / (float)this->adc_max;
    this->y = (float)this->adc_y / (float)this->adc_max;
    // joy_x state update
    switch(this->checkStateX) {
      case _JOY_CHECK: {
        if(this->x < 0.30f) {
          this->checkStateX = _JOY_NEG_COMFIRM;
        } else if(this->x > 0.70f) {
          this->checkStateX = _JOY_POS_COMFIRM;
        }
      } break;
      case _JOY_NEG_COMFIRM: {
        if(this->x < 0.25f) {
          this->checkStateX = _JOY_NEG_RELEASE;
          // joy_up_pressed
          if(this->callback_up_pressed != NULL) {
            this->callback_up_pressed();
          }
        } else {
          this->checkStateX = _JOY_CHECK;
        }
      } break;
      case _JOY_NEG_RELEASE: {
        if(this->x > 0.30f) {
          this->checkStateX = _JOY_CHECK;
          // joy_up_release
          if(this->callback_up_release != NULL) {
            this->callback_up_release();
          }
        }
      } break;
      case _JOY_POS_COMFIRM: {
        if(this->x > 0.75f) {
          this->checkStateX = _JOY_POS_RELEASE;
          // joy_down_pressed
          if(this->callback_down_pressed != NULL) {
            this->callback_down_pressed();
          }
        } else {
          this->checkStateX = _JOY_CHECK;
        }
      } break;
      case _JOY_POS_RELEASE: {
        if(this->x < 0.70f) {
          this->checkStateX = _JOY_CHECK;
          // joy_down_release
          if(this->callback_down_release != NULL) {
            this->callback_down_release();
          }
        }
      } break;
    }
    // joy_y state update
    switch(this->checkStateY) {
      case _JOY_CHECK: {
        if(this->y < 0.30f) {
          this->checkStateY = _JOY_NEG_COMFIRM;
        } else if(this->y > 0.70f) {
          this->checkStateY = _JOY_POS_COMFIRM;
        }
      } break;
      case _JOY_NEG_COMFIRM: {
        if(this->y < 0.25f) {
          this->checkStateY = _JOY_NEG_RELEASE;
          // joy_left_pressed
          if(this->callback_left_pressed != NULL) {
            this->callback_left_pressed();
          }
        } else {
          this->checkStateY = _JOY_CHECK;
        }
      } break;
      case _JOY_NEG_RELEASE: {
        if(this->y > 0.30f) {
          this->checkStateY = _JOY_CHECK;
          // joy_left_release
          if(this->callback_left_release != NULL) {
            this->callback_left_release();
          }
        }
      } break;
      case _JOY_POS_COMFIRM: {
        if(this->y > 0.75f) {
          this->checkStateY = _JOY_POS_RELEASE;
          // joy_right_pressed
          if(this->callback_right_pressed != NULL) {
            this->callback_right_pressed();
          }
        } else {
          this->checkStateY = _JOY_CHECK;
        }
      } break;
      case _JOY_POS_RELEASE: {
        if(this->y < 0.70f) {
          this->checkStateY = _JOY_CHECK;
          // joy_right_release
          if(this->callback_right_release != NULL) {
            this->callback_right_release();
          }
        }
      } break;
    }
    last_adc_time = millis();
  }
}

float JOYSTICK_PICO::getX() 
{
  return this->x;
}

float JOYSTICK_PICO::getY() 
{
  return this->y;
}

void JOYSTICK_PICO::setCallback(JOY_DIR joy_dir, void (*callback_pressed)(), void (*callback_release)())
{
  switch(joy_dir) {
    case JOY_UP: {
      this->callback_up_pressed = callback_pressed;
      this->callback_up_release = callback_release;
    } break;
    case JOY_DOWN: {
      this->callback_down_pressed = callback_pressed;
      this->callback_down_release = callback_release;
    } break;
    case JOY_LEFT: {
      this->callback_left_pressed = callback_pressed;
      this->callback_left_release = callback_release;
    } break;
    case JOY_RIGHT: {
      this->callback_right_pressed = callback_pressed;
      this->callback_right_release = callback_release;
    } break;
  }
}

// Joystick_BSP.scan();
// const uint bar_width = 40;
// uint bar_x_pos = Joystick_BSP.getX() * bar_width;
// uint bar_y_pos = Joystick_BSP.getY() * bar_width;
// Serial.print("\rX: [");
// for (int i = 0; i < bar_width; ++i)
//   Serial.print( i == bar_x_pos ? 'o' : ' ');
// Serial.print("]  Y: [");
// for (int i = 0; i < bar_width; ++i)
//   Serial.print( i == bar_y_pos ? 'o' : ' ');
// Serial.print("]");
