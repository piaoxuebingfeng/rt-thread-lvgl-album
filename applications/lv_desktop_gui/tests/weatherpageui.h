#ifndef _WEATHERPAGEUI_H__
#define _WEATHERPAGEUI_H__
#include <sys/time.h>
#include <ui_icon_weather_style1.h>

// ����������Ϣ�ṹ��

typedef struct weather_s weather_t;

struct weather_s
{
	char date[20];          // ����
	char week[20];          // ����
	char weather_type[20];  // ��������
	char temp_high[20];     // ����
	char temp_low[20];      // ����
	char sunrise[10];       // �ճ�ʱ��
	char sunset[10];        // ����ʱ��
	char notice[100];       // ��ʾ��Ϣ
};


void weatherpageui_update(struct tm *p);
void weatherpageui_init(lv_obj_t *parent);


void weather_info_init();
void weather_info_print();


#endif //_WEATHERPAGEUI_H__