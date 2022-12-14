#include "lv_mycalendar.h"
#include <stdlib.h>

// LV_FONT_DECLARE(lv_font_montserrat_48)
LV_FONT_DECLARE(HarmonyOS_Sans_SC_Medium);


//#####################################################################################################

//static unsigned int LunarCalendarDay;
//static unsigned int LunarCalendarTable[199] =
//{
//	0x04AE53,0x0A5748,0x5526BD,0x0D2650,0x0D9544,0x46AAB9,0x056A4D,0x09AD42,0x24AEB6,0x04AE4A,/*1901-1910*/
//	0x6A4DBE,0x0A4D52,0x0D2546,0x5D52BA,0x0B544E,0x0D6A43,0x296D37,0x095B4B,0x749BC1,0x049754,/*1911-1920*/
//	0x0A4B48,0x5B25BC,0x06A550,0x06D445,0x4ADAB8,0x02B64D,0x095742,0x2497B7,0x04974A,0x664B3E,/*1921-1930*/
//	0x0D4A51,0x0EA546,0x56D4BA,0x05AD4E,0x02B644,0x393738,0x092E4B,0x7C96BF,0x0C9553,0x0D4A48,/*1931-1940*/
//	0x6DA53B,0x0B554F,0x056A45,0x4AADB9,0x025D4D,0x092D42,0x2C95B6,0x0A954A,0x7B4ABD,0x06CA51,/*1941-1950*/
//	0x0B5546,0x555ABB,0x04DA4E,0x0A5B43,0x352BB8,0x052B4C,0x8A953F,0x0E9552,0x06AA48,0x6AD53C,/*1951-1960*/
//	0x0AB54F,0x04B645,0x4A5739,0x0A574D,0x052642,0x3E9335,0x0D9549,0x75AABE,0x056A51,0x096D46,/*1961-1970*/
//	0x54AEBB,0x04AD4F,0x0A4D43,0x4D26B7,0x0D254B,0x8D52BF,0x0B5452,0x0B6A47,0x696D3C,0x095B50,/*1971-1980*/
//	0x049B45,0x4A4BB9,0x0A4B4D,0xAB25C2,0x06A554,0x06D449,0x6ADA3D,0x0AB651,0x093746,0x5497BB,/*1981-1990*/
//	0x04974F,0x064B44,0x36A537,0x0EA54A,0x86B2BF,0x05AC53,0x0AB647,0x5936BC,0x092E50,0x0C9645,/*1991-2000*/
//	0x4D4AB8,0x0D4A4C,0x0DA541,0x25AAB6,0x056A49,0x7AADBD,0x025D52,0x092D47,0x5C95BA,0x0A954E,/*2001-2010*/
//	0x0B4A43,0x4B5537,0x0AD54A,0x955ABF,0x04BA53,0x0A5B48,0x652BBC,0x052B50,0x0A9345,0x474AB9,/*2011-2020*/
//	0x06AA4C,0x0AD541,0x24DAB6,0x04B64A,0x69573D,0x0A4E51,0x0D2646,0x5E933A,0x0D534D,0x05AA43,/*2021-2030*/
//	0x36B537,0x096D4B,0xB4AEBF,0x04AD53,0x0A4D48,0x6D25BC,0x0D254F,0x0D5244,0x5DAA38,0x0B5A4C,/*2031-2040*/
//	0x056D41,0x24ADB6,0x049B4A,0x7A4BBE,0x0A4B51,0x0AA546,0x5B52BA,0x06D24E,0x0ADA42,0x355B37,/*2041-2050*/
//	0x09374B,0x8497C1,0x049753,0x064B48,0x66A53C,0x0EA54F,0x06B244,0x4AB638,0x0AAE4C,0x092E42,/*2051-2060*/
//	0x3C9735,0x0C9649,0x7D4ABD,0x0D4A51,0x0DA545,0x55AABA,0x056A4E,0x0A6D43,0x452EB7,0x052D4B,/*2061-2070*/
//	0x8A95BF,0x0A9553,0x0B4A47,0x6B553B,0x0AD54F,0x055A45,0x4A5D38,0x0A5B4C,0x052B42,0x3A93B6,/*2071-2080*/
//	0x069349,0x7729BD,0x06AA51,0x0AD546,0x54DABA,0x04B64E,0x0A5743,0x452738,0x0D264A,0x8E933E,/*2081-2090*/
//	0x0D5252,0x0DAA47,0x66B53B,0x056D4F,0x04AE45,0x4A4EB9,0x0A4D4C,0x0D1541,0x2D92B5          /*2091-2099*/
//};
//static int MonthAdd[12] = {0,31,59,90,120,151,181,212,243,273,304,334};



//static int LunarCalendar(int year,int month,int day)
//{
//	int Spring_NY,Sun_NY,StaticDayCount;
//	int index,flag;
//	//Spring_NY ???????????????????????????????????????
//	//Sun_NY ??????????????????????????????????????????
//	if ( ((LunarCalendarTable[year-1901] & 0x0060) >> 5) == 1)
//		Spring_NY = (LunarCalendarTable[year-1901] & 0x001F) - 1;
//	else
//		Spring_NY = (LunarCalendarTable[year-1901] & 0x001F) - 1 + 31;
//	Sun_NY = MonthAdd[month-1] + day - 1;
//	if ( (!(year % 4)) && (month > 2))
//		Sun_NY++;
//	//StaticDayCount???????????????????????? 29 ???30
//	//index ????????????????????????????????????
//	//flag ????????????????????????????????????
//	//??????????????????????????????????????????
//	if (Sun_NY >= Spring_NY)//??????????????????????????????????????????
//	{
//		Sun_NY -= Spring_NY;
//		month = 1;
//		index = 1;
//		flag = 0;
//		if ( ( LunarCalendarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)
//			StaticDayCount = 29;
//		else
//			StaticDayCount = 30;
//		while (Sun_NY >= StaticDayCount)
//		{
//			Sun_NY -= StaticDayCount;
//			index++;
//			if (month == ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20) )
//			{
//				flag = ~flag;
//				if (flag == 0)
//					month++;
//			}
//			else
//				month++;
//			if ( ( LunarCalendarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)
//				StaticDayCount=29;
//			else
//				StaticDayCount=30;
//		}
//		day = Sun_NY + 1;
//	}
//	else //?????????????????????
//	{
//		Spring_NY -= Sun_NY;
//		year--;
//		month = 12;
//		if ( ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20) == 0)
//			index = 12;
//		else
//			index = 13;
//		flag = 0;
//		if ( ( LunarCalendarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)
//			StaticDayCount = 29;
//		else
//			StaticDayCount = 30;
//		while (Spring_NY > StaticDayCount)
//		{
//			Spring_NY -= StaticDayCount;
//			index--;
//			if (flag == 0)
//				month--;
//			if (month == ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20))
//				flag = ~flag;
//			if ( ( LunarCalendarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)
//				StaticDayCount = 29;
//			else
//				StaticDayCount = 30;
//		}
//		day = StaticDayCount - Spring_NY + 1;
//	}
//	LunarCalendarDay |= day;
//	LunarCalendarDay |= (month << 6);
//	if (month == ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20))
//		return 1;
//	else
//		return 0;
//}

//#####################################################################################################
typedef struct {
    int year;
    int month;
    int day;
    int reserved;
} Mydate;


Mydate toSolar(Mydate lunar);
Mydate toLunar(Mydate solar);

Mydate toLunar_fromdate(uint32_t year,uint32_t month,uint32_t day);




unsigned int lunar200y[199] = {
    0x04AE53,0x0A5748,0x5526BD,0x0D2650,0x0D9544,0x46AAB9,0x056A4D,0x09AD42,0x24AEB6,0x04AE4A,/*1901-1910*/
    0x6A4DBE,0x0A4D52,0x0D2546,0x5D52BA,0x0B544E,0x0D6A43,0x296D37,0x095B4B,0x749BC1,0x049754,/*1911-1920*/
    0x0A4B48,0x5B25BC,0x06A550,0x06D445,0x4ADAB8,0x02B64D,0x095742,0x2497B7,0x04974A,0x664B3E,/*1921-1930*/
    0x0D4A51,0x0EA546,0x56D4BA,0x05AD4E,0x02B644,0x393738,0x092E4B,0x7C96BF,0x0C9553,0x0D4A48,/*1931-1940*/
    0x6DA53B,0x0B554F,0x056A45,0x4AADB9,0x025D4D,0x092D42,0x2C95B6,0x0A954A,0x7B4ABD,0x06CA51,/*1941-1950*/
    0x0B5546,0x555ABB,0x04DA4E,0x0A5B43,0x352BB8,0x052B4C,0x8A953F,0x0E9552,0x06AA48,0x6AD53C,/*1951-1960*/
    0x0AB54F,0x04B645,0x4A5739,0x0A574D,0x052642,0x3E9335,0x0D9549,0x75AABE,0x056A51,0x096D46,/*1961-1970*/
    0x54AEBB,0x04AD4F,0x0A4D43,0x4D26B7,0x0D254B,0x8D52BF,0x0B5452,0x0B6A47,0x696D3C,0x095B50,/*1971-1980*/
    0x049B45,0x4A4BB9,0x0A4B4D,0xAB25C2,0x06A554,0x06D449,0x6ADA3D,0x0AB651,0x093746,0x5497BB,/*1981-1990*/
    0x04974F,0x064B44,0x36A537,0x0EA54A,0x86B2BF,0x05AC53,0x0AB647,0x5936BC,0x092E50,0x0C9645,/*1991-2000*/
    0x4D4AB8,0x0D4A4C,0x0DA541,0x25AAB6,0x056A49,0x7AADBD,0x025D52,0x092D47,0x5C95BA,0x0A954E,/*2001-2010*/
    0x0B4A43,0x4B5537,0x0AD54A,0x955ABF,0x04BA53,0x0A5B48,0x652BBC,0x052B50,0x0A9345,0x474AB9,/*2011-2020*/
    0x06AA4C,0x0AD541,0x24DAB6,0x04B64A,0x69573D,0x0A4E51,0x0D2646,0x5E933A,0x0D534D,0x05AA43,/*2021-2030*/
    0x36B537,0x096D4B,0xB4AEBF,0x04AD53,0x0A4D48,0x6D25BC,0x0D254F,0x0D5244,0x5DAA38,0x0B5A4C,/*2031-2040*/
    0x056D41,0x24ADB6,0x049B4A,0x7A4BBE,0x0A4B51,0x0AA546,0x5B52BA,0x06D24E,0x0ADA42,0x355B37,/*2041-2050*/
    0x09374B,0x8497C1,0x049753,0x064B48,0x66A53C,0x0EA54F,0x06B244,0x4AB638,0x0AAE4C,0x092E42,/*2051-2060*/
    0x3C9735,0x0C9649,0x7D4ABD,0x0D4A51,0x0DA545,0x55AABA,0x056A4E,0x0A6D43,0x452EB7,0x052D4B,/*2061-2070*/
    0x8A95BF,0x0A9553,0x0B4A47,0x6B553B,0x0AD54F,0x055A45,0x4A5D38,0x0A5B4C,0x052B42,0x3A93B6,/*2071-2080*/
    0x069349,0x7729BD,0x06AA51,0x0AD546,0x54DABA,0x04B64E,0x0A5743,0x452738,0x0D264A,0x8E933E,/*2081-2090*/
    0x0D5252,0x0DAA47,0x66B53B,0x056D4F,0x04AE45,0x4A4EB9,0x0A4D4C,0x0D1541,0x2D92B5          /*2091-2099*/
};

int monthTotal[13] = {0,31,59,90,120,151,181,212,243,273,304,334,365};
Mydate toSolar(Mydate lunar){
    int year = lunar.year,
    month = lunar.month,
    day = lunar.day;
    int byNow, xMonth, i;
    Mydate solar;
    byNow = (lunar200y[year-1901] & 0x001F) - 1;
    if( ((lunar200y[year-1901]&0x0060)>>5) == 2)
        byNow += 31;
    for(i = 1; i < month; i ++){
        if( ( lunar200y[year - 1901] & (0x80000 >> (i-1)) ) ==0){
            byNow += 29;
        }
        else
            byNow += 30;
    }
    byNow += day;
    xMonth = (lunar200y[year - 1901] & 0xf00000)>>20;
    if(xMonth != 0){
        if(month > xMonth
           ||(month==xMonth && lunar.reserved == 1)){
            if((lunar200y[year-1901] & (0x80000>>(month-1)))==0)
                byNow += 29;
            else
                byNow += 30;
        }
    }
    if(byNow > 366
       ||(year%4!=0 && byNow == 365)){
        year += 1;
        if(year%4==0)
            byNow -= 366;
        else
            byNow -= 365;
    }
    for(i=1; i <= 13; i ++){
        if(monthTotal[i] >= byNow){
            month = i;
            break;
        }
    }
    solar.day = byNow - monthTotal[month-1];
    solar.month = month;
    solar.year = year;
    
    return solar;
}
Mydate toLunar(Mydate solar){
    int year = solar.year,
    month = solar.month,
    day = solar.day;
    int bySpring,bySolar,daysPerMonth;
    int index,flag;
    Mydate lunar;
    
    //bySpring ???????????????????????????????????????
    //bySolar ??????????????????????????????????????????
    if( ((lunar200y[year-1901] & 0x0060) >> 5) == 1)
        bySpring = (lunar200y[year-1901] & 0x001F) - 1;
    else
        bySpring = (lunar200y[year-1901] & 0x001F) - 1 + 31;
    bySolar = monthTotal[month-1] + day - 1;
    if( (!(year % 4)) && (month > 2))
        bySolar++;
    
    //daysPerMonth???????????????????????? 29 ???30
    //index ????????????????????????????????????
    //flag ????????????????????????????????????
    
    //??????????????????????????????????????????
    if (bySolar >= bySpring) {//??????????????????????????????????????????
        bySolar -= bySpring;
        month = 1;
        index = 1;
        flag = 0;
        if( ( lunar200y[year - 1901] & (0x80000 >> (index-1)) ) ==0)
            daysPerMonth = 29;
        else
            daysPerMonth = 30;
        while(bySolar >= daysPerMonth) {
            bySolar -= daysPerMonth;
            index++;
            if(month == ((lunar200y[year - 1901] & 0xF00000) >> 20) ) {
                flag = ~flag;
                if(flag == 0)
                    month++;
            }
            else
                month++;
            if( ( lunar200y[year - 1901] & (0x80000 >> (index-1)) ) ==0)
                daysPerMonth=29;
            else
                daysPerMonth=30;
        }
        day = bySolar + 1;
    }
    else {//?????????????????????
        bySpring -= bySolar;
        year--;
        month = 12;
        if ( ((lunar200y[year - 1901] & 0xF00000) >> 20) == 0)
            index = 12;
        else
            index = 13;
        flag = 0;
        if( ( lunar200y[year - 1901] & (0x80000 >> (index-1)) ) ==0)
            daysPerMonth = 29;
        else
            daysPerMonth = 30;
        while(bySpring > daysPerMonth) {
            bySpring -= daysPerMonth;
            index--;
            if(flag == 0)
                month--;
            if(month == ((lunar200y[year - 1901] & 0xF00000) >> 20))
                flag = ~flag;
            if( ( lunar200y[year - 1901] & (0x80000 >> (index-1)) ) ==0)
                daysPerMonth = 29;
            else
                daysPerMonth = 30;
        }
        
        day = daysPerMonth - bySpring + 1;
    }
    lunar.day = day;
    lunar.month = month;
    lunar.year = year;
    if(month == ((lunar200y[year - 1901] & 0xF00000) >> 20))
        lunar.reserved = 1;
    else
        lunar.reserved = 0;
    return lunar;
}

Mydate toLunar_fromdate(uint32_t year,uint32_t month,uint32_t day)
{
//    int year = year,
//    month = month,
//    day = day;
    int bySpring,bySolar,daysPerMonth;
    int index,flag;
    Mydate lunar;
    
    //bySpring ???????????????????????????????????????
    //bySolar ??????????????????????????????????????????
    if( ((lunar200y[year-1901] & 0x0060) >> 5) == 1)
        bySpring = (lunar200y[year-1901] & 0x001F) - 1;
    else
        bySpring = (lunar200y[year-1901] & 0x001F) - 1 + 31;
    bySolar = monthTotal[month-1] + day - 1;
    if( (!(year % 4)) && (month > 2))
        bySolar++;
    
    //daysPerMonth???????????????????????? 29 ???30
    //index ????????????????????????????????????
    //flag ????????????????????????????????????
    
    //??????????????????????????????????????????
    if (bySolar >= bySpring) {//??????????????????????????????????????????
        bySolar -= bySpring;
        month = 1;
        index = 1;
        flag = 0;
        if( ( lunar200y[year - 1901] & (0x80000 >> (index-1)) ) ==0)
            daysPerMonth = 29;
        else
            daysPerMonth = 30;
        while(bySolar >= daysPerMonth) {
            bySolar -= daysPerMonth;
            index++;
            if(month == ((lunar200y[year - 1901] & 0xF00000) >> 20) ) {
                flag = ~flag;
                if(flag == 0)
                    month++;
            }
            else
                month++;
            if( ( lunar200y[year - 1901] & (0x80000 >> (index-1)) ) ==0)
                daysPerMonth=29;
            else
                daysPerMonth=30;
        }
        day = bySolar + 1;
    }
    else {//?????????????????????
        bySpring -= bySolar;
        year--;
        month = 12;
        if ( ((lunar200y[year - 1901] & 0xF00000) >> 20) == 0)
            index = 12;
        else
            index = 13;
        flag = 0;
        if( ( lunar200y[year - 1901] & (0x80000 >> (index-1)) ) ==0)
            daysPerMonth = 29;
        else
            daysPerMonth = 30;
        while(bySpring > daysPerMonth) {
            bySpring -= daysPerMonth;
            index--;
            if(flag == 0)
                month--;
            if(month == ((lunar200y[year - 1901] & 0xF00000) >> 20))
                flag = ~flag;
            if( ( lunar200y[year - 1901] & (0x80000 >> (index-1)) ) ==0)
                daysPerMonth = 29;
            else
                daysPerMonth = 30;
        }
        
        day = daysPerMonth - bySpring + 1;
    }
    lunar.day = day;
    lunar.month = month;
    lunar.year = year;
    if(month == ((lunar200y[year - 1901] & 0xF00000) >> 20))
        lunar.reserved = 1;
    else
        lunar.reserved = 0;
    return lunar;
}



//#####################################################################################################
static const char *ChDay[] = {"*","??????","??????","??????","??????","??????",
                        "??????","??????","??????","??????","??????",
                        "??????","??????","??????","??????","??????",
                        "??????","??????","??????","??????","??????",
                        "??????","??????","??????","??????","??????",
                        "??????","??????","??????","??????","??????"
                        };
static const char *ChMonth[] = {"*","???","???","???","???","???","???","???","???","???","???","??????","???"};





static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        if(lv_calendar_get_pressed_date(obj, &date)) {
            LV_LOG_USER("Clicked date: %02d.%02d.%d", date.day, date.month, date.year);
        }
    }
}

const char * const day_names[7] = {"???","???","???","???","???","???","???"};
const char * const dayofweek_names[7] = {"?????????","?????????","?????????","?????????","?????????","?????????","?????????"};

static lv_obj_t *date_title_panel;
static lv_obj_t *month_show_label;
static lv_obj_t *month_label;
static lv_obj_t *date_line_obj;
static lv_obj_t *year_show_label;
static lv_obj_t *day_show_label;
static lv_obj_t *nongli_label;
static lv_obj_t  *calendar;


void lv_my_calendar_set_date(uint32_t year,uint32_t month,uint32_t day)
{
		Mydate lunar;
		char nonglistr[20]={0};
    char yearstr[5]={0};
    char monthstr[10]={0};
    char daystr[5]={0};
    uint8_t days = 0;
    if(month_show_label)
    {
        rt_sprintf(monthstr,"%02d/%02d",month,day);
        lv_label_set_text(month_show_label,monthstr);
    }
    if(year_show_label)
    {
        rt_sprintf(yearstr,"%04d",year);
        lv_label_set_text(year_show_label,yearstr);
    }
    if(day_show_label)
    {
        days = get_day_of_week(year,month,day);
        lv_label_set_text(day_show_label,dayofweek_names[days]);
    }
    if(calendar)
    {
        lv_calendar_set_today_date(calendar, year, month, day);
        lv_calendar_set_showed_date(calendar, year, month);
    }
    if(nongli_label)
    {
					lunar = toLunar_fromdate(year,month,day);
					if(lunar.reserved)
					{
						rt_memset(nonglistr,0,20*sizeof(char));
            rt_sprintf(nonglistr,"%s???%s (???)",ChMonth[lunar.month],ChDay[lunar.day]);
					}
					else
					{
						rt_memset(nonglistr,0,20*sizeof(char));
            rt_sprintf(nonglistr,"%s???%s",ChMonth[lunar.month],ChDay[lunar.day]);
					}
				lv_label_set_text(nongli_label,nonglistr);
    }
}


int setcalendardate(int argc, char** argv)
{
    if (argc != 4)
    {
        rt_kprintf("Please using: setcalendardate year month day\n");
        return -1;
    }
		lv_my_calendar_set_date(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]));
    return 0;
}

MSH_CMD_EXPORT(setcalendardate, debug setcalendardate.);

void lv_my_calendar_create(lv_obj_t *parent)
{
    calendar = lv_calendar_create(parent);
    lv_obj_set_size(calendar, 280, 280);
    lv_obj_align(calendar, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_add_event_cb(calendar, event_handler, LV_EVENT_ALL, NULL);

    // lv_obj_set_style_bg_color(calendar,lv_color_make(255,255,255),LV_STATE_DEFAULT);
		lv_obj_set_style_text_color(calendar,lv_color_make(255,255,255),LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(calendar,LV_OPA_TRANSP,LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(calendar,&HarmonyOS_Sans_SC_Medium,LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(calendar,0,LV_STATE_DEFAULT);
    lv_calendar_set_day_names(calendar,(const char **)day_names);
    lv_calendar_set_today_date(calendar, 2022, 8, 3);
    lv_calendar_set_showed_date(calendar, 2022, 8);
    //?????? ?????? ??????
    date_title_panel = lv_obj_create(parent);
    lv_obj_set_size(date_title_panel, 200, 80);
    lv_obj_clear_flag(date_title_panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(date_title_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(date_title_panel, lv_color_hex(0x646464), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(date_title_panel, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(date_title_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(date_title_panel,calendar,LV_ALIGN_OUT_TOP_LEFT,0,0);

    year_show_label = lv_label_create(date_title_panel);
    lv_obj_set_style_text_color(year_show_label,lv_color_make(255,255,255),LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(year_show_label,&lv_font_montserrat_24,LV_STATE_DEFAULT);
    lv_label_set_text(year_show_label,"2022");
    lv_obj_align(year_show_label,LV_ALIGN_TOP_LEFT,5,5);

    month_show_label = lv_label_create(date_title_panel);
    lv_obj_set_style_text_color(month_show_label,lv_color_make(255,255,255),LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(month_show_label,&HarmonyOS_Sans_SC_Medium,LV_STATE_DEFAULT);
    lv_label_set_text(month_show_label,"08/03");
    lv_obj_align_to(month_show_label,year_show_label,LV_ALIGN_OUT_BOTTOM_MID,0,0);

    // static lv_obj_t *date_line_obj;
    date_line_obj = lv_line_create(date_title_panel);
    /*Create an array for the points of the line*/
    static lv_point_t line_points[] = { {75, 0}, {75, 50}};
    /*Create style*/
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 2);
    lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_line_rounded(&style_line, true);
    lv_line_set_points(date_line_obj, line_points, 2);     /*Set the points*/
    lv_obj_add_style(date_line_obj, &style_line, 0);

    day_show_label = lv_label_create(date_title_panel);
    lv_obj_set_style_text_color(day_show_label,lv_color_make(255,255,255),LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(day_show_label,&HarmonyOS_Sans_SC_Medium,LV_STATE_DEFAULT);
    lv_label_set_text(day_show_label,"?????????");
    lv_obj_align_to(day_show_label,date_line_obj,LV_ALIGN_OUT_RIGHT_TOP,5,0);

    // ????????????
    nongli_label = lv_label_create(date_title_panel);
    lv_obj_set_style_text_color(nongli_label,lv_color_make(255,255,255),LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(nongli_label,&HarmonyOS_Sans_SC_Medium,LV_STATE_DEFAULT);
    lv_label_set_text(nongli_label,"????????????");
    lv_obj_align_to(nongli_label,date_line_obj,LV_ALIGN_OUT_RIGHT_BOTTOM,5,0);
}


//void lv_example_calendar_1(void)
//{
//    lv_my_calendar_create(lv_scr_act());

//    lv_my_calendar_set_date(2022,8,4);
//}

