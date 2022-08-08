/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 * 2019-04-09     WillianChan  add stm32f469-st-disco bsp
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>


#include <sys/time.h>
#include <string.h>


#include "fcntl.h"
#include "unistd.h"


#if defined(RT_USING_SAL)
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#endif

#if defined(RT_USING_NETDEV)
#include <netdev.h>
#endif

#include"my_desktop_page_mgt_test.h"
#include "newspageui.h"


#include "guiconf.h"  

#include "dfs.h"
#include "fcntl.h"
#include "unistd.h"


#define DBG_ENABLE
#define DBG_SECTION_NAME               "main"
#define DBG_LEVEL                      DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>



int lv_gui_update(const char *news_uri);


//---------------------------------------------------------------------------------------------------------
void imgs_list_init();
void imgs_list_deinit();
void imgs_list_show();
//---------------------------------------------------------------------------------------------------------


/* defined the LED1 pin: PG6 */
#define LED1_PIN    GET_PIN(G, 6)  // green led
#define LED2_PIN    GET_PIN(D, 4)  // orange 
#define LED3_PIN    GET_PIN(D, 5)  // red
#define LED4_PIN    GET_PIN(K, 3)  // blue

static rt_bool_t loop_check_network(void);


extern int webclient_get_news(const char* URI);


// �Զ����ʼ������

//#define INIT_APP_EXPORT(fn)             INIT_EXPORT(fn, "6")
// ���ԣ���Ҳ����ֱ����INIT_EXPORT�����Ƶȼ������������"6.1", "6.2"�ȵ�

//INIT_APP_EXPORT(stm32_sdcard_mount);
//INIT_APP_EXPORT(esp32_device_register);
extern void stm32_sdcard_mount(void);
extern int esp32_device_register(void);
extern int lvgl_demo_init(void);

void rtt_app_init()
{
	
	rt_kprintf("self  rtt app init \n");
	stm32_sdcard_mount();
	
	rt_thread_mdelay(3000);
	guiconf_read(&guiconf_global);
		
	guiconf_print(&guiconf_global);
	
	esp32_device_register();
	
	lvgl_demo_init();
}

	


int main(void)
{
    /* set LED1 pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
		rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
//		int i2c1_scl_pn ;
//		int i2c1_sda_pn ;
		const char *news_uri_base="http://api.tianapi.com/bulletin/index?key=";
		char news_uri[200]={0};

	
	
//		i2c1_scl_pn = rt_pin_get("PB.8");
//		i2c1_sda_pn = rt_pin_get("PB.9");
//	
//		rt_kprintf("test gpio pin\r\n");
//	
//		rt_kprintf("i2c1_scl_pn %d i2c1_sda_pn  %d\r\n",i2c1_scl_pn, i2c1_sda_pn );
	

		rtt_app_init();
		
		
		rt_memset(news_uri,0,200);
		rt_sprintf(news_uri,"%s%s",news_uri_base,guiconf_global.apikey);
		
		//LOG_I("news_uri is %s\n",news_uri);
		
		if(loop_check_network())
		{

			webclient_get_news(news_uri);
		}

		
		news_list_init();
		
		// just test
		imgs_list_init();
		imgs_list_show();
    while (1)
    {
        rt_pin_write(LED1_PIN, PIN_HIGH);
				rt_pin_write(LED2_PIN, PIN_LOW);
        rt_thread_mdelay(400);
        rt_pin_write(LED1_PIN, PIN_LOW);
				rt_pin_write(LED2_PIN, PIN_HIGH);
        rt_thread_mdelay(450);
//				lv_gui_update(news_uri);
			
			lv_desktop_gui_page_update();
    }
		
		news_list_deinit();
		
		imgs_list_deinit();
}






// gui update
// ��ʱ���� gui ����

// ʱ����� ��ͼƬ���� �����Ÿ���

// ����״̬���� 




static rt_bool_t loop_check_network(void)
{
#ifdef RT_USING_NETDEV
    struct netdev * netdev = netdev_get_by_family(AF_INET);
    return (netdev && netdev_is_link_up(netdev));
#else
    return RT_TRUE;
#endif
}





int lv_gui_update(const char *news_uri)
{
	char clocktime[10]={0};   
	time_t now;
	struct tm *p;
	now = time(RT_NULL);
	p = localtime(&now); 
	static int news_show_count =0;
	news_t *news_p = news_head;
	news_t *news_q =news_p;
	lv_obj_t *cur_scr ;
	
		//�жϵ�ǰҳ�����ĸ�ҳ�棬Ȼ�����������
	
		cur_scr = lv_scr_act();
		if(cur_scr)
		{
			
		}
		if(loop_check_network())
		{

			if(p)
			{

				rt_snprintf(clocktime,10,"%02d:%02d",p->tm_hour,p->tm_min);
//				// ����ʱ��
//				lv_clock_set_time(clocktime);
				lv_clock_label_update(p->tm_hour,p->tm_min,p->tm_sec);
//				// ��������
//				lv_clock_calendar_set_date(p->tm_year+1900, p->tm_mon+1, p->tm_mday);
				
				if( p->tm_hour >7 && p->tm_hour < 23 && p->tm_min!=0 &&  p->tm_min %50==0 && p->tm_sec!=0 && p->tm_sec%50==0)
				{
					LOG_I("update news\r\n");
					webclient_get_news(news_uri);
					
					LOG_I("news list update \r\n");
					news_list_deinit();
					news_list_init();
					news_show_count =0 ;
					news_p = news_head;
					news_q = news_p;
					
				}
				if(p->tm_sec %30 ==0)
				{
					while(news_q && (news_q->news_list_count !=news_show_count))
					{
						news_q = news_q->next;
					}
					if(news_q->news_list_count == news_show_count)
					{
						LOG_I("[ %d/%d %d:%d:%d ] total news num :%d , current news :%d\n",p->tm_mon+1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec,news_q->news_list_num,news_show_count);
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
			}	
		}
		else
		{
////			rt_kprintf("network is not link up\n");
		}

	return 0;
}


//---------------------------------------------------------------------------------------------------------

typedef struct imgs_mgt_s imgs_mgt_t;


struct imgs_mgt_s
{
	int imgs_count;
	int imgs_total_nums;
	char *imgs_path;
	char *imgs_lvgl_path;
	
	imgs_mgt_t *next;
};

imgs_mgt_t *imgs_list_head = RT_NULL;





// 读取 SD 卡中图片信息，整理成一个列表，提供给 img page 后续使用
void imgs_list_init()
{
	imgs_mgt_t *imgs_list_p = RT_NULL;	
	imgs_mgt_t *imgs_list_q = RT_NULL;	
	DIR *dirp;
	struct dirent *d;
	int imgs_count =0;
	int imgs_total_nums =0;
	int len=0;
	

	/* 打开 / dir_test 目录 */
	dirp = opendir("/imgs");
	if (dirp == RT_NULL)
	{
			rt_kprintf("open directory error!\n");
	}
	else
	{
			
			/* 读取目录 */
			while ((d = readdir(dirp)) != RT_NULL)
			{
				//rt_kprintf("found %s\n", d->d_name);
				imgs_total_nums++;
			}
			/* 关闭目录 */
			closedir(dirp);
	}
	
	rt_kprintf("img total nums :%d\n",imgs_total_nums);
	
	/* 打开 / dir_test 目录 */
	dirp = opendir("/imgs");
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
				
				rt_sprintf(imgs_list_p->imgs_path,"/imgs/%s",d->d_name);
				rt_sprintf(imgs_list_p->imgs_lvgl_path,"S:imgs/%s",d->d_name);
				imgs_count++;
				imgs_list_p->imgs_count      =  imgs_count;
				imgs_list_p->imgs_total_nums =  imgs_total_nums;
				imgs_list_p->next = RT_NULL;
				rt_kprintf("[%d/%d] %s  \n",imgs_list_p->imgs_count,imgs_list_p->imgs_total_nums,imgs_list_p->imgs_path );

				// 向链表中新增节点
				if(imgs_list_head == RT_NULL)
				{
					imgs_list_head = imgs_list_p;
					imgs_list_q = imgs_list_head;
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


void imgs_list_show()
{
	imgs_mgt_t *imgs_list_p = imgs_list_head;
	imgs_mgt_t *imgs_list_q= imgs_list_p;
	
	if(imgs_list_q != RT_NULL)
	{
		//while(imgs_list_q  && imgs_list_q->next!=RT_NULL)
		while(imgs_list_q)
		{
			rt_kprintf("[%d/%d]   %s  \n",imgs_list_q->imgs_count,imgs_list_q->imgs_total_nums,imgs_list_q->imgs_lvgl_path);
			imgs_list_q = imgs_list_q->next;
		}
	}
}



void imgs_list_deinit()
{
	imgs_mgt_t *imgs_list_p = imgs_list_head;
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
		imgs_list_head = RT_NULL;
	}
}




// read imgs name 

static void readimgsdir_sample(void)
{
    DIR *dirp;
    struct dirent *d;

    /* 打开 / dir_test 目录 */
    dirp = opendir("/imgs");
    if (dirp == RT_NULL)
    {
        rt_kprintf("open directory error!\n");
    }
    else
    {
        /* 读取目录 */
        while ((d = readdir(dirp)) != RT_NULL)
        {
            rt_kprintf("found %s\n", d->d_name);
        }

        /* 关闭目录 */
        closedir(dirp);
    }
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(readimgsdir_sample, readdir imgs dir sample);




















