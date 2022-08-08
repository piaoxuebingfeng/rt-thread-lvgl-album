/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-18     Meco Man      First version
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#define LV_USE_PERF_MONITOR     1
#define LV_COLOR_DEPTH          16

#define LV_USE_GPU_STM32_DMA2D  1
#define LV_GPU_DMA2D_CMSIS_INCLUDE "stm32f469xx.h"

#define LV_DISP_DEF_REFR_PERIOD 20

//#define LV_MEM_CUSTOM 0
//#  define LV_MEM_SIZE    (64U * 1024U)

/* music player demo */
#define LV_HOR_RES_MAX              800
#define LV_VER_RES_MAX              480
//#define LV_USE_DEMO_RTT_MUSIC       1
//#define LV_DEMO_RTT_MUSIC_AUTO_PLAY 1
#define LV_FONT_MONTSERRAT_12       1
#define LV_FONT_MONTSERRAT_16       1
#define LV_FONT_MONTSERRAT_24       1
#define LV_FONT_MONTSERRAT_48       1
 

// lv_100ask_sketchpad_simple_test
//#define LV_USE_FLEX 0
#define LV_USE_CANVAS 1

// lv_100ask_calc_simple_test  
#define LV_FONT_MONTSERRAT_20 1
#define LV_FONT_MONTSERRAT_18 1


//#define LV_USE_FREETYPE 1


#define LV_USE_SJPG 1
#endif
