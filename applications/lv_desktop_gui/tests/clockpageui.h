#ifndef _CLOCKPAGEUI_H__
#define _CLOCKPAGEUI_H__


#include <lvgl.h>


//void lv_clock_calendar_set_date(uint32_t year,uint32_t month,uint32_t day);
//void lv_clock_set_time(const char* time_str);

void clockpageui(lv_obj_t *page);

void lv_clock_label_create(lv_obj_t *parent);
void lv_clock_label_update(uint8_t hour, uint8_t min,uint8_t sec);


#endif
