#ifndef DISPLAY_H
#define DISPLAY_H

#include "lvgl.h"

class Display
{
private:

public:
  void init();
  void routine(uint8_t timeout=5);
};

extern Display Screen_BSP;

#endif