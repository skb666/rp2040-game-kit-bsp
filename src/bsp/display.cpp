#include "bsp/display.h"
#include <TFT_eSPI.h>

static TFT_eSPI *tft = new TFT_eSPI();
Display Screen_BSP;

void my_print(lv_log_level_t level, const char* file, uint32_t line, const char* fun, const char* dsc)
{
  char bf[50];
  sprintf(bf, "%s@%d %s->%s", file, line, fun, dsc);
  Serial.println(bf);
}

void my_disp_flush(lv_disp_drv_t* disp, const lv_area_t* area, lv_color_t* color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft->startWrite();
  tft->setAddrWindow(area->x1, area->y1, w, h);
  tft->pushColors(&color_p->full, w * h, true);
  tft->endWrite();

  lv_disp_flush_ready(disp);
}

void Display::init()
{
  lv_init();

  lv_log_register_print_cb(my_print); /* register print function for debugging */

  tft->begin(); /* TFT init */
  tft->setRotation(0);

  lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

  /*Initialize the display*/
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = 240;
  disp_drv.ver_res = 240;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.buffer = &disp_buf;
  disp_drv.sw_rotate = 1;
  disp_drv.rotated = LV_DISP_ROT_NONE;
  lv_disp_drv_register(&disp_drv);
}

void Display::routine(uint8_t timeout)
{
  static unsigned long last_update_time = millis();
  if(millis() - last_update_time >= timeout) {
    lv_task_handler();
    last_update_time = millis();
  }
}

