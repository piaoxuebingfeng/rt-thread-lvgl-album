#ifndef _LV_CLOCKSCREEN_PAGE_H__
#define _LV_CLOCKSCREEN_PAGE_H__

#include "lvgl.h"

// ----------------------------------------------------------------------------------
// lvgl 万年历显示界面
// 800 * 480 


struct clockscr_obj_s 
{
    lv_obj_t *clockscreen;
    lv_obj_t *top_cond;
    lv_obj_t *clock_cond;
    lv_obj_t *top_panel;
    lv_obj_t *bottom_panel;
    // left
    lv_obj_t *date_panel;   // 100
    lv_obj_t *calendar;     // 240
    lv_obj_t *day_news;     // 100
    //right
    lv_obj_t *clock_panel;          // 120
    lv_obj_t *weather_panel;        // 120
    lv_obj_t *weather_paner_below;  // 200


    // 时钟显示 label
    lv_obj_t *clock_label;

    uint16_t top_cond_width; // 状态栏显示区域宽度 默认 800
    uint16_t top_cond_height; // 状态栏显示区域高度 默认 40
    
    uint16_t clock_cond_width;  //显示区域宽度   默认 800
    uint16_t clock_cond_height; //显示区域高度   默认 440
};

typedef struct clockscr_obj_s clockscr_obj_t;

#endif