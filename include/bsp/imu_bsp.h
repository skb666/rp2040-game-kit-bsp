#ifndef IMU_BSP_H
#define IMU_BSP_H

#include <Arduino.h>
#include <MMA7660.h>

typedef enum {
  IMU_UP = 0,
  IMU_DOWN,
  IMU_LEFT,
  IMU_RIGHT
} IMU_DIR;

typedef enum
{
  _IMU_CHECK = 0,
  _IMU_POS_COMFIRM,
  _IMU_POS_RELEASE,
  _IMU_NEG_COMFIRM,
  _IMU_NEG_RELEASE,
} IMU_STATE;

class IMU_PICO
{
private:
  MMA7660 *imu = NULL;
  MMA7660_ACC_DATA imu_data;
  float gX, gY, gZ;
  IMU_STATE checkStateX, checkStateY;
  void (*callback_up_pressed)() = NULL;
  void (*callback_up_release)() = NULL;
  void (*callback_down_pressed)() = NULL;
  void (*callback_down_release)() = NULL;
  void (*callback_left_pressed)() = NULL;
  void (*callback_left_release)() = NULL;
  void (*callback_right_pressed)() = NULL;
  void (*callback_right_release)() = NULL;
public:
  IMU_PICO(MMA7660 *imu);
  void init();
  void scan(uint8_t timeout=20);
  float getX();
  float getY();
  float getZ();
  void setCallback(IMU_DIR imu_dir, void (*callback_pressed)(), void (*callback_release)()=NULL);
};

extern IMU_PICO IMU_BSP;

#endif
