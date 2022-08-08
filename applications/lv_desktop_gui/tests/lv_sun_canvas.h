#ifndef _LV_SUN_CANVAS_H__
#define _LV_SUN_CANVAS_H__

#include <lvgl.h>

// 封装一个日出日落显示控件

#define CANVAS_WIDTH   200
#define CANVAS_HEIGHT  180

#define ARC_R 80

#define MATH_PI 3.1415926535897932384626433832795

void lv_sun_canvas_test(lv_obj_t *parent);

void lv_sun_set_position(int sun_ang);
void lv_sun_canvas_set_text(const char *sun_on_time_text,const char *sun_off_time_text);
#endif //_LV_SUN_CANVAS_H__