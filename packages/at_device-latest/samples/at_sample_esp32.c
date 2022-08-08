/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-10     chenyong     first version
 */

#include <at_device_esp32.h>

#define LOG_TAG                        "at.sample.esp"
#include <at_log.h>

#include "guiconf.h"  


#define ESP32_SAMPLE_DEIVCE_NAME     "esp32"

static struct at_device_esp32 esp0 =
{
    ESP32_SAMPLE_DEIVCE_NAME,
    ESP32_SAMPLE_CLIENT_NAME,

    ESP32_SAMPLE_WIFI_SSID,
    ESP32_SAMPLE_WIFI_PASSWORD,
    ESP32_SAMPLE_RECV_BUFF_LEN,
};

struct at_device_esp32 esp32_conf_file={
    ESP32_SAMPLE_DEIVCE_NAME,
    ESP32_SAMPLE_CLIENT_NAME,
    RT_NULL,
    RT_NULL,
    ESP32_SAMPLE_RECV_BUFF_LEN,
};




int esp32_device_register(void)
{
    struct at_device_esp32 *esp32 = &esp0;
		int len =0;
		if(guiconf_global.valid ==1)
		{
			rt_kprintf("esp32 device register from conf file\n");
			len = strlen(guiconf_global.wifi_ssid);
			esp32_conf_file.wifi_ssid = (char *)rt_malloc(len+1);
			
			rt_strcpy(esp32_conf_file.wifi_ssid,guiconf_global.wifi_ssid);
			esp32_conf_file.wifi_ssid[len] = '\0';
			
			len = strlen(guiconf_global.wifi_passwd);
			esp32_conf_file.wifi_password = (char *)rt_malloc(len+1);
			rt_strcpy(esp32_conf_file.wifi_password,guiconf_global.wifi_passwd);
			esp32_conf_file.wifi_password[len] = '\0';
			
			rt_kprintf("ssid :%s\n",esp32_conf_file.wifi_ssid);
			
			esp32 = &esp32_conf_file;
			
			return at_device_register(&(esp32->device),
																esp32->device_name,
																esp32->client_name,
																AT_DEVICE_CLASS_ESP32,
																(void *) esp32);
		}
		else
		{
			rt_kprintf("esp32 device register from default config\n");
			return at_device_register(&(esp32->device),
																esp32->device_name,
																esp32->client_name,
																AT_DEVICE_CLASS_ESP32,
																(void *) esp32);	
		}

}


// esp32 重新配置 wifi
void esp32_device_reset_wifi_info()
{
	struct at_device_ssid_pwd  wifi_info;
	struct at_device_esp32 *esp32 = &esp0;
	if(guiconf_global.valid ==1)
	{
		wifi_info.ssid = guiconf_global.wifi_ssid;
		wifi_info.password = guiconf_global.wifi_passwd;
		esp32 = &esp32_conf_file;
		at_device_control(&(esp32->device),AT_DEVICE_CTRL_SET_WIFI_INFO,&wifi_info);  // 重新配置 wifi
	}
	else
	{
		LOG_E("esp32 wifi reset error, global config error \n");
	}
}


void esp32_device_wifiscanning(void *scan_res)
{
	if(scan_res == RT_NULL)
	{
		return;
	}
	struct at_device_esp32 *esp32 = &esp0;
	if(guiconf_global.valid ==1)
	{	
		esp32 = &esp32_conf_file;
	}
	
	at_device_control(&(esp32->device),AT_DEVICE_CTRL_WIFISCAN,scan_res); // 执行 wifi 扫描处理函数 使用 scan_res 返回扫描结果
}
//INIT_APP_EXPORT(esp32_device_register);
