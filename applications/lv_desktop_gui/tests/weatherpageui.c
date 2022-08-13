#include <weatherpageui.h>
#include <lvgl.h>
#include "dfs.h"
#include "fcntl.h"
#include "unistd.h"
#include <cJSON.h>
#include "guiconf.h"  

#include "lv_sun_canvas.h"

#define DBG_ENABLE
#define DBG_SECTION_NAME               "lvgl.weather"
#define DBG_LEVEL                      DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>

static lv_obj_t * ui_WeatherScrPage;

//static lv_obj_t * ui_upstatuspanel;
//static lv_obj_t * ui_locationlabel;
//static lv_obj_t * ui_Image19;
//static lv_obj_t * ui_TimeLabel;

static lv_obj_t * ui_weatherpanelup;

static lv_obj_t * ui_dateweather01;
static lv_obj_t * ui_weathershow01;
static lv_obj_t * ui_temp_text01;
static lv_obj_t * ui_weather_type_text01;
static lv_obj_t * ui_TextArea01;

static lv_obj_t * ui_dateweather02;
static lv_obj_t * ui_weathershow02;
static lv_obj_t * ui_temp_text02;
static lv_obj_t * ui_weather_type_text02;
static lv_obj_t * ui_TextArea02;

static lv_obj_t * ui_dateweather03;
static lv_obj_t * ui_weathershow03;
static lv_obj_t * ui_temp_text03;
static lv_obj_t * ui_weather_type_text03;
static lv_obj_t * ui_TextArea03;

static lv_obj_t * ui_dateweather04;
static lv_obj_t * ui_weathershow04;
static lv_obj_t * ui_temp_text04;
static lv_obj_t * ui_weather_type_text04;
static lv_obj_t * ui_TextArea04;

static lv_obj_t * ui_sunpanel;
static lv_obj_t * ui_preferencepanel;

//static lv_obj_t * ui_dateweather00;
static lv_obj_t * ui_weathershow00;
static lv_obj_t * ui_temp_text00;
static lv_obj_t * ui_weather_type_text00;
static lv_obj_t * ui_TextArea00;
static lv_obj_t * ui_weeklabel00;
static lv_obj_t * ui_noticelabel00;


#define WEATHER_ICON_QING     0
#define WEATHER_ICON_YIN      1
#define WEATHER_ICON_DUOYUN   2
#define WEATHER_ICON_XIAOYU   3
#define WEATHER_ICON_ZHONGYU  4
#define WEATHER_ICON_DAYU     5
#define WEATHER_ICON_BAOYU    6
#define WEATHER_ICON_DABAOYU  7
#define WEATHER_ICON_TEDABAOYU 8
#define WEATHER_ICON_ZHENYU   9
#define WEATHER_ICON_XIAOXUE  10
#define WEATHER_ICON_ZHONGXUE 11
#define WEATHER_ICON_DAXUE    12
#define WEATHER_ICON_BAOXUE   13
#define WEATHER_ICON_ZHENXUE  14
#define WEATHER_ICON_YUJIAXUE 15
#define WEATHER_ICON_SHACHENBAO 16
#define WEATHER_ICON_LZYBB    17
#define WEATHER_ICON_WU       18
#define WEATHER_ICON_LEIZHENYU 19

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



// 记录未来5天天气信息
weather_t weather5day[5];

LV_FONT_DECLARE(HarmonyOS_Sans_SC_Medium);


//void weatherpage_set_time_label(const char *time_str)
//{
//	if(ui_TimeLabel && time_str)
//	{
//		lv_label_set_text(ui_TimeLabel, time_str);
//	}
//}



																		

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

	// ui_dateweather01

	ui_dateweather01 = lv_obj_create(ui_weatherpanelup);

	lv_obj_set_width(ui_dateweather01, 100);
	lv_obj_set_height(ui_dateweather01, 200);

	lv_obj_set_x(ui_dateweather01, -300);
	lv_obj_set_y(ui_dateweather01, 0);

	lv_obj_set_align(ui_dateweather01, LV_ALIGN_CENTER);

	lv_obj_clear_flag(ui_dateweather01, LV_OBJ_FLAG_SCROLLABLE);

	lv_obj_set_style_radius(ui_dateweather01, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_dateweather01, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_dateweather01, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_dateweather01, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_dateweather01, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_dateweather01, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

	// ui_weathershow01

	ui_weathershow01 = lv_img_create(ui_dateweather01);
	lv_img_set_src(ui_weathershow01, icon_weather_array[WEATHER_ICON_QING]);

	lv_obj_set_width(ui_weathershow01, LV_SIZE_CONTENT);
	lv_obj_set_height(ui_weathershow01, LV_SIZE_CONTENT);

	lv_obj_set_x(ui_weathershow01, 0);
	lv_obj_set_y(ui_weathershow01, -62);

	lv_obj_set_align(ui_weathershow01, LV_ALIGN_CENTER);

	lv_obj_add_flag(ui_weathershow01, LV_OBJ_FLAG_ADV_HITTEST);
	lv_obj_clear_flag(ui_weathershow01, LV_OBJ_FLAG_SCROLLABLE);


	ui_temp_text01 = lv_textarea_create(ui_dateweather01);

	lv_obj_set_width(ui_temp_text01,95);
	lv_obj_set_height(ui_temp_text01,28);

	lv_obj_set_x(ui_temp_text01, 0);
	lv_obj_set_y(ui_temp_text01, 0);

	lv_obj_set_align(ui_temp_text01, LV_ALIGN_CENTER);

	lv_obj_set_style_text_color(ui_temp_text01,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_temp_text01, "21 ~ 30");
	lv_textarea_set_one_line(ui_temp_text01, true);

	lv_obj_clear_flag(ui_temp_text01, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_temp_text01, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_temp_text01, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_temp_text01, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	
	

	ui_weather_type_text01 = lv_textarea_create(ui_dateweather01);

	lv_obj_set_width(ui_weather_type_text01, 80);
	lv_obj_set_height(ui_weather_type_text01, 28);

	lv_obj_set_x(ui_weather_type_text01, 0);
	lv_obj_set_y(ui_weather_type_text01, 30);

	lv_obj_set_align(ui_weather_type_text01, LV_ALIGN_CENTER);

	lv_obj_set_style_text_color(ui_weather_type_text01,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_weather_type_text01, &HarmonyOS_Sans_SC_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_weather_type_text01, "晴");
	lv_textarea_set_one_line(ui_weather_type_text01, true);

	lv_obj_clear_flag(ui_weather_type_text01, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_weather_type_text01, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_weather_type_text01, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_weather_type_text01, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	
	// ui_TextArea01

	ui_TextArea01 = lv_textarea_create(ui_dateweather01);

	lv_obj_set_width(ui_TextArea01, 95);
	lv_obj_set_height(ui_TextArea01, 28);

	lv_obj_set_x(ui_TextArea01, 0);
	lv_obj_set_y(ui_TextArea01, 60);

	lv_obj_set_align(ui_TextArea01, LV_ALIGN_CENTER);

	lv_obj_set_style_text_color(ui_TextArea01,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_TextArea01, "7/21");
	lv_textarea_set_one_line(ui_TextArea01, true);

	lv_obj_clear_flag(ui_TextArea01, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_TextArea01, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_TextArea01, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_TextArea01, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	
	

	// ui_dateweather02

	ui_dateweather02 = lv_obj_create(ui_weatherpanelup);

	lv_obj_set_width(ui_dateweather02, 100);
	lv_obj_set_height(ui_dateweather02, 200);

	lv_obj_set_x(ui_dateweather02, -100);
	lv_obj_set_y(ui_dateweather02, 0);

	lv_obj_set_align(ui_dateweather02, LV_ALIGN_CENTER);

	lv_obj_clear_flag(ui_dateweather02, LV_OBJ_FLAG_SCROLLABLE);

	lv_obj_set_style_radius(ui_dateweather02, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_dateweather02, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_dateweather02, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_dateweather02, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_dateweather02, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_dateweather02, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

	// ui_weathershow02

	ui_weathershow02 = lv_img_create(ui_dateweather02);
	lv_img_set_src(ui_weathershow02, icon_weather_array[WEATHER_ICON_YIN]);

	lv_obj_set_width(ui_weathershow02, LV_SIZE_CONTENT);
	lv_obj_set_height(ui_weathershow02, LV_SIZE_CONTENT);

	lv_obj_set_x(ui_weathershow02, 0);
	lv_obj_set_y(ui_weathershow02, -62);

	lv_obj_set_align(ui_weathershow02, LV_ALIGN_CENTER);

	lv_obj_add_flag(ui_weathershow02, LV_OBJ_FLAG_ADV_HITTEST);
	lv_obj_clear_flag(ui_weathershow02, LV_OBJ_FLAG_SCROLLABLE);


	ui_temp_text02 = lv_textarea_create(ui_dateweather02);

	lv_obj_set_width(ui_temp_text02,95);
	lv_obj_set_height(ui_temp_text02,28);

	lv_obj_set_x(ui_temp_text02, 0);
	lv_obj_set_y(ui_temp_text02, 0);

	lv_obj_set_align(ui_temp_text02, LV_ALIGN_CENTER);

	lv_obj_set_style_text_color(ui_temp_text02,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_temp_text02, "24 ~ 32");
	lv_textarea_set_one_line(ui_temp_text02, true);

	lv_obj_clear_flag(ui_temp_text02, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_temp_text02, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_temp_text02, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_temp_text02, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	
	

	ui_weather_type_text02 = lv_textarea_create(ui_dateweather02);

	lv_obj_set_width(ui_weather_type_text02, 95);
	lv_obj_set_height(ui_weather_type_text02, 28);

	lv_obj_set_x(ui_weather_type_text02, 0);
	lv_obj_set_y(ui_weather_type_text02, 30);

	lv_obj_set_align(ui_weather_type_text02, LV_ALIGN_CENTER);

	lv_obj_set_style_text_color(ui_weather_type_text02,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_weather_type_text02, &HarmonyOS_Sans_SC_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_weather_type_text02, "阴");
	lv_textarea_set_one_line(ui_weather_type_text02, true);

	lv_obj_clear_flag(ui_weather_type_text02, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_weather_type_text02, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_weather_type_text02, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_weather_type_text02, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	

	// ui_TextArea02

	ui_TextArea02 = lv_textarea_create(ui_dateweather02);

	lv_obj_set_width(ui_TextArea02, 95);
	lv_obj_set_height(ui_TextArea02, 30);

	lv_obj_set_x(ui_TextArea02, 0);
	lv_obj_set_y(ui_TextArea02, 60);

	lv_obj_set_align(ui_TextArea02, LV_ALIGN_CENTER);


	lv_obj_set_style_text_color(ui_TextArea02,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_TextArea02, "7/22");
	lv_textarea_set_one_line(ui_TextArea02, true);

	lv_obj_clear_flag(ui_TextArea02, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_TextArea02, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_TextArea02, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_TextArea02, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// ui_dateweather03

	ui_dateweather03 = lv_obj_create(ui_weatherpanelup);

	lv_obj_set_width(ui_dateweather03, 100);
	lv_obj_set_height(ui_dateweather03, 200);

	lv_obj_set_x(ui_dateweather03, 100);
	lv_obj_set_y(ui_dateweather03, 0);

	lv_obj_set_align(ui_dateweather03, LV_ALIGN_CENTER);

	lv_obj_clear_flag(ui_dateweather03, LV_OBJ_FLAG_SCROLLABLE);

	lv_obj_set_style_radius(ui_dateweather03, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_dateweather03, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_dateweather03, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_dateweather03, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_dateweather03, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_dateweather03, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

	// ui_weathershow03

	ui_weathershow03 = lv_img_create(ui_dateweather03);
	lv_img_set_src(ui_weathershow03, icon_weather_array[WEATHER_ICON_DUOYUN]);

	lv_obj_set_width(ui_weathershow03, LV_SIZE_CONTENT);
	lv_obj_set_height(ui_weathershow03, LV_SIZE_CONTENT);

	lv_obj_set_x(ui_weathershow03, 0);
	lv_obj_set_y(ui_weathershow03, -62);

	lv_obj_set_align(ui_weathershow03, LV_ALIGN_CENTER);

	lv_obj_add_flag(ui_weathershow03, LV_OBJ_FLAG_ADV_HITTEST);
	lv_obj_clear_flag(ui_weathershow03, LV_OBJ_FLAG_SCROLLABLE);


	ui_temp_text03 = lv_textarea_create(ui_dateweather03);

	lv_obj_set_width(ui_temp_text03,95);
	lv_obj_set_height(ui_temp_text03,28);

	lv_obj_set_x(ui_temp_text03, 0);
	lv_obj_set_y(ui_temp_text03, 0);

	lv_obj_set_align(ui_temp_text03, LV_ALIGN_CENTER);

	lv_obj_set_style_text_color(ui_temp_text03,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_temp_text03, "20 ~ 35");
	lv_textarea_set_one_line(ui_temp_text03, true);

	lv_obj_clear_flag(ui_temp_text03, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_temp_text03, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_temp_text03, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_temp_text03, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	
	

	ui_weather_type_text03 = lv_textarea_create(ui_dateweather03);

	lv_obj_set_width(ui_weather_type_text03, 95);
	lv_obj_set_height(ui_weather_type_text03, 28);

	lv_obj_set_x(ui_weather_type_text03, 0);
	lv_obj_set_y(ui_weather_type_text03, 30);

	lv_obj_set_align(ui_weather_type_text03, LV_ALIGN_CENTER);

	lv_obj_set_style_text_color(ui_weather_type_text03,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_weather_type_text03, &HarmonyOS_Sans_SC_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_weather_type_text03, "小雨");
	lv_textarea_set_one_line(ui_weather_type_text03, true);

	lv_obj_clear_flag(ui_weather_type_text03, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_weather_type_text03, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_weather_type_text03, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_weather_type_text03, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	


	// ui_TextArea03

	ui_TextArea03 = lv_textarea_create(ui_dateweather03);

	lv_obj_set_width(ui_TextArea03, 95);
	lv_obj_set_height(ui_TextArea03, 30);

	lv_obj_set_x(ui_TextArea03, 0);
	lv_obj_set_y(ui_TextArea03, 60);

	lv_obj_set_align(ui_TextArea03, LV_ALIGN_CENTER);


	lv_obj_set_style_text_color(ui_TextArea03,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_TextArea03, "7/23");
	lv_textarea_set_one_line(ui_TextArea03, true);

	lv_obj_clear_flag(ui_TextArea03, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_TextArea03, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_TextArea03, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_TextArea03, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// ui_dateweather04

	ui_dateweather04 = lv_obj_create(ui_weatherpanelup);

	lv_obj_set_width(ui_dateweather04, 100);
	lv_obj_set_height(ui_dateweather04, 200);

	lv_obj_set_x(ui_dateweather04, 300);
	lv_obj_set_y(ui_dateweather04, 0);

	lv_obj_set_align(ui_dateweather04, LV_ALIGN_CENTER);

	lv_obj_clear_flag(ui_dateweather04, LV_OBJ_FLAG_SCROLLABLE);

	lv_obj_set_style_radius(ui_dateweather04, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_dateweather04, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_dateweather04, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_dateweather04, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_dateweather04, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_dateweather04, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

	// ui_weathershow04

	ui_weathershow04 = lv_img_create(ui_dateweather04);
	lv_img_set_src(ui_weathershow04, &ui_img_wu_png);

	lv_obj_set_width(ui_weathershow04, LV_SIZE_CONTENT);
	lv_obj_set_height(ui_weathershow04, LV_SIZE_CONTENT);

	lv_obj_set_x(ui_weathershow04, 0);
	lv_obj_set_y(ui_weathershow04, -62);

	lv_obj_set_align(ui_weathershow04, LV_ALIGN_CENTER);

	lv_obj_add_flag(ui_weathershow04, LV_OBJ_FLAG_ADV_HITTEST);
	lv_obj_clear_flag(ui_weathershow04, LV_OBJ_FLAG_SCROLLABLE);


	ui_temp_text04 = lv_textarea_create(ui_dateweather04);

	lv_obj_set_width(ui_temp_text04,95);
	lv_obj_set_height(ui_temp_text04,28);

	lv_obj_set_x(ui_temp_text04, 0);
	lv_obj_set_y(ui_temp_text04, 0);

	lv_obj_set_align(ui_temp_text04, LV_ALIGN_CENTER);

	lv_obj_set_style_text_color(ui_temp_text04,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_temp_text04, "20 ~ 35");
	lv_textarea_set_one_line(ui_temp_text04, true);

	lv_obj_clear_flag(ui_temp_text04, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_temp_text04, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_temp_text04, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_temp_text04, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	
	

	ui_weather_type_text04 = lv_textarea_create(ui_dateweather04);

	lv_obj_set_width(ui_weather_type_text04, 95);
	lv_obj_set_height(ui_weather_type_text04, 28);

	lv_obj_set_x(ui_weather_type_text04, 0);
	lv_obj_set_y(ui_weather_type_text04, 30);

	lv_obj_set_align(ui_weather_type_text04, LV_ALIGN_CENTER);

	lv_obj_set_style_text_color(ui_weather_type_text04,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_weather_type_text04, &HarmonyOS_Sans_SC_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_weather_type_text04, "晴");
	lv_textarea_set_one_line(ui_weather_type_text04, true);

	lv_obj_clear_flag(ui_weather_type_text04, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_weather_type_text04, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_weather_type_text04, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_weather_type_text04, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	
	// ui_TextArea04

	ui_TextArea04 = lv_textarea_create(ui_dateweather04);

	lv_obj_set_width(ui_TextArea04, 95);
	lv_obj_set_height(ui_TextArea04, 30);

	lv_obj_set_x(ui_TextArea04, 0);
	lv_obj_set_y(ui_TextArea04, 60);

	lv_obj_set_align(ui_TextArea04, LV_ALIGN_CENTER);


	lv_obj_set_style_text_color(ui_TextArea04,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_TextArea04, "7/24");
	lv_textarea_set_one_line(ui_TextArea04, true);

	lv_obj_clear_flag(ui_TextArea04, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_TextArea04, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_TextArea04, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_TextArea04, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

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


	lv_sun_canvas_create(ui_sunpanel);
	
	// ui_preferencepanel 显示当天的天气信息
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



	// ui_weathershow00

	ui_weathershow00 = lv_img_create(ui_preferencepanel);
	lv_img_set_src(ui_weathershow00, &ui_img_qing_png);

	lv_obj_set_width(ui_weathershow00, LV_SIZE_CONTENT);
	lv_obj_set_height(ui_weathershow00, LV_SIZE_CONTENT);

	lv_obj_align(ui_weathershow00, LV_ALIGN_TOP_LEFT,10,30);

	lv_obj_add_flag(ui_weathershow00, LV_OBJ_FLAG_ADV_HITTEST);
	lv_obj_clear_flag(ui_weathershow00, LV_OBJ_FLAG_SCROLLABLE);

//  ui_temp_text00;
//  ui_weather_type_text00;


	ui_temp_text00 = lv_textarea_create(ui_preferencepanel);

	lv_obj_set_width(ui_temp_text00,95);
	lv_obj_set_height(ui_temp_text00,28);

	lv_obj_align_to(ui_temp_text00,ui_weathershow00,LV_ALIGN_OUT_BOTTOM_MID,0,0);

	lv_obj_set_style_text_color(ui_temp_text00,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_temp_text00, "20 ~ 35");
	lv_textarea_set_one_line(ui_temp_text00, true);

	lv_obj_clear_flag(ui_temp_text00, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_temp_text00, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_temp_text00, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_temp_text00, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	
	

	ui_weather_type_text00 = lv_textarea_create(ui_preferencepanel);

	lv_obj_set_width(ui_weather_type_text00, 95);
	lv_obj_set_height(ui_weather_type_text00, 28);

	lv_obj_align_to(ui_weather_type_text00,ui_temp_text00,LV_ALIGN_OUT_BOTTOM_MID,0,-20);

	lv_obj_set_style_text_color(ui_weather_type_text00,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_weather_type_text00, &HarmonyOS_Sans_SC_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_weather_type_text00, "晴");
	lv_textarea_set_one_line(ui_weather_type_text00, true);

	lv_obj_clear_flag(ui_weather_type_text00, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_weather_type_text00, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_weather_type_text00, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_weather_type_text00, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	
	
//  ui_TextArea00;
//  ui_weeklabel00;

	// ui_TextArea00

	ui_TextArea00 = lv_textarea_create(ui_preferencepanel);

	lv_obj_set_width(ui_TextArea00, 95);
	lv_obj_set_height(ui_TextArea00, 30);

	lv_obj_align_to(ui_TextArea00,ui_weathershow00,LV_ALIGN_OUT_RIGHT_TOP,10,-10);


	lv_obj_set_style_text_color(ui_TextArea00,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_TextArea00, "7/24");
	lv_textarea_set_one_line(ui_TextArea00, true);

	lv_obj_clear_flag(ui_TextArea00, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_TextArea00, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_TextArea00, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_TextArea00, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// ui_weeklabel00

	ui_weeklabel00 = lv_textarea_create(ui_preferencepanel);

	lv_obj_set_width(ui_weeklabel00, 95);
	lv_obj_set_height(ui_weeklabel00, 30);

	lv_obj_align_to(ui_weeklabel00,ui_weathershow00,LV_ALIGN_OUT_RIGHT_MID,10,0);


	lv_obj_set_style_text_color(ui_weeklabel00,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_weeklabel00, &HarmonyOS_Sans_SC_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_weeklabel00, "星期一");
	lv_textarea_set_one_line(ui_weeklabel00, true);

	lv_obj_clear_flag(ui_weeklabel00, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_weeklabel00, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_weeklabel00, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_weeklabel00, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	
	ui_noticelabel00 = lv_textarea_create(ui_preferencepanel);

	lv_obj_set_width(ui_noticelabel00, LV_SIZE_CONTENT);
	lv_obj_set_height(ui_noticelabel00, LV_SIZE_CONTENT);

	lv_obj_align_to(ui_noticelabel00,ui_weathershow00,LV_ALIGN_OUT_RIGHT_BOTTOM,10,20);


	lv_obj_set_style_text_color(ui_noticelabel00,lv_color_make(255,255,255),LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_noticelabel00, &HarmonyOS_Sans_SC_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);
//	lv_textarea_set_text(ui_noticelabel00, "星期一");
	lv_textarea_set_one_line(ui_noticelabel00, true);

	lv_obj_clear_flag(ui_noticelabel00, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
										LV_OBJ_FLAG_SCROLL_CHAIN);

	lv_obj_set_style_bg_color(ui_noticelabel00, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_noticelabel00, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_noticelabel00, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	
	
	time_t now;
	struct tm *p;
	now = time(RT_NULL);
	p = localtime(&now); 
	weatherpageui_update(p);
	
	return ;
}

const void *get_weather_icon(const char *weather_type_str)
{

	if(weather_type_str)
	{

		if(0 == rt_strcmp(weather_type_str,"晴"))
		{

			return &ui_img_qing_png;
		}
		else if(0 == rt_strcmp(weather_type_str,"阴"))
		{

			return &ui_img_yin_png;
		}
		else if(0 == rt_strcmp(weather_type_str,"多云"))
		{
			return &ui_img_duoyun_png;
		}
		else if(0 == rt_strcmp(weather_type_str,"小雨"))
		{
			return &ui_img_xiaoyu_png;
		}
		else if(0 == rt_strcmp(weather_type_str,"中雨"))
		{
			return &ui_img_zhongyu_png;
		}
		else if(0 == rt_strcmp(weather_type_str,"大雨"))
		{
			return &ui_img_dayu_png;
		}
		else if(0 == rt_strcmp(weather_type_str,"暴雨"))
		{
			return &ui_img_baoyu_png;
		}
		else if(0 == rt_strcmp(weather_type_str,"大暴雨"))
		{
			return &ui_img_dabaoyu_png;
		}
		else if(0 == rt_strcmp(weather_type_str,"特大暴雨"))
		{
			return &ui_img_tedabaoyu_png;
		}
		else if(0 == rt_strcmp(weather_type_str,"阵雨"))
		{
			return &ui_img_zhenyu_png;
		}
		else if(0 == rt_strcmp(weather_type_str,"小雪"))
		{
			return &ui_img_xiaoxue_png;
		}
		else if(0 == rt_strcmp(weather_type_str,"中雪"))
		{
			return &ui_img_zhongxue_png;
		}
		else if(0 == rt_strcmp(weather_type_str,"大雪"))
		{
			return &ui_img_xiaoyu_png;
		}
		else if(0 == rt_strcmp(weather_type_str,"暴雪"))
		{
			return &ui_img_baoxue_png;
		}
		else if(0 == rt_strcmp(weather_type_str,"阵雪"))
		{
			return &ui_img_zhenxue_png;
		}
		else if(0 == rt_strcmp(weather_type_str,"雨夹雪"))
		{
			return &ui_img_yujiaxue_png;
		}
		else if(0 == rt_strcmp(weather_type_str,"沙尘暴"))
		{
			return &ui_img_shachenbao_png;
		}
		else if(0 == rt_strcmp(weather_type_str,"雷阵雨冰雹"))
		{
			return &ui_img_leizhenyubingbao_png;
		}
		else if(0 == rt_strcmp(weather_type_str,"雾"))
		{
			return &ui_img_wu_png;
		}
		else if(0 == rt_strcmp(weather_type_str,"雷阵雨"))
		{
			return &ui_img_leizhenyu_png;
		}
		else
		{
			return RT_NULL;
		}
	}
	
}



void weatherpageui_update(struct tm *p)
{
	int sun_i;
	char tempstr[20];
	// 更新天气界面
	
	// 更新天气信息
	
	lv_img_set_src(ui_weathershow00, get_weather_icon(weather5day[0].weather_type));
	rt_memset(tempstr,0,20);
	rt_sprintf(tempstr,"%s ~ %s",weather5day[0].temp_low,weather5day[0].temp_high);
	lv_textarea_set_text(ui_temp_text00, tempstr);
	lv_textarea_set_text(ui_weather_type_text00,weather5day[0].weather_type);
	lv_textarea_set_text(ui_TextArea00, weather5day[0].date);
	lv_textarea_set_text(ui_weeklabel00, weather5day[0].week);
	lv_textarea_set_text(ui_noticelabel00, weather5day[0].notice);

	
	
	lv_img_set_src(ui_weathershow01, get_weather_icon(weather5day[1].weather_type));
	rt_memset(tempstr,0,20);
	rt_sprintf(tempstr,"%s ~ %s",weather5day[1].temp_low,weather5day[1].temp_high);
	lv_textarea_set_text(ui_temp_text01, tempstr);
	lv_textarea_set_text(ui_weather_type_text01,weather5day[1].weather_type);
	lv_textarea_set_text(ui_TextArea01, weather5day[1].date);
	
	
	lv_img_set_src(ui_weathershow02,get_weather_icon(weather5day[2].weather_type));
	rt_memset(tempstr,0,20);
	rt_sprintf(tempstr,"%s ~ %s",weather5day[2].temp_low,weather5day[2].temp_high);
	lv_textarea_set_text(ui_temp_text02, tempstr);
	lv_textarea_set_text(ui_weather_type_text02, weather5day[2].weather_type);
	lv_textarea_set_text(ui_TextArea02, weather5day[2].date);
	
	lv_img_set_src(ui_weathershow03, get_weather_icon(weather5day[3].weather_type));
	rt_memset(tempstr,0,20);
	rt_sprintf(tempstr,"%s ~ %s",weather5day[3].temp_low,weather5day[3].temp_high);
	lv_textarea_set_text(ui_temp_text03, tempstr);
	lv_textarea_set_text(ui_weather_type_text03, weather5day[3].weather_type);
	lv_textarea_set_text(ui_TextArea03, weather5day[3].date);
	
	lv_img_set_src(ui_weathershow04, get_weather_icon(weather5day[4].weather_type));
	rt_memset(tempstr,0,20);
	rt_sprintf(tempstr,"%s ~ %s",weather5day[4].temp_low,weather5day[4].temp_high);
	lv_textarea_set_text(ui_temp_text04, tempstr);
	lv_textarea_set_text(ui_weather_type_text04, weather5day[4].weather_type);
	lv_textarea_set_text(ui_TextArea04, weather5day[4].date);
	

	//根据当前时间显示太阳位置
	if(p->tm_hour < 5)
	{
		lv_sun_set_position(0);
	}
	else if(p->tm_hour > 5 && p->tm_hour < 20)
	{
		sun_i = (int)(((p->tm_hour-5)/15.0)*180);
//		rt_kprintf("sun_i %d\n",sun_i);
		lv_sun_set_position(sun_i);
	}
	else if(p->tm_hour >= 20)
	{
		lv_sun_set_position(180);
	}
	

	// 更新当天的日出日落时间
	lv_sun_canvas_set_text(weather5day[0].sunrise,weather5day[0].sunset);
	return ;
}




// -----------------------------------------------------------------------------------------------------------

void weather_info_print()
{
	uint16_t i =0;
	printf("-------- weather info show -----------\n");
	for(i=0;i<5;i++)
	{
			rt_kprintf("date          : %s\n",weather5day[i].date);
			rt_kprintf("week          : %s\n",weather5day[i].week);
			rt_kprintf("weather_type  : %s\n",weather5day[i].weather_type);
			rt_kprintf("temp_high     : %s\n",weather5day[i].temp_high);
			rt_kprintf("temp_low      : %s\n",weather5day[i].temp_low);
			rt_kprintf("temp_low str len %d\n",rt_strlen(weather5day[i].temp_low));
			rt_kprintf("sunrise       : %s\n",weather5day[i].sunrise);
			rt_kprintf("sunset        : %s\n",weather5day[i].sunset);
			rt_kprintf("notice        : %s\n",weather5day[i].notice);
	}
	printf("----------------------------------------\n");
}


// 从 sd 卡中读取出来天气信息，初始化天气信息数组
// 天气信息初始化
void weather_info_init()
{
		const char *newsfile="/tmp/weather";
		int read_len;
		int total_length;
		int ret;
		int fd;
		int news_num=0;
		uint16_t i;
		struct stat file_stat;
		char *weather_info_buffer = RT_NULL; 
    cJSON *root = RT_NULL, *object = RT_NULL, *item = RT_NULL;
		cJSON *cityInfo_obj = RT_NULL;
		cJSON *dataobj = RT_NULL;
		cJSON *JsonArray =RT_NULL;
		uint16_t jsonarray_size =0;
		uint16_t parse_array_size =5;
		ret = stat(newsfile, &file_stat);
		if(ret == 0)
		{
			total_length = file_stat.st_size;
			rt_kprintf("%s file size = %d\n", newsfile,file_stat.st_size);
		}
    else
			rt_kprintf("%s file not fonud\n",newsfile);
		
		
		fd = open(newsfile, O_RDONLY , 0);
		if (fd < 0)
		{
				LOG_E("get file failed, open file(%s) error.", newsfile);
				return ;
		}
	
		weather_info_buffer = (char *)rt_malloc(total_length*sizeof(char));
		if (weather_info_buffer == RT_NULL)
		{
				LOG_E("news_mem_buffer malloc failed \n");
				goto __exit;
		}
		read_len = read(fd,weather_info_buffer,total_length);
		LOG_I("read data len from file %s :%d\n",newsfile,read_len);
		
		
	
		root = cJSON_Parse((const char *)weather_info_buffer);
    if (!root)
    {
        rt_kprintf("No memory for cJSON root!\n");
        return;
    }
		
		//LOG_I("------------------------------------------------------\n");
		//LOG_I("  parse news  \n");
		dataobj = cJSON_GetObjectItem(root,"data");
		
		JsonArray = cJSON_GetObjectItem(dataobj,"forecast");
		
		jsonarray_size = cJSON_GetArraySize(JsonArray);
		if(jsonarray_size>5)
		{
			parse_array_size =5;
		}
		else
		{
			parse_array_size = jsonarray_size;
		}
		
		for(i=0;i<parse_array_size;i++)
		{
			rt_memset(weather5day[i].date,0,20);
			rt_memset(weather5day[i].week,0,20);
			rt_memset(weather5day[i].weather_type,0,20);
			rt_memset(weather5day[i].temp_high,0,20);
			rt_memset(weather5day[i].temp_low,0,20);
			rt_memset(weather5day[i].sunrise,0,10);
			rt_memset(weather5day[i].sunset,0,10);
			rt_memset(weather5day[i].notice,0,100);
		}
		
		// 最多解析5组出来
		for(i=0;i<parse_array_size;i++)
		{
			object = cJSON_GetArrayItem(JsonArray,i);
			
			item = cJSON_GetObjectItem(object, "ymd");
			//rt_kprintf("\n date   :%s \n", item->valuestring);
			rt_strcpy(weather5day[i].date,item->valuestring);

			item = cJSON_GetObjectItem(object, "week");
			//rt_kprintf("\n week   :%s \n", item->valuestring);
			rt_strcpy(weather5day[i].week,item->valuestring);
			
			item = cJSON_GetObjectItem(object, "type");
			//rt_kprintf("\n type   :%s \n", item->valuestring);
			rt_strcpy(weather5day[i].weather_type,item->valuestring);
			
			item = cJSON_GetObjectItem(object, "high");
			//rt_kprintf("\n high   :%s \n", item->valuestring);
			rt_strcpy(weather5day[i].temp_high,(char *)(item->valuestring+6));
			
			item = cJSON_GetObjectItem(object, "low");
			//rt_kprintf("\n low   :%s \n", item->valuestring);
			rt_strcpy(weather5day[i].temp_low,(char *)(item->valuestring+6));
			
			item = cJSON_GetObjectItem(object, "sunrise");
			//rt_kprintf("\n sunrise   :%s \n", item->valuestring);
			rt_strcpy(weather5day[i].sunrise,item->valuestring);
			
			item = cJSON_GetObjectItem(object, "sunset");
			//rt_kprintf("\n sunset   :%s \n", item->valuestring);
			rt_strcpy(weather5day[i].sunset,item->valuestring);
			
			item = cJSON_GetObjectItem(object, "notice");
			//rt_kprintf("\n notice   :%s \n", item->valuestring);
			rt_strcpy(weather5day[i].notice,item->valuestring);
			
		}
__exit:
		if(weather_info_buffer)
		{
			rt_free(weather_info_buffer);
		}
		if (root != RT_NULL)
		{
			cJSON_Delete(root);
		}
		if(fd)
		{
			close(fd);
		}
		return ;
}
