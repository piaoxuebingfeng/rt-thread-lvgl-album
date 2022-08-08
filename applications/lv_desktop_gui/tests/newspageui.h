// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: news_page

#ifndef _NEWS_PAGE_UI_H
#define _NEWS_PAGE_UI_H

#ifdef __cplusplus
extern "C" {
#endif

//#if __has_include(<lvgl.h>)
//#include <lvgl.h>
//#else
//#include "lvgl/lvgl.h"
//#endif
#include <lvgl.h>

// extern lv_obj_t * ui_Screen1;
// extern lv_obj_t * ui_topstatuspanel;
// extern lv_obj_t * ui_Label3;
// extern lv_obj_t * ui_newspanel;
// extern lv_obj_t * ui_newstitle;
// extern lv_obj_t * ui_newslabel;
// extern lv_obj_t * ui_Panel3;
// extern lv_obj_t * ui_Panel4;
// extern lv_obj_t * ui_Calendar1;
// extern lv_obj_t * ui_weatherpanel;
// extern lv_obj_t * ui_weathertitle;
// extern lv_obj_t * ui_Label1;




LV_FONT_DECLARE(ui_font_cnfontgeneral18);
// LV_FONT_DECLARE(ui_font_Font1);
// LV_FONT_DECLARE(ui_font_lishu112);
LV_FONT_DECLARE(ui_font_lishu16);
LV_FONT_DECLARE(ui_font_lishu24);


void ui_news_page_screen_init(lv_obj_t *parent);
// void ui_init(void);


typedef struct news_s news_t;

struct news_s {
	int news_list_count;   // 当前显示的第几条新闻
	int news_list_num;     // 新闻总数量
	char *news_mtime;
  char *news_title;
	char *news_digest;
	
	news_t *next;  // 单项链表
};
extern news_t *news_head ;

void news_list_init();
void news_list_show();
void news_list_deinit();

void ui_set_news_title(const char * buf);
void ui_news_set_time(const char *buf);
void ui_set_news_time(const char *buf);
void ui_set_news_digest(const char * buf);


void news_str_update();
void news_show_update();


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
