#ifndef _LV_MYCALENDAR_H__
#define  _LV_MYCALENDAR_H__

#include <lvgl.h>

// 自定义日历控件接口

void lv_my_calendar_create(lv_obj_t *parent);
void lv_my_calendar_set_date(uint32_t year,uint32_t month,uint32_t day);




#endif