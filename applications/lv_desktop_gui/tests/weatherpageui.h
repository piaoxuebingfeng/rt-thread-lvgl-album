#ifndef _WEATHERPAGEUI_H__
#define _WEATHERPAGEUI_H__
#include <sys/time.h>
#include <ui_icon_weather_style1.h>

// 定义天气信息结构体

typedef struct weather_s weather_t;

struct weather_s
{
	char date[20];          // 日期
	char week[20];          // 星期
	char weather_type[20];  // 天气类型
	char temp_high[20];     // 高温
	char temp_low[20];      // 低温
	char sunrise[10];       // 日出时间
	char sunset[10];        // 日落时间
	char notice[100];       // 提示信息
};


void weatherpageui_update(struct tm *p);
void weatherpageui_init(lv_obj_t *parent);


void weather_info_init();
void weather_info_print();


#endif //_WEATHERPAGEUI_H__