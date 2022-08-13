// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: news_page

#include "newspageui.h"
#include "dfs.h"
#include "fcntl.h"
#include "unistd.h"
#include <cJSON.h>
#include "guiconf.h"  

#define DBG_ENABLE
#define DBG_SECTION_NAME               "lvgl.gui"
#define DBG_LEVEL                      DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>



///////////////////// VARIABLES ////////////////////
static lv_obj_t * ui_ScreenNews;
static lv_obj_t * ui_topstatuspanel;
static lv_obj_t * ui_img_location;
static lv_obj_t * ui_Label3;
static lv_obj_t * ui_newspanel;
static lv_obj_t * ui_newstitle;
static lv_obj_t * ui_news_title_index;
static lv_obj_t * ui_news_time_label;
static lv_obj_t * ui_newslabel;
static lv_obj_t * ui_Panel3;
static lv_obj_t * ui_timeshow_label;


static int news_show_count =0;


//static lv_obj_t * ui_Label1;
LV_FONT_DECLARE(HarmonyOS_Sans_SC_Medium);

LV_IMG_DECLARE(ui_img_iconlocation16_png);

///////////////////// TEST LVGL SETTINGS ////////////////////
// #if LV_COLOR_DEPTH != 16
//     #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
// #endif
// #if LV_COLOR_16_SWAP !=0
//     #error "#error LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
// #endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////


#define NEWS_FILE "/tmp/news.txt";



news_t *news_head = RT_NULL;
char *news_mem_buffer = RT_NULL; 
static cJSON *news_json_root = RT_NULL, *object = RT_NULL, *item = RT_NULL;
static cJSON *newslistarray = RT_NULL;

// 初始化新闻列表
void news_list_init()
{
		const char *newsfile="/tmp/news.txt";
		int read_len;
		int total_length;
		int ret;
		int fd;
		int news_num=0;
		int i;
		struct stat file_stat;
		news_t *news_point = RT_NULL;
		news_t *news_p = RT_NULL;
		
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
	
		news_mem_buffer = (char *)rt_malloc(total_length*sizeof(char));
		if (news_mem_buffer == RT_NULL)
		{
				LOG_E("news_mem_buffer malloc failed \n");
				goto __exit;
		}
		read_len = read(fd,news_mem_buffer,total_length);
		LOG_I("read data len from file %s :%d\n",newsfile,read_len);
		
		
	
		news_json_root = cJSON_Parse((const char *)news_mem_buffer);
    if (!news_json_root)
    {
        rt_kprintf("No memory for cJSON root!\n");
        return;
    }
		
		//LOG_I("------------------------------------------------------\n");
		//LOG_I("  parse news  \n");
		newslistarray = cJSON_GetObjectItem(news_json_root,"newslist");
		
		news_num = cJSON_GetArraySize(newslistarray);
		
		for(i=0;i<news_num;i++)
		{
			
				news_point =  (news_t *)rt_malloc(sizeof(news_t));
				if(news_point == RT_NULL)
				{
					LOG_E("news_point malloc failed \n");
					goto __exit;
				}
				
				news_point->news_list_count = i;
				news_point->news_list_num = news_num;	
				object = cJSON_GetArrayItem(newslistarray,i);
				item = cJSON_GetObjectItem(object,"mtime");
				news_point->news_mtime = item->valuestring;
				item = cJSON_GetObjectItem(object,"title");
				news_point->news_title = item->valuestring;
				item = cJSON_GetObjectItem(object,"digest");
				news_point->news_digest = item->valuestring;				
				news_point->next = RT_NULL;
				
				if(news_head==RT_NULL)
				{
					news_head = news_point;
					news_p = news_head;
				}
				else
				{
					while(news_p->next!=RT_NULL)
					{
						news_p = news_p->next;
					}
					news_p->next = news_point;
				}
		}
__exit:
		
		if(fd)
		{
			close(fd);
		}
		return ;
}


// 遍历显示新闻列表

void news_list_show()
{
	news_t *news_p = news_head;
	news_t *news_q =news_p;

	while(news_q && news_q->next!=RT_NULL)
	{
		//test 
		rt_kprintf("---------------------------------------\n\n");
		LOG_I("news list count : %d\n",news_q->news_list_count);
		LOG_I("news list mtime : %s\n",news_q->news_mtime);
		LOG_I("news list title : %s\n",news_q->news_title);
		rt_kprintf("---------------------------------------\n\n");
		news_q = news_q->next;
	}
	return ;
}



// 删除新闻列表
void news_list_deinit()
{
		news_t *news_p = news_head;
		news_t *news_q =RT_NULL;
		
		// 清除单项链表
		while(news_p)
		{
			news_q = news_p->next;
			rt_free(news_p);
			news_p = news_q;
		}
		news_head = RT_NULL;
	
		if(news_json_root)
		{
			cJSON_Delete(news_json_root);
			news_json_root= RT_NULL;
		}
		// 清除内存中的新闻数据
		if(news_mem_buffer !=RT_NULL)
		{
				rt_free(news_mem_buffer);
			news_mem_buffer=NULL;
		}
		
}






void ui_set_news_title(const char * buf)
{
		if(buf == RT_NULL)
		{
			return;
		}
		if(ui_news_title_index)
		{
			lv_label_set_text(ui_news_title_index,buf);
		}		
}

void ui_set_news_time(const char *buf)
{
	
	if(buf == RT_NULL)
	{
		return;
	}
	if(ui_news_time_label)
	{
		lv_label_set_text(ui_news_time_label,buf);
	}		
}


void ui_set_news_digest(const char * buf)
{
		if(buf == RT_NULL)
		{
			return;
		}
		if(ui_newslabel)
		{
			lv_label_set_text(ui_newslabel,buf);
		}		
}


void ui_news_set_time(const char *buf)
{
	if(buf == RT_NULL)
	{
		return ;
	}
	if(ui_timeshow_label)
	{
		lv_label_set_text(ui_timeshow_label, buf);
	}
	
}



static void newsdata_parse(rt_uint8_t *data,int news_index)
{
		cJSON *root = RT_NULL, *object = RT_NULL, *item = RT_NULL;
		cJSON *newslistarray = RT_NULL;
		int news_num=0;
		int i=0;
		if(RT_NULL == data)
		{
			rt_kprintf("news data is null\r\n");
			return ;
		}
	
    root = cJSON_Parse((const char *)data);
    if (!root)
    {
        rt_kprintf("No memory for cJSON root!\n");
        return;
    }
		
		LOG_I("------------------------------------------------------\n");
		LOG_I("  parse news  \n");
		newslistarray = cJSON_GetObjectItem(root,"newslist");
		news_num = cJSON_GetArraySize(newslistarray);
		
		LOG_I("get news num :%d\n",news_num);
		if(news_num>0)
		{
//			for(i=0;i<news_num;i++)
//			{
//					object = cJSON_GetArrayItem(newslistarray,i);
//					item = cJSON_GetObjectItem(object,"mtime");
//					rt_kprintf("mtime : %s \n\n",item->valuestring);
//				
//					item = cJSON_GetObjectItem(object,"title");
//					rt_kprintf("title : %s \n\n",item->valuestring);
//				
//					item = cJSON_GetObjectItem(object,"digest");
//					rt_kprintf("digest : %s \n\n",item->valuestring);
//			}
			

				object = cJSON_GetArrayItem(newslistarray,news_index);
				item = cJSON_GetObjectItem(object,"mtime");
				rt_kprintf("mtime : %s \n\n",item->valuestring);
				ui_set_news_time(item->valuestring);
			
				item = cJSON_GetObjectItem(object,"title");
				rt_kprintf("title : %s \n\n",item->valuestring);
			
				ui_set_news_title(item->valuestring);


				item = cJSON_GetObjectItem(object,"digest");
				rt_kprintf("digest : %s \n\n",item->valuestring);
				ui_set_news_digest(item->valuestring);
		}
		LOG_I("------------------------------------------------------\n");
		if (root != RT_NULL)
			cJSON_Delete(root);
	
}

static void show_news(int news_num)
{
		const char *newsfile="/tmp/news.txt";
		unsigned char *readfile_buf = RT_NULL;
		int read_len;
		int total_length;
		int ret;
		int fd;
		struct stat file_stat;
	
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
		

		readfile_buf = (unsigned char *)rt_malloc(total_length*sizeof(unsigned char));
		if (readfile_buf == RT_NULL)
		{
				LOG_E("readfile_buf malloc failed \n");
		}
		read_len = read(fd,readfile_buf,total_length);
		LOG_I("read data len from file %s :%d\n",newsfile,read_len);
		LOG_I("news data is :\n\n");
		//LOG_I("%s",readfile_buf);
		rt_kprintf("%s", readfile_buf);
		LOG_I("\n\n");
		
		// 解析新闻 json 字符串  解析出来第一条新闻并显示
		newsdata_parse(readfile_buf,news_num);
		
		
		close(fd);
		if(readfile_buf !=RT_NULL)
		{
				rt_free(readfile_buf);
		}
}



void news_str_update()
{
	extern int webclient_get_news(const char* URI);
	news_t *news_p = news_head;
	news_t *news_q =news_p;
	const char *news_uri_base="http://api.tianapi.com/bulletin/index?key=";
	char news_uri[200]={0};
	
	rt_memset(news_uri,0,200);
	rt_sprintf(news_uri,"%s%s",news_uri_base,guiconf_global.apikey);
	
	webclient_get_news(news_uri);
	news_list_deinit();
	news_list_init();
	news_show_count =0 ;
	news_p = news_head;
	news_q = news_p;

}

void news_show_update()
{
	news_t *news_p = news_head;
	news_t *news_q =news_p;

	while(news_q && (news_q->news_list_count !=news_show_count))
	{
		news_q = news_q->next;
	}
	if(news_q->news_list_count == news_show_count)
	{
		ui_set_news_title(news_q->news_title);
		ui_set_news_time(news_q->news_mtime);
		ui_set_news_digest(news_q->news_digest);
		news_show_count++;
		if(news_show_count >= news_q->news_list_num)
		{
			news_show_count = 0;
		}
	}
}





///////////////////// SCREENS ////////////////////

void ui_news_page_screen_init(lv_obj_t *parent)
{

    // ui_ScreenNews

    ui_ScreenNews = lv_obj_create(parent);

    lv_obj_clear_flag(ui_ScreenNews, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(ui_ScreenNews, LV_HOR_RES, LV_VER_RES);       // 设置到屏幕大小
    lv_obj_set_style_bg_color(ui_ScreenNews, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui_ScreenNews, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenNews, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_ScreenNews, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_ScreenNews, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ScreenNews, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_center(ui_ScreenNews);

//    // ui_topstatuspanel

//    ui_topstatuspanel = lv_obj_create(ui_ScreenNews);

//    lv_obj_set_width(ui_topstatuspanel, 800);
//    lv_obj_set_height(ui_topstatuspanel, 32);

//    lv_obj_set_x(ui_topstatuspanel, 0);
//    lv_obj_set_y(ui_topstatuspanel, -224);

//    lv_obj_set_align(ui_topstatuspanel, LV_ALIGN_CENTER);

//    lv_obj_clear_flag(ui_topstatuspanel, LV_OBJ_FLAG_SCROLLABLE);

//    lv_obj_set_style_radius(ui_topstatuspanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_color(ui_topstatuspanel, lv_color_hex(0x646464), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_opa(ui_topstatuspanel, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_border_width(ui_topstatuspanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);


//		// ui_img_location
//		
//		ui_img_location = lv_img_create(ui_topstatuspanel);
//		lv_img_set_src(ui_img_location,&ui_img_iconlocation16_png);
//		lv_obj_set_x(ui_img_location, -370);
//    lv_obj_set_y(ui_img_location, 0);
//		lv_obj_set_align(ui_img_location, LV_ALIGN_CENTER);
//		
//    // ui_Label3

//    ui_Label3 = lv_label_create(ui_topstatuspanel);

//    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);
//    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);

//    lv_obj_set_x(ui_Label3, -340);
//    lv_obj_set_y(ui_Label3, 0);

//    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);

//    lv_label_set_text(ui_Label3, "郑州");
//		lv_obj_set_style_text_color(ui_Label3,lv_color_hex(0xFFFFFF),LV_STATE_DEFAULT);
//    lv_obj_set_style_text_font(ui_Label3, &HarmonyOS_Sans_SC_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);
//		
//    ui_timeshow_label = lv_label_create(ui_topstatuspanel);

//    lv_obj_set_width(ui_timeshow_label, LV_SIZE_CONTENT);
//    lv_obj_set_height(ui_timeshow_label, LV_SIZE_CONTENT);

//    lv_obj_set_x(ui_timeshow_label,0);
//    lv_obj_set_y(ui_timeshow_label, 0);

//    lv_obj_set_align(ui_timeshow_label, LV_ALIGN_CENTER);

//		lv_label_set_text(ui_timeshow_label, "08:00");
//		lv_obj_set_style_text_color(ui_timeshow_label,lv_color_hex(0xFFFFFF),LV_STATE_DEFAULT);
//    lv_obj_set_style_text_font(ui_timeshow_label, &HarmonyOS_Sans_SC_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);
//		

    // ui_newspanel

    ui_newspanel = lv_obj_create(ui_ScreenNews);

    lv_obj_set_width(ui_newspanel, 790);
    lv_obj_set_height(ui_newspanel, 430);

    lv_obj_set_x(ui_newspanel, 0);
    lv_obj_set_y(ui_newspanel, 20);

    lv_obj_set_align(ui_newspanel, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_newspanel, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_radius(ui_newspanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_newspanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_newspanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_newspanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_newspanel, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_newspanel, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_newstitle

    ui_newstitle = lv_label_create(ui_newspanel);

    lv_obj_set_width(ui_newstitle, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_newstitle, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_newstitle, 0);
    lv_obj_set_y(ui_newstitle, -195);

    lv_obj_set_align(ui_newstitle, LV_ALIGN_CENTER);

    lv_label_set_text(ui_newstitle, "每日新闻");

    lv_obj_set_style_text_font(ui_newstitle, &ui_font_lishu24, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_color(ui_newstitle,lv_color_hex(0xFFFFFF),LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_newstitle, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_newstitle, lv_color_hex(0xFF0019), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_newstitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_newstitle, lv_color_hex(0xFF0019), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_newstitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_newstitle, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
		
		
		
		// ui_news_title_index
		ui_news_title_index = lv_label_create(ui_newspanel);
    lv_obj_set_width(ui_news_title_index, 770);
    lv_obj_set_height(ui_news_title_index, 30);
    lv_obj_set_x(ui_news_title_index, 0);
    lv_obj_set_y(ui_news_title_index, -160);
		lv_obj_set_align(ui_news_title_index, LV_ALIGN_CENTER);
		
		lv_label_set_long_mode(ui_news_title_index,LV_LABEL_LONG_SCROLL_CIRCULAR );
    lv_obj_set_style_text_color(ui_news_title_index, lv_color_hex(0xE6E6E6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_news_title_index, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_news_title_index, &HarmonyOS_Sans_SC_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);
		
    lv_label_set_text(ui_news_title_index,"新闻标题");
		
		
		 
		
		ui_news_time_label = lv_label_create(ui_newspanel);
    lv_obj_set_width(ui_news_time_label, 770);
    lv_obj_set_height(ui_news_time_label, 30);
    lv_obj_set_x(ui_news_time_label, 0);
    lv_obj_set_y(ui_news_time_label, -120);
		lv_obj_set_align(ui_news_time_label, LV_ALIGN_CENTER);
		
		lv_label_set_long_mode(ui_news_time_label,LV_LABEL_LONG_SCROLL_CIRCULAR );
    lv_obj_set_style_text_color(ui_news_time_label, lv_color_hex(0xE6E6E6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_news_time_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_news_time_label, &HarmonyOS_Sans_SC_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);
		
    lv_label_set_text(ui_news_time_label,"2022/7/27 18:00");
		
    // ui_newslabel

    ui_newslabel = lv_label_create(ui_newspanel);

    lv_obj_set_width(ui_newslabel, 770);
    lv_obj_set_height(ui_newslabel, 400);

    lv_obj_set_x(ui_newslabel, 0);
    lv_obj_set_y(ui_newslabel, 90);

    lv_obj_set_align(ui_newslabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_newslabel,
                      "新闻内容");

    lv_obj_set_style_text_color(ui_newslabel, lv_color_hex(0xE6E6E6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_newslabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_newslabel, &HarmonyOS_Sans_SC_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);


		news_show_update();
}

