// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: xiangce

#ifndef _XIANGCE_UI_H
#define _XIANGCE_UI_H

#ifdef __cplusplus
extern "C" {
#endif

//#if __has_include("lvgl.h")
//#include "lvgl.h"
//#else
//#include "lvgl/lvgl.h"
//#endif
#include <lvgl.h>

#include "dfs.h"
#include "fcntl.h"
#include "unistd.h"

//extern lv_obj_t * ui_albumpage;
//extern lv_obj_t * ui_Image1;
//extern lv_obj_t * ui_Image2;
//extern lv_obj_t * ui_Image3;
//extern lv_obj_t * ui_bottompanel;
//extern lv_obj_t * ui_btnleft;
//extern lv_obj_t * ui_Labbtnleft;
//extern lv_obj_t * ui_btnright;
//extern lv_obj_t * ui_Labbtnright;


LV_IMG_DECLARE(bg_lvgl);    // assets\testbg.png
LV_IMG_DECLARE(ui_img_testbg_png);    // assets\testbg.png
LV_IMG_DECLARE(ui_img_seaandsky800_png);    // assets\seaandsky800.png



typedef struct imgs_mgt_s imgs_mgt_t;

struct imgs_mgt_s
{
	int imgs_count;
	int imgs_total_nums;
	char *imgs_path;
	char *imgs_lvgl_path;
	
	imgs_mgt_t *next;
};




void ui_init(void);
void ui_albumpage_screen_init(lv_obj_t *parent);


void imgs_list_init();
void imgs_set_current_img_node_head();
void lv_albumpage_auto_update();
void imgs_list_deinit();
void imgs_list_show();




#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
