/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-17     Meco Man      First version
 */
#include <rtthread.h>
#include <lvgl.h>
#include <lv_port_indev.h>
#define DBG_TAG    "LVGL.demo"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>
#include "lv_lib_100ask_conf.h"
//#include "lv_lib_100ask.h"
#include "my_desktop_page_mgt_test.h"
#ifndef LV_THREAD_STACK_SIZE
    #define LV_THREAD_STACK_SIZE 4096
#endif

#ifndef LV_THREAD_PRIO
    #define LV_THREAD_PRIO (RT_THREAD_PRIORITY_MAX * 2 / 8)
#endif

static struct rt_thread lvgl_thread;
static rt_uint8_t lvgl_thread_stack[LV_THREAD_STACK_SIZE];

static void lvgl_entry(void *parameter)
{
//    extern void lv_demo_music(void);
//    lv_demo_music();

	
		
		rt_kprintf("start lvgl demo test\r\n");
	
//		extern void lv_desktop(void);
//		lv_desktop();
	
//		extern void lv_desktop_backbtn_test(void);
//		lv_desktop_backbtn_test();
//		extern void clocktime_update_timer_task_init(void);
//		clocktime_update_timer_task_init();

//	lv_100ask_sketchpad_simple_test();
//		lv_100ask_calc_simple_test();
	
//		lv_100ask_page_manager_simple_test();
		lv_my_desktop_page_mgt_test();
    while(1)
    {
        lv_task_handler();
        rt_thread_mdelay(5);
    }
}

int lvgl_demo_init(void)
{
    rt_thread_t tid;
		//等待文件系统挂载完成
		rt_thread_mdelay(1000);
  
		rt_thread_init(&lvgl_thread,
                   "LVGL",
                   lvgl_entry,
                   RT_NULL,
                   &lvgl_thread_stack[0],
                   sizeof(lvgl_thread_stack),
                   LV_THREAD_PRIO,
                   10);
    rt_thread_startup(&lvgl_thread);

    return 0;
}
//INIT_APP_EXPORT(lvgl_demo_init);
