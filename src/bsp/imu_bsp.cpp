#include "bsp/imu_bsp.h"

static MMA7660 accelemeter;

IMU_PICO IMU_BSP(&accelemeter);

IMU_PICO::IMU_PICO(MMA7660 *imu) 
{
  this->imu = imu;
}

void IMU_PICO::init() 
{
  this->imu->init();
  this->checkStateX = _IMU_CHECK;
  this->checkStateY = _IMU_CHECK;
}

void IMU_PICO::scan(uint8_t timeout) 
{
  static unsigned long last_imu_time = millis();
  if(millis() - last_imu_time >= timeout) {
    if(this->imu->getAcceleration(&(this->imu_data))) {
      this->gX = (this->imu_data.x.g + 1.50f) / 3.00f;
      this->gY = (this->imu_data.y.g + 1.50f) / 3.00f;
      this->gZ = (this->imu_data.z.g + 1.50f) / 3.00f;
    }
    // imu_x state update
    switch(this->checkStateX) {
      case _IMU_CHECK: {
        if(this->gX < 0.27f) {
          this->checkStateX = _IMU_NEG_COMFIRM;
        } else if(this->gX > 0.83f) {
          this->checkStateX = _IMU_POS_COMFIRM;
        }
      } break;
      case _IMU_NEG_COMFIRM: {
        if(this->gX < 0.22f) {
          this->checkStateX = _IMU_NEG_RELEASE;
          // imu_down_pressed
          if(this->callback_down_pressed != NULL) {
            this->callback_down_pressed();
          }
        } else {
          this->checkStateX = _IMU_CHECK;
        }
      } break;
      case _IMU_NEG_RELEASE: {
        if(this->gX > 0.45f) {
          this->checkStateX = _IMU_CHECK;
          // imu_down_release
          if(this->callback_down_release != NULL) {
            this->callback_down_release();
          }
        }
      } break;
      case _IMU_POS_COMFIRM: {
        if(this->gX > 0.85f) {
          this->checkStateX = _IMU_POS_RELEASE;
          // imu_up_pressed
          if(this->callback_up_pressed != NULL) {
            this->callback_up_pressed();
          }
        } else {
          this->checkStateX = _IMU_CHECK;
        }
      } break;
      case _IMU_POS_RELEASE: {
        if(this->gX < 0.63f) {
          this->checkStateX = _IMU_CHECK;
          // imu_up_release
          if(this->callback_up_release != NULL) {
            this->callback_up_release();
          }
        }
      } break;
    }
    // imu_y state update
    switch(this->checkStateY) {
      case _IMU_CHECK: {
        if(this->gY < 0.25f) {
          this->checkStateY = _IMU_NEG_COMFIRM;
        } else if(this->gY > 0.75f) {
          this->checkStateY = _IMU_POS_COMFIRM;
        }
      } break;
      case _IMU_NEG_COMFIRM: {
        if(this->gY < 0.20f) {
          this->checkStateY = _IMU_NEG_RELEASE;
          // imu_left_pressed
          if(this->callback_left_pressed != NULL) {
            this->callback_left_pressed();
          }
        } else {
          this->checkStateY = _IMU_CHECK;
        }
      } break;
      case _IMU_NEG_RELEASE: {
        if(this->gY > 0.40f) {
          this->checkStateY = _IMU_CHECK;
          // imu_left_release
          if(this->callback_left_release != NULL) {
            this->callback_left_release();
          }
        }
      } break;
      case _IMU_POS_COMFIRM: {
        if(this->gY > 0.80f) {
          this->checkStateY = _IMU_POS_RELEASE;
          // imu_right_pressed
          if(this->callback_right_pressed != NULL) {
            this->callback_right_pressed();
          }
        } else {
          this->checkStateY = _IMU_CHECK;
        }
      } break;
      case _IMU_POS_RELEASE: {
        if(this->gY < 0.63f) {
          this->checkStateY = _IMU_CHECK;
          // imu_right_release
          if(this->callback_right_release != NULL) {
            this->callback_right_release();
          }
        }
      } break;
    }
    last_imu_time = millis();
  }
}

float IMU_PICO::getX() 
{
  return this->gX;
}

float IMU_PICO::getY() 
{
  return this->gY;
}

float IMU_PICO::getZ() 
{
  return this->gZ;
}

void IMU_PICO::setCallback(IMU_DIR imu_dir, void (*callback_pressed)(), void (*callback_release)())
{
  switch(imu_dir) {
    case IMU_UP: {
      this->callback_up_pressed = callback_pressed;
      this->callback_up_release = callback_release;
    } break;
    case IMU_DOWN: {
      this->callback_down_pressed = callback_pressed;
      this->callback_down_release = callback_release;
    } break;
    case IMU_LEFT: {
      this->callback_left_pressed = callback_pressed;
      this->callback_left_release = callback_release;
    } break;
    case IMU_RIGHT: {
      this->callback_right_pressed = callback_pressed;
      this->callback_right_release = callback_release;
    } break;
  }
}

// char buf_t[100];
// float x, y;
// x = IMU_BSP.getX();
// y = IMU_BSP.getY();
// sprintf(buf_t, "\rx: %5.2f | y: %5.2f", x, y);
// Serial.print(buf_t);

