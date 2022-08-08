
/**
 * @file simple_test.c
 *
 */



/*********************
 *      INCLUDES
 *********************/
#include "simple_test.h"

#if LV_100ASK_2048_SIMPLE_TEST != 0

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/



/**********************
 *  STATIC PROTOTYPES
 **********************/


/**********************
 *  STATIC VARIABLES
 **********************/


/**********************
 *      MACROS
 **********************/


/**********************
 *   GLOBAL FUNCTIONS
 **********************/
static void game_2048_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj_2048 = lv_event_get_target(e);
    lv_obj_t * label = lv_event_get_user_data(e);
    
    if(code == LV_EVENT_VALUE_CHANGED) {
        if (lv_100ask_2048_get_best_tile(obj_2048) >= 2048)
            lv_label_set_text(label, "#00b329 YOU WIN! #");
        else if(lv_100ask_2048_get_status(obj_2048))
            lv_label_set_text(label, "#00b329 www.100ask.net: # #ff0000 GAME OVER! #");
        else
            lv_label_set_text_fmt(label, "SCORE: #ff00ff %d #", lv_100ask_2048_get_score(obj_2048));
    }
}

static void new_game_btn_event_handler(lv_event_t * e)
{
    lv_obj_t * obj_2048 = lv_event_get_user_data(e);

    lv_100ask_2048_set_new_game(obj_2048);
}


void lv_100ask_2048_simple_test(lv_obj_t *page)
{
		lv_obj_t *game_ScreenPage = lv_obj_create(page);
    lv_obj_clear_flag(game_ScreenPage, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(game_ScreenPage, LV_HOR_RES, LV_VER_RES);       // 设置到屏幕大小
    lv_obj_set_style_bg_color(game_ScreenPage, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(game_ScreenPage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_radius(game_ScreenPage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(game_ScreenPage,0,LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_align(game_ScreenPage,LV_ALIGN_CENTER,0,0);
	
	lv_obj_t *gamepage_scr =  lv_obj_create(game_ScreenPage);
	lv_obj_clear_flag(gamepage_scr, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_size(gamepage_scr, LV_HOR_RES, LV_VER_RES-40);       // 设置到屏幕大小
	lv_obj_set_style_bg_color(gamepage_scr, lv_color_hex(0xECEBEB), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(gamepage_scr, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(gamepage_scr,LV_ALIGN_CENTER,0,20);
//	lv_obj_center(gamepage_scr);
    /*Create 2048 game*/
    lv_obj_t * obj_2048 = lv_100ask_2048_create(gamepage_scr);
#if LV_FONT_MONTSERRAT_40    
    lv_obj_set_style_text_font(obj_2048, &lv_font_montserrat_40, 0);
#endif
//		lv_obj_set_size(obj_2048, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_size(obj_2048, 400, 400);
    lv_obj_center(obj_2048);

    /*Information*/
    lv_obj_t * label = lv_label_create(gamepage_scr);
    lv_label_set_recolor(label, true); 
    lv_label_set_text_fmt(label, "SCORE: #ff00ff %d #", lv_100ask_2048_get_score(obj_2048));
    lv_obj_align_to(label, obj_2048, LV_ALIGN_OUT_RIGHT_TOP, 0, 0);

    lv_obj_add_event_cb(obj_2048, game_2048_event_cb, LV_EVENT_ALL, label);

    /*New Game*/
    lv_obj_t * btn = lv_btn_create(gamepage_scr);
    lv_obj_align_to(btn, obj_2048, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
    lv_obj_add_event_cb(btn, new_game_btn_event_handler, LV_EVENT_CLICKED, obj_2048);

    label = lv_label_create(btn);
    lv_label_set_text(label, "New Game");
    lv_obj_center(label);
}


/*=====================
 * Other functions
 *====================*/

/**********************
 *   STATIC FUNCTIONS
 **********************/


#endif  /*SIMPLE_TEST*/
