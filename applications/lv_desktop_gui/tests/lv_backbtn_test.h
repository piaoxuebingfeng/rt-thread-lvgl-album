#ifndef _LV_BACKBTN_TEST_H__
#define _LV_BACKBTN_TEST_H__
#include "lvgl.h"
#include "lv_clockscreen_page.h"

// 定义一个桌面悬浮球的结构体，用于管理桌面悬浮球对象
struct desktop_menubtn_s
{
    lv_obj_t *menubtn_parent;
    lv_obj_t *menubtn;         //桌面悬浮球按钮
    lv_obj_t *menu_panel;      //子菜单面板
    lv_obj_t *backscreenbtn;   //返回到上一级主界面
    lv_obj_t *timesceen_btn;   //进入时钟显示界面
    lv_obj_t *musicsceen_btn;  //进入音乐播放界面 
    lv_obj_t *weatherscreen_btn; //进入天气界面
    bool btnMenuState;
    uint16_t menubtn_pos_x;   // 悬浮球当前 x 坐标
    uint16_t menubtn_pos_y;   // 悬浮球当前 y 坐标
};

typedef struct desktop_menubtn_s desktop_menubtn_t;

void lv_desktop_top_symbol_create(lv_obj_t* parent);
void lv_desktop_backbtn_create(lv_obj_t * parent);
void lv_backbtn_event_cb(lv_event_t * e);
void lv_submenu_create(desktop_menubtn_t *dm_t);
void lv_submenu_clear(desktop_menubtn_t *dm_t);


void desktopmainpage_update();

void desktop_img_switch(const char *imgsrc);

extern clockscr_obj_t clock_screen_t;

#endif