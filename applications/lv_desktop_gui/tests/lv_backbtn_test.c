#include <lvgl.h>
#include "lv_backbtn_test.h"
#include "albumpageui.h"

// just test
#include"my_desktop_page_mgt_test.h"

// #include "lv_desktop_gui/imgs/chinese-style.h"
//#pragma execution_character_set("utf-8")

// 测试中文字体库
//LV_FONT_DECLARE(m16chinesefont);
LV_FONT_DECLARE(HarmonyOS_Sans_SC_Medium);

//LV_FONT_DECLARE(MontserratMediumNumber120);
LV_FONT_DECLARE(SiYuanRouHeiDengKuanBan120);

#define LV_BACKBTN_SIZE 64
#define LV_MENU_BTN_SIZE 32


// 定义桌面图标结构体

struct app_icon_s
{
	lv_obj_t *app_cond;
	lv_obj_t *app_img;
	lv_obj_t *app_name;
	lv_coord_t app_cond_w;
	lv_coord_t app_cond_h;
};

typedef struct app_icon_s app_icon_t;

// app 图标结构体
#define APP_ICON_SIZE 90

app_icon_t app_weather={NULL,NULL,NULL,APP_ICON_SIZE,APP_ICON_SIZE};
app_icon_t app_news={NULL,NULL,NULL,APP_ICON_SIZE,APP_ICON_SIZE};
app_icon_t app_imgs={NULL,NULL,NULL,APP_ICON_SIZE,APP_ICON_SIZE};
app_icon_t app_game={NULL,NULL,NULL,APP_ICON_SIZE,APP_ICON_SIZE};
app_icon_t app_setting={NULL,NULL,NULL,APP_ICON_SIZE,APP_ICON_SIZE};


extern app_icon_t app_imgs;


LV_IMG_DECLARE(ui_img_iconimages64_png);
LV_IMG_DECLARE(ui_img_iconniews64_png);
LV_IMG_DECLARE(ui_img_iconsetting64_png);
LV_IMG_DECLARE(ui_img_iconweather64_png);
LV_IMG_DECLARE(ui_img_icongame2048_png);



//// 定义一个桌面悬浮球的结构体，用于管理桌面悬浮球对象
//struct desktop_menubtn_s
//{
//    lv_obj_t *menubtn_parent;
//    lv_obj_t *menubtn;         //桌面悬浮球按钮
//    lv_obj_t *backscreenbtn;   //返回到上一级主界面
//    lv_obj_t *timesceen_btn;   //进入时钟显示界面
//    lv_obj_t *musicsceen_btn;  //进入音乐播放界面 
//    lv_obj_t *weatherscreen_btn; //进入天气界面
//    bool btnMenuState;
//    uint16_t menubtn_pos_x;   // 悬浮球当前 x 坐标
//    uint16_t menubtn_pos_y;   // 悬浮球当前 y 坐标
//};

//typedef struct desktop_menubtn_s desktop_menubtn_t;


desktop_menubtn_t dm={
    .menubtn_parent=NULL,
    .menubtn=NULL,
    .backscreenbtn=NULL,
    .timesceen_btn=NULL,
    .musicsceen_btn=NULL,
    .weatherscreen_btn=NULL,
    .btnMenuState=false,
    .menubtn_pos_x=0,
    .menubtn_pos_y=0};



// 样式定义
/*Init the style for the default state*/
static lv_style_t menubtnstyle;
/*Init the pressed style*/
static lv_style_t style_pr;
static lv_style_t btn_style_pr;
static lv_style_t btnstyle;
		
		


// 字体样式		
static lv_style_t label_time_style;
//中文字体样式
//static lv_style_t label_style;


static lv_style_transition_dsc_t menubtntrans;
static lv_style_transition_dsc_t btntrans;

static void lv_menu_style_init(void);


static lv_obj_t * bg_img ;
static lv_obj_t *time_label;


// 函数声明

static void lv_desktop_backbtn_create(lv_obj_t * parent);
static void lv_backbtn_event_cb(lv_event_t * e);
static void lv_backbtn_menu_create(desktop_menubtn_t *dm_t);


static void lv_desktop_img_show_create(lv_obj_t *parent);
static void lv_desktop_bottom_menu_create(lv_obj_t *parent);


// 设置桌面背景
void lv_desktop_set_bg_img(int imgnum)
{
	if(bg_img)
	{
		switch(imgnum)
		{
			case 0:
				lv_img_set_src(bg_img, &bg_lvgl);
				break;
			case 1:
				lv_img_set_src(bg_img, &ui_img_testbg_png);
				break;
			case 2:
				lv_img_set_src(bg_img, &ui_img_seaandsky800_png);
				break;
			default:
				lv_img_set_src(bg_img, &bg_lvgl);
				break;
		}
	}
}


// 桌面悬浮球测试函数
void lv_desktop_backbtn_test(lv_obj_t * page)
{
    // 创建桌面
    lv_obj_t *desktop = lv_obj_create(page);

    // 删除对象所有样式
    lv_obj_remove_style_all(desktop);
    lv_obj_set_size(desktop, LV_HOR_RES, LV_VER_RES);       // 设置到屏幕大小
    

    //初始化样式
    lv_menu_style_init();


    // 设置桌面背景
    // 设置纯色背景
		lv_obj_set_style_bg_opa(desktop, LV_OPA_30, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(desktop,lv_color_make(157,137, 157),LV_STATE_DEFAULT);

#if 1
    // 设置图片背景
    // 使用 c 数组设置

    bg_img = lv_img_create(desktop);
//  lv_img_set_src(bg_img, &bg_lvgl);
		lv_img_set_src(bg_img, &ui_img_testbg_png);
		lv_obj_align(bg_img, LV_ALIGN_CENTER, 0, 0);
	// lv_obj_fade_in(desktop,0, delay);
#endif

#if 0
    // 设置图片背景
    // 直接获取原始图片
    lv_obj_t *bg_img = lv_img_create(desktop);
    lv_img_set_src(bg_img,"S:imgs/testbg.sjpg");
    lv_obj_center(bg_img);

#endif



    // 桌面悬浮球测试
//    lv_desktop_backbtn_create(desktop);
    lv_style_init(&label_time_style);
//    lv_style_set_text_opa(&label_time_style, LV_OPA_COVER);
    lv_style_set_text_color(&label_time_style, lv_color_hex(0xF4AA56));
//    lv_style_set_text_font(&label_time_style, &lv_font_montserrat_48);
//		lv_style_set_text_font(&label_time_style, &digitalclock);

    lv_style_set_text_font(&label_time_style, &SiYuanRouHeiDengKuanBan120);
    

	  time_label = lv_label_create(desktop);
    lv_obj_add_style(time_label, &label_time_style,LV_STATE_DEFAULT);
//		lv_obj_set_style_text_font(time_label, &digitalclock, LV_STATE_DEFAULT);
//		lv_obj_set_style_text_color(time_label, lv_color_hex(0xF4AA56), LV_STATE_DEFAULT);
    
		//lv_obj_align(time_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align(time_label, LV_ALIGN_TOP_RIGHT, -30,30);
		lv_label_set_text(time_label, "18:00");
		lv_100ask_page_manager_set_load_page_event(time_label, NULL, "clockscr");
		
		// 中文字体测试
//    lv_style_init(&label_style);
//    lv_style_set_text_opa(&label_style, LV_OPA_COVER);
//    lv_style_set_text_color(&label_style, lv_color_make(0,0,0));
//    lv_style_set_text_font(&label_style,&HarmonyOS_Sans_SC_Medium);

//    lv_obj_t *font_label = lv_label_create(desktop);
//    lv_obj_add_style(font_label, &label_style,LV_STATE_DEFAULT);
//    lv_obj_align(font_label, LV_ALIGN_TOP_MID, 0, 0);
//    lv_label_set_text(font_label,"桌面相册");
//    lv_label_set_text(font_label, "main");

	
	
	// 创建桌面图片展示区域
		lv_desktop_img_show_create(desktop);
		// 创建底部 app 菜单栏
		lv_desktop_bottom_menu_create(desktop);

}


static void lv_menu_style_init(void)
{
    lv_style_init(&btnstyle);
    lv_style_set_radius(&btnstyle, 360);
    lv_style_set_bg_opa(&btnstyle, LV_OPA_100);
    lv_style_set_bg_color(&btnstyle, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_bg_grad_color(&btnstyle, lv_palette_darken(LV_PALETTE_GREEN, 2));
    lv_style_set_bg_grad_dir(&btnstyle, LV_GRAD_DIR_VER);
    lv_style_set_border_opa(&btnstyle, LV_OPA_40);
    lv_style_set_border_width(&btnstyle, 2);
    lv_style_set_border_color(&btnstyle, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_outline_opa(&btnstyle, LV_OPA_COVER);
    lv_style_set_outline_color(&btnstyle, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_text_color(&btnstyle, lv_color_white());
    lv_style_set_pad_all(&btnstyle, 10);

    lv_style_init(&menubtnstyle);
    lv_style_set_radius(&menubtnstyle, 360);
    lv_style_set_bg_opa(&menubtnstyle, LV_OPA_100);
    lv_style_set_bg_color(&menubtnstyle, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_bg_grad_color(&menubtnstyle, lv_palette_darken(LV_PALETTE_GREY, 2));
    lv_style_set_bg_grad_dir(&menubtnstyle, LV_GRAD_DIR_VER);
    lv_style_set_border_opa(&menubtnstyle, LV_OPA_40);
    lv_style_set_border_width(&menubtnstyle, 2);
    lv_style_set_border_color(&menubtnstyle, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_outline_opa(&menubtnstyle, LV_OPA_COVER);
    lv_style_set_outline_color(&menubtnstyle, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_text_color(&menubtnstyle, lv_color_white());
    lv_style_set_pad_all(&menubtnstyle, 10);

    lv_style_init(&style_pr);
    /*Ad a large outline when pressed*/
    lv_style_set_outline_width(&style_pr, 30);
    lv_style_set_outline_opa(&style_pr, LV_OPA_TRANSP);
    //lv_style_set_translate_y(&style_pr, 5);
    lv_style_set_bg_color(&style_pr, lv_palette_darken(LV_PALETTE_GREY, 2));
    lv_style_set_bg_grad_color(&style_pr, lv_palette_darken(LV_PALETTE_GREY, 4));

    lv_style_init(&btn_style_pr);
    /*Ad a large outline when pressed*/
    lv_style_set_outline_width(&btn_style_pr, 30);
    lv_style_set_outline_opa(&btn_style_pr, LV_OPA_TRANSP);
    //lv_style_set_translate_y(&btn_style_pr, 5);
    lv_style_set_bg_color(&btn_style_pr, lv_palette_darken(LV_PALETTE_GREEN, 2));
    lv_style_set_bg_grad_color(&btn_style_pr, lv_palette_darken(LV_PALETTE_GREEN, 4));
    

    /*Add a transition to the the outline*/
    // static lv_style_transition_dsc_t menubtntrans;
    static lv_style_prop_t menu_btn_props[] = {LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA, 0};
    lv_style_transition_dsc_init(&menubtntrans, menu_btn_props, lv_anim_path_linear, 300, 0, NULL);
    lv_style_set_transition(&style_pr, &menubtntrans);

    // 子菜单的动画效果需要更改
    static lv_style_prop_t btn_props[] = {LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA, 0};
    lv_style_transition_dsc_init(&btntrans, btn_props, lv_anim_path_linear, 200, 0, NULL);
    lv_style_set_transition(&btn_style_pr, &btntrans);




}

//-----------------------------------------------------------------------------------------------------
// 时间实时显示 定时器
#include <sys/time.h>
#include <string.h>


void desktopmainpage_update()
{
	char clocktime[10]={0};  
	static uint8_t img_i=0;
//	static char *desktop_imgsrc_path[2]={"S:minimgs/tiger.jpg","S:minimgs/esp32show.jpg"};	
	time_t now;
	struct tm *p;
	/* output current time */
	now = time(RT_NULL);
	p = localtime(&now); 
	if(p)
	{
		if(p->tm_sec % 2 ==0)
		{
			rt_snprintf(clocktime,10,"%02d:%02d",p->tm_hour,p->tm_min);
		}
		else
		{
			rt_snprintf(clocktime,10,"%02d %02d",p->tm_hour,p->tm_min);
		}
		if(time_label)
		{
			lv_label_set_text(time_label, clocktime);
		}
		
		// 更新照片
		if(p->tm_sec %15==0)
		{
//			desktop_img_switch(desktop_imgsrc_path[img_i]);
//			img_i++;
//			if(img_i==2)
//			{
//				img_i=0;
//			}
			lv_minimgs_auto_update();
		}
	}
}



void clocktime_update_timer_cb(lv_timer_t * timer)
{
    uint32_t * user_data = timer->user_data;
	  char clocktime[10]={0};   
		time_t now;
	  struct tm *p;
		/* output current time */
		now = time(RT_NULL);
		p = localtime(&now); 
		if(p)
		{
			if(p->tm_sec % 2 ==0)
			{
				rt_snprintf(clocktime,10,"%02d:%02d",p->tm_hour,p->tm_min);
			}
			else
			{
				rt_snprintf(clocktime,10,"%02d %02d",p->tm_hour,p->tm_min);
			}
			
			
			if(time_label)
			{
				lv_label_set_text(time_label, clocktime);
			}
		}
}

static lv_obj_t * desktop_img_cond ;
static lv_obj_t *desktop_imgshow;

static void lv_desktop_img_show_create(lv_obj_t *parent)
{
		if(NULL ==parent)
		{
			LV_LOG_ERROR("parent is null \n");
			return;
		}
		
		desktop_img_cond = lv_obj_create(parent);
    lv_obj_set_size(desktop_img_cond, 250, 330);
		lv_obj_clear_flag(desktop_img_cond, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(desktop_img_cond, LV_ALIGN_LEFT_MID, 20, -60);
		lv_obj_set_style_radius(desktop_img_cond,5,LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(desktop_img_cond,LV_OPA_50,LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(desktop_img_cond,lv_color_hex(0xC9C9CE),LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(desktop_img_cond,0,LV_STATE_DEFAULT);
//		lv_obj_set_flex_flow(desktop_img_cond, LV_FLEX_FLOW_ROW);
//    lv_obj_set_style_flex_main_place(desktop_img_cond,LV_FLEX_ALIGN_SPACE_EVENLY,LV_STATE_DEFAULT);
		
    desktop_imgshow = lv_img_create(desktop_img_cond);
//    lv_img_set_src(desktop_imgshow,"S:minimgs/esp32show.jpg");
    lv_obj_center(desktop_imgshow);
		
}


static void img_opa_anim_cb(void * var, int32_t v)
{
    // lv_obj_set_y(var, v);
    lv_obj_set_style_opa(var,v,LV_STATE_DEFAULT);
}



// minimgs
static imgs_mgt_t *minimgs_list_head = RT_NULL;
static imgs_mgt_t *minimgs_current_show = RT_NULL;
static uint32_t minimg_show_count =1;


// 读取 SD 卡中图片信息，整理成一个列表，提供给 minimgs 后续使用
void minimgs_list_init()
{
	imgs_mgt_t *imgs_list_p = RT_NULL;	
	imgs_mgt_t *imgs_list_q = RT_NULL;	
	DIR *dirp;
	struct dirent *d;
	int imgs_count =0;
	int imgs_total_nums =0;
	int len=0;
	

	/* 打开 / dir_test 目录 */
	dirp = opendir("/minimgs");
	if (dirp == RT_NULL)
	{
			rt_kprintf("open directory error!\n");
	}
	else
	{
			
			/* 读取目录 */
			while ((d = readdir(dirp)) != RT_NULL)
			{
				imgs_total_nums++;
			}
			/* 关闭目录 */
			closedir(dirp);
	}
	
	rt_kprintf("minimgs total nums :%d\n",imgs_total_nums);
	
	dirp = opendir("/minimgs");
	if (dirp == RT_NULL)
	{
			rt_kprintf("open directory error!\n");
	}
	else
	{
			
			/* 读取目录 */
			while ((d = readdir(dirp)) != RT_NULL)
			{
				len = rt_strlen(d->d_name);
				imgs_list_p = (imgs_mgt_t *)rt_malloc(sizeof(imgs_mgt_t));
				if(imgs_list_p== RT_NULL)
				{
					rt_kprintf("imgs_list_p malloc fail\n");
					goto __exit ;
				}
				// 插入图片名称
				imgs_list_p->imgs_path = (char *)rt_malloc(sizeof(char)*len+10);
				if(imgs_list_p->imgs_path== RT_NULL)
				{
					rt_kprintf("imgs_path malloc fail\n");
					goto __exit ;
				}
				imgs_list_p->imgs_lvgl_path = (char *)rt_malloc(sizeof(char)*len+10);
				if(imgs_list_p->imgs_lvgl_path== RT_NULL)
				{
					rt_kprintf("imgs_lvgl_path malloc fail\n");
					goto __exit ;
				}			
				
				rt_sprintf(imgs_list_p->imgs_path,"/minimgs/%s",d->d_name);
				rt_sprintf(imgs_list_p->imgs_lvgl_path,"S:minimgs/%s",d->d_name);
				imgs_count++;
				imgs_list_p->imgs_count      =  imgs_count;
				imgs_list_p->imgs_total_nums =  imgs_total_nums;
				imgs_list_p->next = RT_NULL;
				rt_kprintf("[%d/%d] %s  \n",imgs_list_p->imgs_count,imgs_list_p->imgs_total_nums,imgs_list_p->imgs_path );

				// 向链表中新增节点
				if(minimgs_list_head == RT_NULL)
				{
					minimgs_list_head = imgs_list_p;
					imgs_list_q = minimgs_list_head;					
				}
				else
				{
					while(imgs_list_q->next!=RT_NULL)
					{
						imgs_list_q = imgs_list_q->next;
					}
					imgs_list_q->next = imgs_list_p;
				}
			}
			/* 关闭目录 */
			closedir(dirp);
			return ;
	}
	
	
__exit:
	imgs_list_deinit();
	if(dirp)
	{
		closedir(dirp);
	}
}


void minimgs_set_current_img_node_head()
{
	if(minimgs_list_head)
	{
		minimgs_current_show = minimgs_list_head;
	}
}


void minimgs_list_show()
{
	imgs_mgt_t *imgs_list_p = minimgs_list_head;
	imgs_mgt_t *imgs_list_q= imgs_list_p;
	
	if(imgs_list_q != RT_NULL)
	{
		//while(imgs_list_q  && imgs_list_q->next!=RT_NULL)
		rt_kprintf("minimgs show \n");
		while(imgs_list_q)
		{
			rt_kprintf("[%d/%d]   %s  \n",imgs_list_q->imgs_count,imgs_list_q->imgs_total_nums,imgs_list_q->imgs_lvgl_path);
			imgs_list_q = imgs_list_q->next;
		}
	}
}


void lv_minimgs_auto_update()
{
	if(minimgs_current_show != RT_NULL)
	{
		if(minimgs_current_show->imgs_lvgl_path)
		{
			rt_kprintf("[%d/%d]   %s  \n",minimgs_current_show->imgs_count,minimgs_current_show->imgs_total_nums,minimgs_current_show->imgs_lvgl_path);
//			lv_img_set_src(desktop_imgshow, minimgs_current_show->imgs_lvgl_path);
			desktop_img_switch(minimgs_current_show->imgs_lvgl_path);
			minimgs_current_show = minimgs_current_show->next;
			if(minimgs_current_show == RT_NULL)
			{
				minimgs_current_show = minimgs_list_head;
			}
		}
	}
	
}




void minimgs_list_deinit()
{
	imgs_mgt_t *imgs_list_p = minimgs_list_head;
	imgs_mgt_t *imgs_list_q= RT_NULL;
	
	if(imgs_list_p != RT_NULL)
	{
		while(imgs_list_p)
		{
			imgs_list_q = imgs_list_p->next;
			if(imgs_list_p->imgs_path)
			{
				rt_free(imgs_list_p->imgs_path);
			}
			if(imgs_list_p->imgs_lvgl_path)
			{
				rt_free(imgs_list_p->imgs_lvgl_path);
			}
			rt_free(imgs_list_p);	
			imgs_list_p = imgs_list_q;
		}
		minimgs_list_head = RT_NULL;
	}
}


void desktop_img_switch(const char *imgsrc)
{
    if(imgsrc ==NULL && desktop_imgshow == NULL)
    {
        return ;
    }
		if(desktop_imgshow)
		{
			lv_img_set_src(desktop_imgshow,imgsrc);
			//创建图片切换动画
			lv_anim_t a2;
			lv_anim_init(&a2);
			lv_anim_set_var(&a2, desktop_imgshow);
			lv_anim_set_exec_cb(&a2, img_opa_anim_cb);
			lv_anim_set_values(&a2, 0, 255);
			lv_anim_set_delay(&a2,0);
			lv_anim_set_time(&a2, 1000);
			lv_anim_set_playback_delay(&a2, 10000);
			lv_anim_set_playback_time(&a2, 1000);
			lv_anim_start(&a2);
		}
}


// 桌面底部 app 图标菜单栏
static void lv_desktop_bottom_menu_create(lv_obj_t *parent)
{
		if(NULL ==parent)
		{
			LV_LOG_ERROR("parent is null \n");
			return;
		}
		
//    /* 创建底部导航栏 */
//		    /* bottom menu style */
//    static lv_style_t style_bottom_menu;
//    lv_style_init(&style_bottom_menu);
////    lv_style_set_text_font(&style_label_app_name, LV_STATE_DEFAULT, &lv_font_montserrat_12);
//    lv_style_set_bg_opa(&style_bottom_menu,  LV_OPA_80); // 设置色彩透明度
//    lv_style_set_radius(&style_bottom_menu, 10); // 设置圆角
//    lv_style_set_bg_color(&style_bottom_menu, lv_color_hex(0xC9C9CE)); //设置颜色
//		lv_style_set_border_width(&style_bottom_menu,0);

////    static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_INDEXED_1BIT(700, 100)];
////    lv_obj_t * canvas_bottom_menu = lv_canvas_create(parent);
//		
//		lv_obj_t * canvas_bottom_menu = lv_obj_create(parent);
//		lv_obj_set_size(canvas_bottom_menu, 700, 100);
//		
////		lv_obj_clear_flag(canvas_bottom_menu, LV_OBJ_FLAG_SCROLLABLE);
////		lv_canvas_set_buffer(canvas_bottom_menu,cbuf,700,100,LV_IMG_CF_INDEXED_1BIT);
//    lv_obj_align(canvas_bottom_menu,LV_ALIGN_BOTTOM_MID,0,-20);
//    lv_obj_add_style(canvas_bottom_menu, &style_bottom_menu,LV_STATE_DEFAULT);
////    lv_obj_fade_in(canvas_bottom_menu, 0 , 500);
//		
//		lv_obj_set_flex_flow(canvas_bottom_menu, LV_FLEX_FLOW_ROW);





    lv_obj_t * canvas_bottom_menu = lv_obj_create(parent);
    lv_obj_set_size(canvas_bottom_menu, 700, 120);
		lv_obj_clear_flag(canvas_bottom_menu, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(canvas_bottom_menu, LV_ALIGN_BOTTOM_MID, 0, -10);
		lv_obj_set_style_radius(canvas_bottom_menu,10,LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(canvas_bottom_menu,LV_OPA_50,LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(canvas_bottom_menu,lv_color_hex(0xC9C9CE),LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(canvas_bottom_menu,0,LV_STATE_DEFAULT);
		lv_obj_set_flex_flow(canvas_bottom_menu, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_flex_main_place(canvas_bottom_menu,LV_FLEX_ALIGN_SPACE_EVENLY,LV_STATE_DEFAULT);

		static lv_style_t style_app_icon_cond;
		static lv_style_t style_app_icon_cond_press;
		
		
		lv_style_init(&style_app_icon_cond);
    lv_style_set_bg_opa(&style_app_icon_cond,  LV_OPA_70); // 设置色彩透明度
    lv_style_set_radius(&style_app_icon_cond, 5); // 设置圆角
    lv_style_set_bg_color(&style_app_icon_cond, lv_color_hex(0xFFFFFF)); //设置颜色
	
		lv_style_init(&style_app_icon_cond_press);
    lv_style_set_bg_opa(&style_app_icon_cond_press,  LV_OPA_90); // 设置色彩透明度
    lv_style_set_radius(&style_app_icon_cond_press, 5); // 设置圆角
    lv_style_set_bg_color(&style_app_icon_cond_press, lv_color_hex(0xFFFFFF)); //设置颜色	
		
		
		
		app_weather.app_cond = lv_obj_create(canvas_bottom_menu);
		lv_obj_clear_flag(app_weather.app_cond, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_size(app_weather.app_cond,app_weather.app_cond_w,app_weather.app_cond_h);
		lv_obj_add_style(app_weather.app_cond, &style_app_icon_cond,LV_STATE_DEFAULT);
		lv_obj_add_style(app_weather.app_cond, &style_app_icon_cond_press,LV_STATE_PRESSED);
		
//		lv_obj_fade_in(app_weather.app_cond, 0 , 500);
		lv_obj_center(app_weather.app_cond);
		
		app_weather.app_img = lv_img_create(app_weather.app_cond);
		lv_img_set_src(app_weather.app_img, &ui_img_iconweather64_png);
		lv_obj_align(app_weather.app_img, LV_ALIGN_CENTER, 0, 0);
		
		lv_100ask_page_manager_set_load_page_event(app_weather.app_cond, NULL, "weatherscr");
		
		app_news.app_cond = lv_obj_create(canvas_bottom_menu);
		lv_obj_clear_flag(app_news.app_cond, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_size(app_news.app_cond,app_news.app_cond_w,app_news.app_cond_h);
		lv_obj_add_style(app_news.app_cond, &style_app_icon_cond,LV_STATE_DEFAULT);
		lv_obj_add_style(app_news.app_cond, &style_app_icon_cond_press,LV_STATE_PRESSED);
//		lv_obj_fade_in(app_news.app_cond, 0 , 500);
		lv_obj_center(app_news.app_cond);
		app_news.app_img = lv_img_create(app_news.app_cond);
		lv_img_set_src(app_news.app_img, &ui_img_iconniews64_png);
		lv_obj_align(app_news.app_img, LV_ALIGN_CENTER, 0, 0);
		
		lv_100ask_page_manager_set_load_page_event(app_news.app_cond, NULL, "newsscr");
		
		app_imgs.app_cond = lv_obj_create(canvas_bottom_menu);
		lv_obj_clear_flag(app_imgs.app_cond, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_size(app_imgs.app_cond,app_imgs.app_cond_w,app_imgs.app_cond_h);
		lv_obj_add_style(app_imgs.app_cond, &style_app_icon_cond,LV_STATE_DEFAULT);
		lv_obj_add_style(app_imgs.app_cond, &style_app_icon_cond_press,LV_STATE_PRESSED);

//		lv_obj_fade_in(app_imgs.app_cond, 0 , 500);
		lv_obj_center(app_imgs.app_cond);
		app_imgs.app_img = lv_img_create(app_imgs.app_cond);
		lv_img_set_src(app_imgs.app_img, &ui_img_iconimages64_png);
		lv_obj_align(app_imgs.app_img, LV_ALIGN_CENTER, 0, 0);
		
		
		// only test
		lv_100ask_page_manager_set_load_page_event(app_imgs.app_cond, NULL, "imgscr");
	
		
		app_game.app_cond = lv_obj_create(canvas_bottom_menu);
		lv_obj_clear_flag(app_game.app_cond, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_size(app_game.app_cond,app_game.app_cond_w,app_game.app_cond_h);
		lv_obj_add_style(app_game.app_cond, &style_app_icon_cond,LV_STATE_DEFAULT);
		lv_obj_add_style(app_game.app_cond, &style_app_icon_cond_press,LV_STATE_PRESSED);

//		lv_obj_fade_in(app_game.app_cond, 0 , 500);
		lv_obj_center(app_game.app_cond);
		app_game.app_img = lv_img_create(app_game.app_cond);
		lv_img_set_src(app_game.app_img, &ui_img_icongame2048_png);
		lv_obj_align(app_game.app_img, LV_ALIGN_CENTER, 0, 0);
		lv_100ask_page_manager_set_load_page_event(app_game.app_cond, NULL, "game2048");
		
		app_setting.app_cond = lv_obj_create(canvas_bottom_menu);
		lv_obj_clear_flag(app_setting.app_cond, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_size(app_setting.app_cond,app_setting.app_cond_w,app_setting.app_cond_h);
		lv_obj_add_style(app_setting.app_cond, &style_app_icon_cond,LV_STATE_DEFAULT);
		lv_obj_add_style(app_setting.app_cond, &style_app_icon_cond_press,LV_STATE_PRESSED);

//		lv_obj_fade_in(app_setting.app_cond, 0 , 500);
		lv_obj_center(app_setting.app_cond);
		app_setting.app_img = lv_img_create(app_setting.app_cond);
		lv_img_set_src(app_setting.app_img, &ui_img_iconsetting64_png);
		lv_obj_align(app_setting.app_img, LV_ALIGN_CENTER, 0, 0);
		lv_100ask_page_manager_set_load_page_event(app_setting.app_cond, NULL, "settingscr");

			
			
}
	



//桌面返回悬浮球
static void lv_desktop_backbtn_create(lv_obj_t * parent)
{


    dm.menubtn_parent = parent;




    dm.menubtn = lv_obj_create(parent);
    lv_obj_remove_style_all(dm.menubtn);                          /*Remove the style coming from the theme*/
    lv_obj_add_style(dm.menubtn, &menubtnstyle, 0);
    lv_obj_add_style(dm.menubtn, &style_pr, LV_STATE_PRESSED);
    //lv_obj_set_size(back_btn, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_size(dm.menubtn, LV_BACKBTN_SIZE, LV_BACKBTN_SIZE);
    // lv_obj_align(dm.menubtn,LV_ALIGN_LEFT_MID,0,0);

    lv_obj_set_pos(dm.menubtn,0,((LV_VER_RES/2)-(LV_BACKBTN_SIZE/2)));
    
    lv_obj_add_flag(dm.menubtn, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_t * label = lv_label_create(dm.menubtn);
    lv_label_set_text(label, "MENU");
    lv_obj_center(label);

    dm.menubtn_pos_x = lv_obj_get_x(dm.menubtn);
    dm.menubtn_pos_y = lv_obj_get_y(dm.menubtn);

    lv_obj_add_event_cb(dm.menubtn, lv_backbtn_event_cb, LV_EVENT_CLICKED, (void*)&dm);  
    lv_obj_add_event_cb(dm.menubtn, lv_backbtn_event_cb, LV_EVENT_PRESSING, (void*)&dm);   

}


// 清除悬浮球子菜单中的按钮
static void lv_backbtn_menu_clear(desktop_menubtn_t *dm_t)
{
    if(!dm_t)
    {
//        printf("%s error\n",__FUNCTION__);
        return ;
    }
    // dm_t->btnMenuState = false;

    if(dm_t->backscreenbtn !=NULL)
    {
        //lv_obj_clean(dm_t->backscreenbtn);
        lv_obj_del(dm_t->backscreenbtn);
        dm_t->backscreenbtn=NULL;
    }
    if(dm_t->musicsceen_btn !=NULL)
    {
        lv_obj_del(dm_t->musicsceen_btn);
        dm_t->musicsceen_btn=NULL;
    }
    if(dm_t->timesceen_btn !=NULL)
    {
        lv_obj_del(dm_t->timesceen_btn);
        dm_t->timesceen_btn=NULL;
    }
    if(dm_t->weatherscreen_btn !=NULL)
    {
        lv_obj_del(dm_t->weatherscreen_btn);
        dm_t->weatherscreen_btn=NULL;
    }


}

// 创建桌面悬浮球弹出菜单
// 返回上一级  时钟 音乐 天气
static void lv_backbtn_menu_create(desktop_menubtn_t *dm_t)
{
    int align_x=LV_MENU_BTN_SIZE-(LV_MENU_BTN_SIZE/2);
    int align_y=LV_MENU_BTN_SIZE;
    if(!dm_t)
    {
        // 用 lvgl log 替换
//        printf("error\r\n");
        return ;
    }
    
    // 计算子菜单显示的相对坐标位置
    if((dm_t->menubtn_pos_x>LV_HOR_RES/2) && (dm_t->menubtn_pos_x< LV_HOR_RES))
    {
        align_x = (-LV_MENU_BTN_SIZE-LV_BACKBTN_SIZE-LV_MENU_BTN_SIZE/2);
    }
    else if((dm_t->menubtn_pos_x>0) && (dm_t->menubtn_pos_x<= LV_HOR_RES/2))
    {
        align_x=LV_MENU_BTN_SIZE-(LV_MENU_BTN_SIZE/2);
    }


    if(dm_t->backscreenbtn == NULL)
    {
        dm_t->backscreenbtn = lv_obj_create(dm_t->menubtn_parent);
        lv_obj_remove_style_all(dm_t->backscreenbtn);                          /*Remove the style coming from the theme*/
        lv_obj_add_style(dm_t->backscreenbtn, &btnstyle, 0);
        // lv_obj_add_style(backscreen_btn, &style_pr, LV_STATE_PRESSED);
        //lv_obj_set_size(back_btn, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_size(dm_t->backscreenbtn, LV_MENU_BTN_SIZE, LV_MENU_BTN_SIZE);
        //lv_obj_align(back_btn, LV_ALIGN_RIGHT_MID, -60, -200);
        lv_obj_add_flag(dm_t->backscreenbtn, LV_OBJ_FLAG_CLICKABLE);

        lv_obj_add_style(dm_t->backscreenbtn, &btn_style_pr, LV_STATE_PRESSED);

        //相对位置偏移
        lv_obj_align_to(dm_t->backscreenbtn,dm_t->menubtn,LV_ALIGN_OUT_RIGHT_MID,align_x,0);
        lv_obj_t * label = lv_label_create(dm_t->backscreenbtn);
        lv_label_set_text(label, LV_SYMBOL_LEFT);
        lv_obj_center(label);
    }


    if(dm_t->timesceen_btn == NULL)
    {
        dm_t->timesceen_btn = lv_obj_create(dm_t->menubtn_parent);
        lv_obj_remove_style_all(dm_t->timesceen_btn);                          /*Remove the style coming from the theme*/
        lv_obj_add_style(dm_t->timesceen_btn, &btnstyle, 0);
        lv_obj_set_size(dm_t->timesceen_btn, LV_MENU_BTN_SIZE, LV_MENU_BTN_SIZE);
        lv_obj_add_flag(dm_t->timesceen_btn, LV_OBJ_FLAG_CLICKABLE);


        lv_obj_add_style(dm_t->timesceen_btn, &btn_style_pr, LV_STATE_PRESSED);
        //相对位置偏移
        lv_obj_align_to(dm_t->timesceen_btn,dm_t->menubtn,LV_ALIGN_OUT_RIGHT_MID,align_x,-LV_MENU_BTN_SIZE-5);
        lv_obj_t * label = lv_label_create(dm_t->timesceen_btn);
        lv_label_set_text(label, LV_SYMBOL_IMAGE);
        lv_obj_center(label);
    }

    if(dm_t->musicsceen_btn == NULL)
    {
        dm_t->musicsceen_btn = lv_obj_create(dm_t->menubtn_parent);
        lv_obj_remove_style_all(dm_t->musicsceen_btn);                          /*Remove the style coming from the theme*/
        lv_obj_add_style(dm_t->musicsceen_btn, &btnstyle, 0);
        lv_obj_set_size(dm_t->musicsceen_btn, LV_MENU_BTN_SIZE, LV_MENU_BTN_SIZE);
        lv_obj_add_flag(dm_t->musicsceen_btn, LV_OBJ_FLAG_CLICKABLE);


        lv_obj_add_style(dm_t->musicsceen_btn, &btn_style_pr, LV_STATE_PRESSED);
        //相对位置偏移
        lv_obj_align_to(dm_t->musicsceen_btn,dm_t->menubtn,LV_ALIGN_OUT_RIGHT_MID,align_x,LV_MENU_BTN_SIZE+5);
        lv_obj_t * label = lv_label_create(dm_t->musicsceen_btn);
        lv_label_set_text(label, LV_SYMBOL_AUDIO);
        lv_obj_center(label);
    }

    if(dm_t->weatherscreen_btn == NULL)
    {
        dm_t->weatherscreen_btn = lv_obj_create(dm_t->menubtn_parent);
        lv_obj_remove_style_all(dm_t->weatherscreen_btn); 
        lv_obj_add_style(dm_t->weatherscreen_btn, &btnstyle, 0);
        lv_obj_set_size(dm_t->weatherscreen_btn, LV_MENU_BTN_SIZE, LV_MENU_BTN_SIZE);
        lv_obj_add_flag(dm_t->weatherscreen_btn, LV_OBJ_FLAG_CLICKABLE);


        lv_obj_add_style(dm_t->weatherscreen_btn, &btn_style_pr, LV_STATE_PRESSED);
        //相对位置偏移
        lv_obj_align_to(dm_t->weatherscreen_btn,dm_t->menubtn,LV_ALIGN_OUT_RIGHT_MID,align_x,LV_MENU_BTN_SIZE*2+10);
        lv_obj_t * label = lv_label_create(dm_t->weatherscreen_btn);
        lv_label_set_text(label, LV_SYMBOL_IMAGE);
        lv_obj_center(label);
    }

    

    // if (show_flag) {
    //     lv_obj_clear_flag(dm_t->backscreenbtn, LV_OBJ_FLAG_HIDDEN); // 隐藏
    // } else {
    //     lv_obj_add_flag(dm_t->backscreenbtn, LV_OBJ_FLAG_HIDDEN);
    // }
}


static void lv_backbtn_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    //lv_obj_t *parent = (lv_obj_t*)lv_event_get_user_data(e);

    desktop_menubtn_t *dm_t = (desktop_menubtn_t *)lv_event_get_user_data(e);

    if (code == LV_EVENT_CLICKED)
    {
        // 加载悬浮球子菜单
        dm_t->btnMenuState = dm_t->btnMenuState ? false : true;
        if(dm_t->btnMenuState)
        {
            lv_backbtn_menu_create(dm_t);
        }
        else
        {
            lv_backbtn_menu_clear(dm_t);
        }
        
    }
    else if(code == LV_EVENT_PRESSING)
    {
        lv_backbtn_menu_clear(dm_t);
        lv_obj_t * obj = lv_event_get_target(e);
        //获取触摸输入设备的矢量偏移
        lv_indev_t * indev = lv_indev_get_act();
        if(indev == NULL)  return;

        lv_point_t vect;
        lv_indev_get_vect(indev, &vect);

        lv_coord_t x = lv_obj_get_x(obj) + vect.x;
        lv_coord_t y = lv_obj_get_y(obj) + vect.y;
        lv_obj_set_pos(obj, x, y);
        //更新悬浮球的坐标
        dm_t->menubtn_pos_x = x;
        dm_t->menubtn_pos_y = y;
    }
}