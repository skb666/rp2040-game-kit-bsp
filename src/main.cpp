#include <Arduino.h>
#define RAW_BUFFER_LENGTH  750  // 750 is the value for air condition remotes.
#define RECORD_GAP_MICROS  20000
#define INFO // To see valuable informations from universal decoder for pulse width or pulse distance protocols
#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>
#include <LittleFS_Mbed_RP2040.h>

#include "bsp.h"
#include "song.h"
#include "lv_cubic_gui.h"

void setup() {
  bsp_init();

  LED_BSP.on();
  lv_cubic_gui();
  Screen_BSP.routine(0);
  while (!Serial)
  sleep_ms(1000);
  Serial.println("hello world!");
  LED_BSP.toggle();

  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols (&Serial);
  Serial.print(F("at pin "));
  Serial.println(IR_RECEIVE_PIN);
  Serial.print(F("Ready to send IR signals at pin "));
  Serial.print(IR_SEND_PIN);
}

void loop() {
  static uint8_t music = 0;

  bsp_update();

  switch(music) {
    case 0: Buzzer_BSP.play(100, 0, demo_song); break;
    case 1: Buzzer_BSP.play(80, 0, my_people_my_country); break;
    case 2: Buzzer_BSP.play(50, 0, turkish_march); break;
  }

  if(Buzzer_BSP.isStop()) {
    music = (music + 1) % 3;
  }
}
