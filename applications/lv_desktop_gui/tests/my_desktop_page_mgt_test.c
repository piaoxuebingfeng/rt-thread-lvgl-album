#include <sys/time.h>
#include <string.h>
#include "my_desktop_page_mgt_test.h"
#include "newspageui.h"
#include "settingpageui.h"
//#include "lv_imgscreen_page_test.h"
#include "albumpageui.h"
#include "simple_test.h"
#include "weatherpageui.h"
#include "clockpageui.h"
#include "lv_mycalendar.h"
#include "lv_backbtn_test.h"
#if defined(RT_USING_SAL)
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#endif

#if defined(RT_USING_NETDEV)
#include <netdev.h>
#endif



#if LV_MY_DESKTOP_PAGE_MGT_TEST != 0


static lv_obj_t * page_manager = NULL;

// 桌面
static void my_desktop_main_page(lv_obj_t * page);

//时钟 万年历界面
static void clockscr_page(lv_obj_t * page);

//相册界面
static void imgscr_page(lv_obj_t * page);
//天气界面
static void weatherscr_page(lv_obj_t *page);

// 新闻 

static void newsscr_page(lv_obj_t * page);

static void game2048_page(lv_obj_t *page);

//设置界面
static void settingscr_page(lv_obj_t *page);

void clockscr_timer_task_init(void);

void lv_my_desktop_page_mgt_test(void)
{
    page_manager = lv_100ask_page_manager_create(lv_scr_act());

    lv_obj_t * desktop_main_page = lv_100ask_page_manager_page_create(page_manager, "deskmainpage");
    lv_obj_t * clock_page = lv_100ask_page_manager_page_create(page_manager, "clockscr");
		lv_obj_t * weather_page = lv_100ask_page_manager_page_create(page_manager, "weatherscr");
    lv_obj_t * img_page = lv_100ask_page_manager_page_create(page_manager, "imgscr");
    lv_obj_t * news_page = lv_100ask_page_manager_page_create(page_manager, "newsscr");
		lv_obj_t * game_page = lv_100ask_page_manager_page_create(page_manager, "game2048");
    lv_obj_t * setting_page = lv_100ask_page_manager_page_create(page_manager, "settingscr");

    lv_100ask_page_manager_set_page_init(desktop_main_page, my_desktop_main_page);
    lv_100ask_page_manager_set_page_init(clock_page, clockscr_page);
		lv_100ask_page_manager_set_page_init(weather_page, weatherscr_page);
	
    lv_100ask_page_manager_set_page_init(img_page, imgscr_page);
    lv_100ask_page_manager_set_page_init(news_page, newsscr_page);
		lv_100ask_page_manager_set_page_init(game_page, game2048_page);
    lv_100ask_page_manager_set_page_init(setting_page, settingscr_page);
	

    lv_100ask_page_manager_set_main_page(page_manager, desktop_main_page);
    lv_100ask_page_manager_set_open_page(NULL, "deskmainpage");
}


static void my_desktop_main_page(lv_obj_t * page)
{
	extern void lv_desktop_backbtn_test(lv_obj_t * page);
	lv_desktop_backbtn_test(page);
	


//    static lv_style_t style;
//    lv_style_init(&style);
//    lv_style_set_flex_flow(&style, LV_FLEX_FLOW_ROW_WRAP);
//    lv_style_set_flex_main_place(&style, LV_FLEX_ALIGN_SPACE_EVENLY);
//    lv_style_set_layout(&style, LV_LAYOUT_FLEX);

//    lv_obj_t * cont = lv_obj_create(page);
//    lv_obj_set_size(cont, LV_PCT(95), LV_PCT(20));
//    lv_obj_center(cont);
//    lv_obj_add_style(cont, &style, 0);


//    lv_obj_t * obj1 = lv_obj_create(cont);
//    lv_obj_set_size(obj1, LV_SIZE_CONTENT, LV_PCT(100));
//    lv_obj_add_flag(obj1, LV_OBJ_FLAG_CHECKABLE);
//    lv_obj_t * label1 = lv_label_create(obj1);
//    lv_label_set_text(label1, "clockscr");
//    lv_obj_center(label1);
//    lv_100ask_page_manager_set_load_page_event(obj1, NULL, lv_label_get_text(label1));


//    lv_obj_t * obj2 = lv_obj_create(cont);
//    lv_obj_set_size(obj2, LV_SIZE_CONTENT, LV_PCT(100));
//    lv_obj_add_flag(obj2, LV_OBJ_FLAG_CHECKABLE);
//    lv_obj_t * label2 = lv_label_create(obj2);
//    lv_label_set_text(label2, "imgscr");
//    lv_obj_center(label2);
//    lv_100ask_page_manager_set_load_page_event(obj2, NULL, lv_label_get_text(label2));
}



// --------------------------------------------------------------------------------------------------------------------------
// 相册桌面

static void imgscr_page(lv_obj_t * page)
{
    if(page==NULL)
    {
        LV_LOG_USER("lv_obj_t page is null\n");
        return ;
    }

		ui_albumpage_screen_init(page);
//    lv_imgscr_page_create(page);
}

static void weatherscr_page(lv_obj_t *page)
{
    if(page==NULL)
    {
        LV_LOG_USER("lv_obj_t page is null\n");
        return ;
    }
		weatherpageui_init(page);
}



static void settingscr_page(lv_obj_t * page)
{
    if(page==NULL)
    {
        LV_LOG_USER("lv_obj_t page is null\n");
        return ;
    }
    ui_settingpage_screen_init(page);
}

static void game2048_page(lv_obj_t *page)
{
	if(page==NULL)
	{
			LV_LOG_USER("lv_obj_t page is null\n");
			return ;
	}
	lv_100ask_2048_simple_test(page);
}

static void newsscr_page(lv_obj_t * page)
{
    if(page==NULL)
    {
        LV_LOG_USER("lv_obj_t page is null\n");
        return ;
    }
    ui_news_page_screen_init(page);
}


static void clockscr_page(lv_obj_t * page)
{
	if(page==NULL)
	{
			LV_LOG_USER("lv_obj_t page is null\n");
			return ;
	}
	clockpageui(page);
//	lv_clock_label_create(page);
}

// --------------------------------------------------------------------------------------------------------------------------
// 当前页面更新
// 根据页面更新内容




static rt_bool_t loop_check_network(void)
{
#ifdef RT_USING_NETDEV
    struct netdev * netdev = netdev_get_by_family(AF_INET);
    return (netdev && netdev_is_link_up(netdev));
#else
    return RT_TRUE;
#endif
}

void update_top_status_bar(struct tm *p)
{
		char ptimestr[10];
		if(loop_check_network())
		{
			lv_page_top_status_set_wifi_label(1);
		}
		else
		{
			lv_page_top_status_set_wifi_label(0);
		}
		
		//void lv_page_top_status_set_sdcard_label(char sdcard_status);
		//void lv_page_top_status_set_location_label(const char *location_str);
		if(p)
		{
			rt_memset(ptimestr,0,10);
			rt_sprintf(ptimestr,"%02d:%02d",p->tm_hour,p->tm_min);
			lv_page_top_status_set_time_label(ptimestr);
		}
}

void lv_desktop_gui_page_update()
{
	time_t now;
	struct tm *p;
	now = time(RT_NULL);
	p = localtime(&now); 
	
	if(page_manager)
	{
//		if(!lv_100ask_page_manager_get_current_page(page_manager,"deskmainpage"))
//		{
//				update_top_status_bar(p);
//		}
		if(lv_100ask_page_manager_get_current_page(page_manager,"deskmainpage"))
		{
//			rt_kprintf("desktop page\n");
			desktopmainpage_update();

		}
		else if(lv_100ask_page_manager_get_current_page(page_manager,"clockscr"))
		{
//			rt_kprintf("clock page\n");
			if(p)
			{
				//rt_snprintf(clocktime,10,"%02d:%02d",p->tm_hour,p->tm_min);
				
//				lv_my_calendar_set_date(p->tm_year+1900, p->tm_mon+1, p->tm_mday);
				lv_clock_label_update(p->tm_hour,p->tm_min,p->tm_sec);		
			}
			update_top_status_bar(p);

		}
		else if(lv_100ask_page_manager_get_current_page(page_manager,"imgscr"))
		{
			update_top_status_bar(p);
//			rt_kprintf("img page\n");
		}
		else if(lv_100ask_page_manager_get_current_page(page_manager,"newsscr"))
		{
//			rt_kprintf("news page\n");
			if( p->tm_hour >7 && p->tm_hour < 23 && p->tm_min!=0 &&  p->tm_min %50==0 && p->tm_sec!=0 && p->tm_sec%50==0)
			{
				news_str_update();
			}
			if(p->tm_sec %30 ==0)
			{
				news_show_update();
			}
			update_top_status_bar(p);

		}
		else if(lv_100ask_page_manager_get_current_page(page_manager,"game2048"))
		{
//			rt_kprintf("game2048 page\n");
			update_top_status_bar(p);
		}
		else if(lv_100ask_page_manager_get_current_page(page_manager,"weatherscr"))
		{
//			rt_kprintf("weather page\n");
			update_top_status_bar(p);
		}
		else if(lv_100ask_page_manager_get_current_page(page_manager,"settingscr"))
		{
//			rt_kprintf("setting page\n");
			update_top_status_bar(p);
		}
		
	}
}



#endif