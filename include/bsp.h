#ifndef BSP_H
#define BSP_H

#include "bsp/display.h"
#include "bsp/led_bsp.h"
#include "bsp/buzzer_bsp.h"
#include "bsp/buttons_bsp.h"
#include "bsp/joystick_bsp.h"
#include "bsp/imu_bsp.h"
#include "bsp/ir_bsp.h"

void bsp_init();
void bsp_update();

void btn_a_pressed();
void btn_a_release();
void btn_b_pressed();
void btn_b_release();
void btn_start_pressed();
void btn_start_release();
void btn_select_pressed();
void btn_select_release();
void joy_up_pressed();
void joy_up_release();
void joy_down_pressed();
void joy_down_release();
void joy_left_pressed();
void joy_left_release();
void joy_right_pressed();
void joy_right_release();
void imu_up_pressed();
void imu_up_release();
void imu_down_pressed();
void imu_down_release();
void imu_left_pressed();
void imu_left_release();
void imu_right_pressed();
void imu_right_release();

extern IRrecv IrReceiver;
extern IRsend IrSender;

#endif
