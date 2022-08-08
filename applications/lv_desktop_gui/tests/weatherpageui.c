#include <weatherpageui.h>
#include <lvgl.h>


#include "lv_sun_canvas.h"


static lv_obj_t * ui_WeatherScrPage;
static lv_obj_t * ui_upstatuspanel;
static lv_obj_t * ui_locationlabel;
static lv_obj_t * ui_Image19;
static lv_obj_t * ui_TimeLabel;
static lv_obj_t * ui_weatherpanelup;
static lv_obj_t * ui_dateweather4;
static lv_obj_t * ui_weathershow1;
static lv_obj_t * ui_TextArea4;
static lv_obj_t * ui_dateweather5;
static lv_obj_t * ui_weathershow4;
static lv_obj_t * ui_TextArea5;
static lv_obj_t * ui_dateweather6;
static lv_obj_t * ui_weathershow5;
static lv_obj_t * ui_TextArea6;
static lv_obj_t * ui_dateweather7;
static lv_obj_t * ui_weathershow6;
static lv_obj_t * ui_TextArea7;
static lv_obj_t * ui_sunpanel;
static lv_obj_t * ui_preferencepanel;


static const void *icon_weather_array[] = {
																		&ui_img_qing_png,
																		&ui_img_yin_png,
																		&ui_img_duoyun_png,
																		&ui_img_xiaoyu_png,
																		&ui_img_zhongyu_png,
																		&ui_img_dayu_png,
																		&ui_img_baoyu_png,
																		&ui_img_dabaoyu_png,
																		&ui_img_tedabaoyu_png,
																		&ui_img_zhenyu_png,
																		&ui_img_xiaoxue_png,
																		&ui_img_zhongxue_png,
																		&ui_img_daxue_png,
																		&ui_img_baoxue_png,
																		&ui_img_zhenxue_png,
																		&ui_img_yujiaxue_png,
																		&ui_img_shachenbao_png,
																		&ui_img_leizhenyubingbao_png,
																		&ui_img_wu_png,
																		&ui_img_leizhenyu_png
};


void weatherpage_set_time_label(const char *time_str)
{
	if(ui_TimeLabel && time_str)
	{
		lv_label_set_text(ui_TimeLabel, time_str);
	}
}



																		

void weatherpageui_init(lv_obj_t *parent)
{
	// ui_WeatherScrPage

	ui_WeatherScrPage = lv_obj_create(parent);

	lv_obj_clear_flag(ui_WeatherScrPage, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_size(ui_WeatherScrPage, LV_HOR_RES, LV_VER_RES);       // ���õ���Ļ��С
	lv_obj_set_style_bg_color(ui_WeatherScrPage, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui_WeatherScrPage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_WeatherScrPage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_WeatherScrPage, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_WeatherScrPage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_WeatherScrPage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	

	// // ui_upstatuspanel

	// ui_upstatuspanel = lv_obj_create(ui_WeatherScrPage);

	// lv_obj_set_width(ui_upstatuspanel, 800);
	// lv_obj_set_height(ui_upstatuspanel, 40);

	// lv_obj_set_x(ui_upstatuspanel, 0);
	// lv_obj_set_y(ui_upstatuspanel, -220);

	// lv_obj_set_align(ui_upstatuspanel, LV_ALIGN_CENTER);

	// lv_obj_clear_flag(ui_upstatuspanel, LV_OBJ_FLAG_SCROLLABLE);

	// lv_obj_set_style_radius(ui_upstatuspanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	// lv_obj_set_style_bg_color(ui_upstatuspanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	// lv_obj_set_style_bg_opa(ui_upstatuspanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	// lv_obj_set_style_border_color(ui_upstatuspanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	// lv_obj_set_style_border_opa(ui_upstatuspanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	// lv_obj_set_style_border_width(ui_upstatuspanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// // ui_locationlabel

	// ui_locationlabel = lv_label_create(ui_upstatuspanel);

	// lv_obj_set_width(ui_locationlabel, LV_SIZE_CONTENT);
	// lv_obj_set_height(ui_locationlabel, LV_SIZE_CONTENT);

	// lv_obj_set_x(ui_locationlabel, -320);
	// lv_obj_set_y(ui_locationlabel, 0);

	// lv_obj_set_align(ui_locationlabel, LV_ALIGN_CENTER);

	// lv_label_set_text(ui_locationlabel, "ZhengZhou");

	// // ui_Image19

	// ui_Image19 = lv_img_create(ui_upstatuspanel);
	// lv_img_set_src(ui_Image19, &ui_img_iconlocation16_png);

	// lv_obj_set_width(ui_Image19, LV_SIZE_CONTENT);
	// lv_obj_set_height(ui_Image19, LV_SIZE_CONTENT);

	// lv_obj_set_x(ui_Image19, -380);
	// lv_obj_set_y(ui_Image19, 0);

	// lv_obj_set_align(ui_Image19, LV_ALIGN_CENTER);

	// lv_obj_add_flag(ui_Image19, LV_OBJ_FLAG_ADV_HITTEST);
	// lv_obj_clear_flag(ui_Image19, LV_OBJ_FLAG_SCROLLABLE);

	// // ui_TimeLabel

	// ui_TimeLabel = lv_label_create(ui_upstatuspanel);

	// lv_obj_set_width(ui_TimeLabel, LV_SIZE_CONTENT);
	// lv_obj_set_height(ui_TimeLabel, LV_SIZE_CONTENT);

	// lv_obj_set_x(ui_TimeLabel, 0);
	// lv_obj_set_y(ui_TimeLabel, 0);

	// lv_obj_set_align(ui_TimeLabel, LV_ALIGN_CENTER);

	// lv_label_set_text(ui_TimeLabel, "18:00");

	// ui_weatherpanelup

	ui_weatherpanelup = lv_obj_create(ui_WeatherScrPage);

	lv_obj_set_width(ui_weatherpanelup, 790);
	lv_obj_set_height(ui_weatherpanelup, 220);

	lv_obj_set_x(ui_weatherpanelup, 0);
	lv_obj_set_y(ui_weatherpanelup, -85);

	lv_obj_set_align(ui_weatherpanelup, LV_ALIGN_CENTER);

	lv_obj_clear_flag(ui_weatherpanelup, LV_OBJ_FLAG_SCROLLABLE);

	lv_obj_set_style_radius(ui_weatherpanelup, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_weatherpanelup, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_weatherpanelup, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_weatherpanelup, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_weatherpanelup, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_weatherpanelup, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

	// ui_dateweather4

	ui_dateweather4 = lv_obj_create(ui_weatherpanelup);

	lv_obj_set_width(ui_dateweather4, 100);
	lv_obj_set_height(ui_dateweather4, 180);

	lv_obj_set_x(ui_dateweather4, -300);
	lv_obj_set_y(ui_dateweather4, 0);

	lv_obj_set_align(ui_dateweather4, LV_ALIGN_CENTER);

	lv_obj_clear_flag(ui_dateweather4, LV_OBJ_FLAG_SCROLLABLE);

	lv_obj_set_style_radius(ui_dateweather4, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_dateweather4, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_dateweather4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_dateweather4, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_dateweather4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_dateweather4, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

	// ui_weathershow1

	ui_weathershow1 = lv_img_create(ui_dateweather4);
	lv_img_set_src(ui_weathershow1, &ui_img_qing_png);

	lv_obj_set_width(ui_weathershow1, LV_SIZE_CONTENT);
	lv_obj_set_height(ui_weathershow1, LV_SIZE_CONTENT);

	lv_obj_set_x(ui_weathershow1, 0);
	lv_obj_set_y(ui_weathershow1, -30);

	lv_obj_set_align(ui_weathershow1, LV_ALIGN_CENTER);

	lv_obj_add_flag(ui_weathershow1, LV_OBJ_FLAG_ADV_HITTEST);
	lv_obj_clear_flag(ui_weathershow1, LV_OBJ_FLAG_SCROLLABLE);

	// ui_TextArea4

	ui_TextArea4 = lv_textarea_create(ui_dateweather4);

	lv_obj_set_width(ui_TextArea4, 50);
	lv_obj_set_height(ui_TextArea4, 30);

	lv_obj_set_x(ui_TextArea4, 0);
	lv_obj_set_y(ui_TextArea4, 40);

	lv_obj_set_align(ui_TextArea4, LV_ALIGN_CENTER);

//	if("" == "") lv_textarea_set_accepted_chars(ui_TextArea4, NULL);
//	else lv_textarea_set_accepted_chars(ui_TextArea4, "");

	lv_obj_set_style_text_color(ui_TextArea4,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_TextArea4, "7/21");
//	lv_textarea_set_placeholder_text(ui_TextArea4, "Placeholder...");
	lv_textarea_set_one_line(ui_TextArea4, true);

	lv_obj_clear_flag(ui_TextArea4, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_TextArea4, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_TextArea4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_TextArea4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// ui_dateweather5

	ui_dateweather5 = lv_obj_create(ui_weatherpanelup);

	lv_obj_set_width(ui_dateweather5, 100);
	lv_obj_set_height(ui_dateweather5, 180);

	lv_obj_set_x(ui_dateweather5, -100);
	lv_obj_set_y(ui_dateweather5, 0);

	lv_obj_set_align(ui_dateweather5, LV_ALIGN_CENTER);

	lv_obj_clear_flag(ui_dateweather5, LV_OBJ_FLAG_SCROLLABLE);

	lv_obj_set_style_radius(ui_dateweather5, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_dateweather5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_dateweather5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_dateweather5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_dateweather5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_dateweather5, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

	// ui_weathershow4

	ui_weathershow4 = lv_img_create(ui_dateweather5);
	lv_img_set_src(ui_weathershow4, &ui_img_yin_png);

	lv_obj_set_width(ui_weathershow4, LV_SIZE_CONTENT);
	lv_obj_set_height(ui_weathershow4, LV_SIZE_CONTENT);

	lv_obj_set_x(ui_weathershow4, 0);
	lv_obj_set_y(ui_weathershow4, -30);

	lv_obj_set_align(ui_weathershow4, LV_ALIGN_CENTER);

	lv_obj_add_flag(ui_weathershow4, LV_OBJ_FLAG_ADV_HITTEST);
	lv_obj_clear_flag(ui_weathershow4, LV_OBJ_FLAG_SCROLLABLE);

	// ui_TextArea5

	ui_TextArea5 = lv_textarea_create(ui_dateweather5);

	lv_obj_set_width(ui_TextArea5, 50);
	lv_obj_set_height(ui_TextArea5, 30);

	lv_obj_set_x(ui_TextArea5, 0);
	lv_obj_set_y(ui_TextArea5, 40);

	lv_obj_set_align(ui_TextArea5, LV_ALIGN_CENTER);

//	if("" == "") lv_textarea_set_accepted_chars(ui_TextArea5, NULL);
//	else lv_textarea_set_accepted_chars(ui_TextArea5, "");

	lv_obj_set_style_text_color(ui_TextArea5,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_TextArea5, "7/22");
//	lv_textarea_set_placeholder_text(ui_TextArea5, "Placeholder...");
	lv_textarea_set_one_line(ui_TextArea5, true);

	lv_obj_clear_flag(ui_TextArea5, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_TextArea5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_TextArea5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_TextArea5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// ui_dateweather6

	ui_dateweather6 = lv_obj_create(ui_weatherpanelup);

	lv_obj_set_width(ui_dateweather6, 100);
	lv_obj_set_height(ui_dateweather6, 180);

	lv_obj_set_x(ui_dateweather6, 100);
	lv_obj_set_y(ui_dateweather6, 0);

	lv_obj_set_align(ui_dateweather6, LV_ALIGN_CENTER);

	lv_obj_clear_flag(ui_dateweather6, LV_OBJ_FLAG_SCROLLABLE);

	lv_obj_set_style_radius(ui_dateweather6, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_dateweather6, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_dateweather6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_dateweather6, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_dateweather6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_dateweather6, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

	// ui_weathershow5

	ui_weathershow5 = lv_img_create(ui_dateweather6);
	lv_img_set_src(ui_weathershow5, &ui_img_qing_png);

	lv_obj_set_width(ui_weathershow5, LV_SIZE_CONTENT);
	lv_obj_set_height(ui_weathershow5, LV_SIZE_CONTENT);

	lv_obj_set_x(ui_weathershow5, 0);
	lv_obj_set_y(ui_weathershow5, -30);

	lv_obj_set_align(ui_weathershow5, LV_ALIGN_CENTER);

	lv_obj_add_flag(ui_weathershow5, LV_OBJ_FLAG_ADV_HITTEST);
	lv_obj_clear_flag(ui_weathershow5, LV_OBJ_FLAG_SCROLLABLE);

	// ui_TextArea6

	ui_TextArea6 = lv_textarea_create(ui_dateweather6);

	lv_obj_set_width(ui_TextArea6, 50);
	lv_obj_set_height(ui_TextArea6, 30);

	lv_obj_set_x(ui_TextArea6, 0);
	lv_obj_set_y(ui_TextArea6, 40);

	lv_obj_set_align(ui_TextArea6, LV_ALIGN_CENTER);

//	if("" == "") lv_textarea_set_accepted_chars(ui_TextArea6, NULL);
//	else lv_textarea_set_accepted_chars(ui_TextArea6, "");

	lv_obj_set_style_text_color(ui_TextArea6,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_TextArea6, "7/23");
//	lv_textarea_set_placeholder_text(ui_TextArea6, "Placeholder...");
	lv_textarea_set_one_line(ui_TextArea6, true);

	lv_obj_clear_flag(ui_TextArea6, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_TextArea6, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_TextArea6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_TextArea6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// ui_dateweather7

	ui_dateweather7 = lv_obj_create(ui_weatherpanelup);

	lv_obj_set_width(ui_dateweather7, 100);
	lv_obj_set_height(ui_dateweather7, 180);

	lv_obj_set_x(ui_dateweather7, 300);
	lv_obj_set_y(ui_dateweather7, 0);

	lv_obj_set_align(ui_dateweather7, LV_ALIGN_CENTER);

	lv_obj_clear_flag(ui_dateweather7, LV_OBJ_FLAG_SCROLLABLE);

	lv_obj_set_style_radius(ui_dateweather7, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_dateweather7, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_dateweather7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_dateweather7, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_dateweather7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_dateweather7, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

	// ui_weathershow6

	ui_weathershow6 = lv_img_create(ui_dateweather7);
	lv_img_set_src(ui_weathershow6, &ui_img_wu_png);

	lv_obj_set_width(ui_weathershow6, LV_SIZE_CONTENT);
	lv_obj_set_height(ui_weathershow6, LV_SIZE_CONTENT);

	lv_obj_set_x(ui_weathershow6, 0);
	lv_obj_set_y(ui_weathershow6, -30);

	lv_obj_set_align(ui_weathershow6, LV_ALIGN_CENTER);

	lv_obj_add_flag(ui_weathershow6, LV_OBJ_FLAG_ADV_HITTEST);
	lv_obj_clear_flag(ui_weathershow6, LV_OBJ_FLAG_SCROLLABLE);

	// ui_TextArea7

	ui_TextArea7 = lv_textarea_create(ui_dateweather7);

	lv_obj_set_width(ui_TextArea7, 50);
	lv_obj_set_height(ui_TextArea7, 30);

	lv_obj_set_x(ui_TextArea7, 0);
	lv_obj_set_y(ui_TextArea7, 40);

	lv_obj_set_align(ui_TextArea7, LV_ALIGN_CENTER);

//	if("" == "") lv_textarea_set_accepted_chars(ui_TextArea7, NULL);
//	else lv_textarea_set_accepted_chars(ui_TextArea7, "");

	lv_obj_set_style_text_color(ui_TextArea7,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_TextArea7, "7/24");
//	lv_textarea_set_placeholder_text(ui_TextArea7, "Placeholder...");
	lv_textarea_set_one_line(ui_TextArea7, true);

	lv_obj_clear_flag(ui_TextArea7, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_TextArea7, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_TextArea7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_TextArea7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// ui_sunpanel

	ui_sunpanel = lv_obj_create(ui_WeatherScrPage);

	lv_obj_set_width(ui_sunpanel, 210);
	lv_obj_set_height(ui_sunpanel, 200);

	lv_obj_set_x(ui_sunpanel, -290);
	lv_obj_set_y(ui_sunpanel, 135);

	lv_obj_set_align(ui_sunpanel, LV_ALIGN_CENTER);

	lv_obj_clear_flag(ui_sunpanel, LV_OBJ_FLAG_SCROLLABLE);

	lv_obj_set_style_radius(ui_sunpanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_sunpanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_sunpanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_sunpanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_sunpanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_sunpanel, 1, LV_PART_MAIN | LV_STATE_DEFAULT);


	lv_sun_canvas_test(ui_sunpanel);
	
	
	// ui_preferencepanel

	ui_preferencepanel = lv_obj_create(ui_WeatherScrPage);

	lv_obj_set_width(ui_preferencepanel, 570);
	lv_obj_set_height(ui_preferencepanel, 200);

	lv_obj_set_x(ui_preferencepanel, 110);
	lv_obj_set_y(ui_preferencepanel, 135);

	lv_obj_set_align(ui_preferencepanel, LV_ALIGN_CENTER);

	lv_obj_clear_flag(ui_preferencepanel, LV_OBJ_FLAG_SCROLLABLE);

	lv_obj_set_style_radius(ui_preferencepanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_preferencepanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_preferencepanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_preferencepanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_preferencepanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_preferencepanel, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
	return ;
}



void weatherpageui_update()
{
	return ;
}
