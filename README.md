# rp2040-game-kit
**rp2040-game-kit 的 bsp**

## 开发环境

**windows 11**

**Visual Studio Code** + **PlatformIO**

## 平台及框架

**Raspberry Pi Pico** + **Arduino**

## 其他

**C:/Users/用户名/.platformio/packages/framework-arduino-mbed/variants/RASPBERRY_PI_PICO/pins_arduino.h**

修改该文件中 **Wire** 的管脚

```c++
// Wire
#define PIN_WIRE_SDA        (10u)
#define PIN_WIRE_SCL        (11u)
```

**[test/midi2buzzer.py](test/midi2buzzer.py)**

	可用于转换 [onlinesequencer.net]([Online Sequencer](https://onlinesequencer.net/)) schematic format 的乐谱

**[test/upload.py](test/upload.py)**

	当PIO的upload无效时，可用该脚本自动上传固件