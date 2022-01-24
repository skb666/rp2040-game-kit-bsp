#include "bsp.h"

void bsp_init() {
  Serial.begin(115200);
  Screen_BSP.init();
  LED_BSP.init();
  Buzzer_BSP.init();
  Buttons_BSP.init();
  Joystick_BSP.init();
  IMU_BSP.init();

  Buttons_BSP.setCallback(BTN_A_PICO_PIN, btn_a_pressed, btn_a_release);
  Buttons_BSP.setCallback(BTN_B_PICO_PIN, btn_b_pressed, btn_b_release);
  Buttons_BSP.setCallback(BTN_START_PICO_PIN, btn_start_pressed, btn_start_release);
  Buttons_BSP.setCallback(BTN_SELECT_PICO_PIN, btn_select_pressed, btn_select_release);
  Joystick_BSP.setCallback(JOY_UP, joy_up_pressed, joy_up_release);
  Joystick_BSP.setCallback(JOY_DOWN, joy_down_pressed, joy_down_release);
  Joystick_BSP.setCallback(JOY_LEFT, joy_left_pressed, joy_left_release);
  Joystick_BSP.setCallback(JOY_RIGHT, joy_right_pressed, joy_right_release);
  IMU_BSP.setCallback(IMU_UP, imu_up_pressed, imu_up_release);
  IMU_BSP.setCallback(IMU_DOWN, imu_down_pressed, imu_down_release);
  IMU_BSP.setCallback(IMU_LEFT, imu_left_pressed, imu_left_release);
  IMU_BSP.setCallback(IMU_RIGHT, imu_right_pressed, imu_right_release);

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  IrSender.begin(IR_SEND_PIN, ENABLE_LED_FEEDBACK);

  IrReceiver.start();
}

void bsp_update() {
  Screen_BSP.routine();
  Buttons_BSP.scan();
  Joystick_BSP.scan();
  IMU_BSP.scan();

  if (IrReceiver.available()) {
    storeCode(IrReceiver.read());
    IrReceiver.resume(); // resume receiver
  }
}

void btn_a_pressed() {
  Serial.println("BTN_A Pressed");
  IrReceiver.stop();
  LED_BSP.on();
  sendCode(&sStoredIRData);
  LED_BSP.off();
}

void btn_a_release() {
  Serial.println("BTN_A Release");
  IrReceiver.start();
}

void btn_b_pressed() {
  Serial.println("BTN_B Pressed");
}

void btn_b_release() {
  Serial.println("BTN_B Release");
}

void btn_start_pressed() {
  Serial.println("BTN_START Pressed");
}

void btn_start_release() {
  Serial.println("BTN_START Release");
  if(Buzzer_BSP.pause()) {
    Serial.println("Buzzer restart");
  } else {
    Serial.println("Buzzer paused");
  }
}

void btn_select_pressed() {
  Serial.println("BTN_SELECT Pressed");
}

void btn_select_release() {
  Serial.println("BTN_SELECT Release");
}

void joy_up_pressed() {
  Serial.println("JOY_UP Pressed");
}

void joy_up_release() {
  Serial.println("JOY_UP Release");
}

void joy_down_pressed() {
  Serial.println("JOY_DOWN Pressed");
}

void joy_down_release() {
  Serial.println("JOY_DOWN Release");
}

void joy_left_pressed() {
  Serial.println("JOY_LEFT Pressed");
}

void joy_left_release() {
  Serial.println("JOY_LEFT Release");
}

void joy_right_pressed() {
  Serial.println("JOY_RIGHT Pressed");
}

void joy_right_release() {
  Serial.println("JOY_RIGHT Release");
}

void imu_up_pressed() {
  Serial.println("IMU_UP Pressed");
  lv_disp_set_rotation(NULL, LV_DISP_ROT_180);
}

void imu_up_release() {
  Serial.println("IMU_UP Release");
}

void imu_down_pressed() {
  Serial.println("IMU_DOWN Pressed");
  lv_disp_set_rotation(NULL, LV_DISP_ROT_NONE);
}

void imu_down_release() {
  Serial.println("IMU_DOWN Release");
}

void imu_left_pressed() {
  Serial.println("IMU_LEFT Pressed");
  lv_disp_set_rotation(NULL, LV_DISP_ROT_270);
}

void imu_left_release() {
  Serial.println("IMU_LEFT Release");
}

void imu_right_pressed() {
  Serial.println("IMU_RIGHT Pressed");
  lv_disp_set_rotation(NULL, LV_DISP_ROT_90);
}

void imu_right_release() {
  Serial.println("IMU_RIGHT Release");
}

