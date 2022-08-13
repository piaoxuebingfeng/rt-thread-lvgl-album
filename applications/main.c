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
#include "albumpageui.h"
#include "weatherpageui.h"
#include "guiconf.h"  

#include "dfs.h"
#include "fcntl.h"
#include "unistd.h"


#define DBG_ENABLE
#define DBG_SECTION_NAME               "main"
#define DBG_LEVEL                      DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>


/* defined the LED1 pin: PG6 */
#define LED1_PIN    GET_PIN(G, 6)  // green led
#define LED2_PIN    GET_PIN(D, 4)  // orange 
#define LED3_PIN    GET_PIN(D, 5)  // red
#define LED4_PIN    GET_PIN(K, 3)  // blue

static rt_bool_t loop_check_network(void);


extern int webclient_get_news(const char* URI);

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


	
	
//		i2c1_scl_pn = rt_pin_get("PB.8");
//		i2c1_sda_pn = rt_pin_get("PB.9");
//		rt_kprintf("test gpio pin\r\n");
//		rt_kprintf("i2c1_scl_pn %d i2c1_sda_pn  %d\r\n",i2c1_scl_pn, i2c1_sda_pn );
	

		rtt_app_init();
		

		
		news_list_init();
		
		
		weather_info_init();
		
		
		// just test
		//weather_info_print();
		
		imgs_list_init();
		imgs_set_current_img_node_head();
//		imgs_list_show();

		minimgs_list_init();
		minimgs_set_current_img_node_head();
    while (1)
    {
        rt_pin_write(LED1_PIN, PIN_HIGH);
				rt_pin_write(LED2_PIN, PIN_LOW);
        rt_thread_mdelay(400);
        rt_pin_write(LED1_PIN, PIN_LOW);
				rt_pin_write(LED2_PIN, PIN_HIGH);
        rt_thread_mdelay(450);
			
			lv_desktop_gui_page_update();
    }
		
		news_list_deinit();
		
		imgs_list_deinit();
		minimgs_list_deinit();
}



static rt_bool_t loop_check_network(void)
{
#ifdef RT_USING_NETDEV
    struct netdev * netdev = netdev_get_by_family(AF_INET);
    return (netdev && netdev_is_link_up(netdev));
#else
    return RT_TRUE;
#endif
}


static struct rt_work network_info_sync_work;
static void network_info_sync_work_func(struct rt_work *work, void *work_data)
{
		char weather_uri[200]={0};
    if (loop_check_network())
    {		
			extern int webclient_get_file(const char* URI, const char* filename);
			
			news_str_update();
			
			rt_kprintf("news info update success\n");
			
			rt_memset(weather_uri,0,200);
			rt_sprintf(weather_uri,"%s%s","http://t.weather.sojson.com/api/weather/city/",guiconf_global.cityid);
			webclient_get_file(weather_uri,"/tmp/weather");
			weather_info_init();
			
			rt_kprintf("weather info update success\n");
      //rt_work_submit(work, rt_tick_from_millisecond(3600 * 1000));		
    }
    else
    {
        rt_work_submit(work, rt_tick_from_millisecond(5 * 1000));
    }
}

static int network_info_auto_sync_init(void)
{
    rt_work_init(&network_info_sync_work, network_info_sync_work_func, RT_NULL);
    rt_work_submit(&network_info_sync_work, rt_tick_from_millisecond(40 * 1000));
    return RT_EOK;
}
INIT_COMPONENT_EXPORT(network_info_auto_sync_init);























