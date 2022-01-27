#include <Arduino.h>
#define RAW_BUFFER_LENGTH  750  // 750 is the value for air condition remotes.
#define RECORD_GAP_MICROS  20000
#define INFO // To see valuable informations from universal decoder for pulse width or pulse distance protocols
#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>

#include "mbed.h"
#include "USBMSD.h"
#include "FlashIAPBlockDevice.h"
#include "FATFileSystem.h"

#define RP2040_FLASH_SIZE         (2 * 1024 * 1024)
#define RP2040_FS_LOCATION_END    RP2040_FLASH_SIZE
#define RP2040_FS_SIZE_KB         (1024)
#define RP2040_FS_START           (RP2040_FLASH_SIZE - (RP2040_FS_SIZE_KB * 1024))

#define MBED_FATFS_FILE_NAME     "fatfs"
#define MBED_FATFS_FILE_PREFIX   "/" MBED_FATFS_FILE_NAME

static FlashIAPBlockDevice bd(XIP_BASE + RP2040_FS_START, (RP2040_FS_SIZE_KB * 1024));
static mbed::FATFileSystem fs(MBED_FATFS_FILE_NAME);

#include "bsp.h"
#include "song.h"
#include "lv_cubic_gui.h"

int mkdirs(const char *mudir) {
  uint8_t flag = 0, len = strlen(mudir);
  int err;
  char dirname[256];
  strncpy(dirname, mudir, len);
  for(int i=1; i<len; ++i) {
    if(dirname[i] == '/') {
      if(flag) {
        dirname[i] = '\0';
        err = mkdir(dirname, 0777);
        if(!err) {
          Serial.print(dirname);
          Serial.println(" => Create OK");
        } else {
          Serial.println(" => Create Failed");
          return 1;
        }
        dirname[i] = '/';
      } else {
        flag = 1;
      }
    }
  }
  if(dirname[len-1] != '/') {
    err = mkdir(dirname, 0777);
  }
  return err;
}

void setup() {
  bsp_init();

  LED_BSP.on();
  lv_cubic_gui();
  Screen_BSP.routine(0);
  LED_BSP.off();

  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols (&Serial);
  Serial.print(F("at pin "));
  Serial.println(IR_RECEIVE_PIN);
  Serial.print(F("Ready to send IR signals at pin "));
  Serial.println(IR_SEND_PIN);

  DIR* dir;
  struct dirent* de;
  FILE *file;
  char dirname[] = MBED_FATFS_FILE_PREFIX "/IR/";
  char fileName[] = MBED_FATFS_FILE_PREFIX "/hello.txt";
  char buf_t[100];
  int cnt = 0, err = fs.mount(&bd);

  if(err) {
    // Reformat if we can't mount the filesystem
    Serial.println("Formatting... ");
    err = fs.reformat(&bd);
    if(err) {
      Serial.println("FatFS error");
      return;
    }
  }

  dir = opendir(dirname);
  if(dir == NULL) {
    err = mkdirs(dirname);
    if(!err) {
      dir = opendir(dirname);
    } else {
      return;
    }
  }

  if(dir) {
    strcpy(buf_t, MBED_FATFS_FILE_PREFIX);
    strcat(buf_t, "/number");
    file = fopen(buf_t, "rb");
    Serial.print(buf_t);
    if(file) {
      Serial.println(" => Open OK");
      fread(&cnt, sizeof(cnt), 1, file);
      Serial.print("* Reading: cnt = ");
      Serial.println(cnt);
      fclose(file);
    } else {
      Serial.println(" => Open Failed");
    }

    file = fopen(fileName, "w");
    Serial.print(fileName);
    if(file) {
      Serial.println(" => Open OK");
      cnt = 0;
      while((de = readdir(dir)) != NULL){
        cnt++;
        sprintf(buf_t, "%s\t->\t%d\n", de->d_name, de->d_type);
        if(fwrite(buf_t, 1, strlen(buf_t), file)) {
          Serial.println("* Writing OK");
        } else {
          Serial.println("* Writing failed");
        }
      }
      fclose(file);
    } else {
      Serial.println(" => Open Failed");
    }

    strcpy(buf_t, MBED_FATFS_FILE_PREFIX);
    strcat(buf_t, "/number");
    file = fopen(buf_t, "wb");
    Serial.print(buf_t);
    if(file) {
      Serial.println(" => Open OK");
      if(fwrite(&cnt, sizeof(cnt), 1, file)) {
        Serial.println("* Writing OK");
      } else {
        Serial.println("* Writing failed");
      }
      fclose(file);
    } else {
      Serial.println(" => Open Failed");
    }

    closedir(dir);
  }
}

void loop() {
  static uint8_t music = 0;
  static USBMSD *usb = new USBMSD(&bd);
  
  usb->process();

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
