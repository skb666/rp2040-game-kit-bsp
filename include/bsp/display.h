#ifndef DISPLAY_H
#define DISPLAY_H

#include "lvgl.h"

class Display
{
private:
  lv_disp_drv_t disp_drv;
  lv_disp_buf_t disp_buf;
  lv_color_t buf[LV_HOR_RES_MAX * 10];
public:
  void init();
  void routine(uint8_t timeout=5);
};

extern Display Screen_BSP;

#endif