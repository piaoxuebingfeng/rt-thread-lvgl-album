/*
 * File      : httpclient.c
 *
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author      Notes
 * 2018-07-20     flybreak     first version
 * 2018-09-05     flybreak     Upgrade API to webclient latest version
 */

#include <webclient.h>  /* 使用 HTTP 协议与服务器通信需要包含此头文件 */
#include <sys/socket.h> /* 使用BSD socket，需要包含socket.h头文件 */
#include <netdb.h>
#include <cJSON.h>
#include <finsh.h>

#define GET_HEADER_BUFSZ        1024        //头部大小
#define GET_RESP_BUFSZ          8192        //响应缓冲区大小
#define GET_URL_LEN_MAX         256         //网址最大长度


//#define GET_URI                 "http://www.weather.com.cn/data/sk/%s.html" //获取天气的 API
#define AREA_ID                 "101180101" //河南 郑州

/* 天气数据解析 */

//void weather_data_parse(rt_uint8_t *data)
//{
//    cJSON *root = RT_NULL, *object = RT_NULL, *item = RT_NULL;

//    root = cJSON_Parse((const char *)data);
//    if (!root)
//    {
//        rt_kprintf("No memory for cJSON root!\n");
//        return;
//    }
//    object = cJSON_GetObjectItem(root, "weatherinfo");

//    item = cJSON_GetObjectItem(object, "city");
//    rt_kprintf("\ncity:%s ", item->valuestring);

//    item = cJSON_GetObjectItem(object, "temp");
//    rt_kprintf("\ntemp    :%s ", item->valuestring);

//    item = cJSON_GetObjectItem(object, "WD");
//    rt_kprintf("\nWD      :%s ", item->valuestring);

//    item = cJSON_GetObjectItem(object, "WS");
//    rt_kprintf("\nWS      :%s ", item->valuestring);

//    item = cJSON_GetObjectItem(object, "SD");
//    rt_kprintf("\nSD      :%s ", item->valuestring);

////    item = cJSON_GetObjectItem(object, "date");
////    rt_kprintf("\ndate    :%s", item->valuestring);

//    item = cJSON_GetObjectItem(object, "time");
//    rt_kprintf("\ntime    :%s \n", item->valuestring);

//    if (root != RT_NULL)
//        cJSON_Delete(root);
//}


//#define GET_URI 								"http://www.weather.com.cn/data/cityinfo/%s.html"
// 解析天气数据
void weather_data_parse(rt_uint8_t *data)
{
    cJSON *root = RT_NULL, *object = RT_NULL, *item = RT_NULL;

    root = cJSON_Parse((const char *)data);
    if (!root)
    {
        rt_kprintf("No memory for cJSON root!\n");
        return;
    }
    object = cJSON_GetObjectItem(root, "weatherinfo");

    item = cJSON_GetObjectItem(object, "city");
    rt_kprintf("\n city:%s ", item->valuestring);

    item = cJSON_GetObjectItem(object, "temp1");
    rt_kprintf("\n temp1   :%s ", item->valuestring);

    item = cJSON_GetObjectItem(object, "temp2");
    rt_kprintf("\n temp2   :%s ", item->valuestring);
		
    item = cJSON_GetObjectItem(object, "weather");
    rt_kprintf("\n weather   :%s ", item->valuestring);
		
    item = cJSON_GetObjectItem(object, "ptime");
    rt_kprintf("\n ptime   :%s \n", item->valuestring);

    if (root != RT_NULL)
        cJSON_Delete(root);
}



#define GET_URI 								"http://t.weather.sojson.com/api/weather/city/%s"
// 
//http://t.weather.sojson.com/api/weather/city/101180101   json 格式数据解析
void weather_sojson_data_parse(rt_uint8_t *data)
{
    cJSON *root = RT_NULL, *object = RT_NULL, *item = RT_NULL;
		cJSON *cityInfo_obj = RT_NULL;
		cJSON *dataobj = RT_NULL;
		cJSON *JsonArray =RT_NULL;
		uint16_t jsonarray_size =0;
		uint16_t i =0;

    root = cJSON_Parse((const char *)data);
    if (!root)
    {
        rt_kprintf("No memory for cJSON root!\n");
        return;
    }
    cityInfo_obj = cJSON_GetObjectItem(root, "cityInfo");

    item = cJSON_GetObjectItem(cityInfo_obj, "city");
    rt_kprintf("\n city:%s ", item->valuestring);

		
		dataobj = cJSON_GetObjectItem(root, "data");
		
		JsonArray = cJSON_GetObjectItem(dataobj,"forecast");
		
		jsonarray_size = cJSON_GetArraySize(JsonArray);
		for(i=0;i<jsonarray_size;i++)
		{
			object = cJSON_GetArrayItem(JsonArray,i);
			
			item = cJSON_GetObjectItem(object, "ymd");
			rt_kprintf("\n date   :%s ", item->valuestring);
			
			item = cJSON_GetObjectItem(object, "type");
			rt_kprintf("\n type   :%s ", item->valuestring);
			
			item = cJSON_GetObjectItem(object, "high");
			rt_kprintf("\n high   :%s ", item->valuestring);
			
			item = cJSON_GetObjectItem(object, "low");
			rt_kprintf("\n low   :%s ", item->valuestring);
			
			item = cJSON_GetObjectItem(object, "sunrise");
			rt_kprintf("\n sunrise   :%s ", item->valuestring);
			
			item = cJSON_GetObjectItem(object, "sunset");
			rt_kprintf("\n sunset   :%s ", item->valuestring);
			
			item = cJSON_GetObjectItem(object, "notice");
			rt_kprintf("\n notice   :%s ", item->valuestring);
		}
		
    if (root != RT_NULL)
        cJSON_Delete(root);
}




void weather(int argc, char **argv)
{
    rt_uint8_t *buffer = RT_NULL;
    int resp_status;
    struct webclient_session *session = RT_NULL;
    char *weather_url = RT_NULL;
    int content_length = -1, bytes_read = 0;
    int content_pos = 0;

    /* 为 weather_url 分配空间 */
    weather_url = rt_calloc(1, GET_URL_LEN_MAX);
    if (weather_url == RT_NULL)
    {
        rt_kprintf("No memory for weather_url!\n");
        goto __exit;
    }
    /* 拼接 GET 网址 */
    rt_snprintf(weather_url, GET_URL_LEN_MAX, GET_URI, AREA_ID);

    /* 创建会话并且设置响应的大小 */
    session = webclient_session_create(GET_HEADER_BUFSZ);
    if (session == RT_NULL)
    {
        rt_kprintf("No memory for get header!\n");
        goto __exit;
    }

    /* 发送 GET 请求使用默认的头部 */
    if ((resp_status = webclient_get(session, weather_url)) != 200)
    {
        rt_kprintf("webclient GET request failed, response(%d) error.\n", resp_status);
        goto __exit;
    }

    /* 分配用于存放接收数据的缓冲 */
    buffer = rt_calloc(1, GET_RESP_BUFSZ);
    if (buffer == RT_NULL)
    {
        rt_kprintf("No memory for data receive buffer!\n");
        goto __exit;
    }

    content_length = webclient_content_length_get(session);
    if (content_length < 0)
    {
        /* 返回的数据是分块传输的. */
        do
        {
            bytes_read = webclient_read(session, buffer, GET_RESP_BUFSZ);
            if (bytes_read <= 0)
            {
                break;
            }
        }while (1);
    }
    else
    {
        do
        {
            bytes_read = webclient_read(session, buffer,
                                        content_length - content_pos > GET_RESP_BUFSZ ?
                                        GET_RESP_BUFSZ : content_length - content_pos);
            if (bytes_read <= 0)
            {
                break;
            }
            content_pos += bytes_read;
        }while (content_pos < content_length);
    }

    /* 天气数据解析 */
//    weather_data_parse(buffer);
		weather_sojson_data_parse(buffer);
__exit:
    /* 释放网址空间 */
    if (weather_url != RT_NULL)
        rt_free(weather_url);
    /* 关闭会话 */
    if (session != RT_NULL)
        webclient_close(session);
    /* 释放缓冲区空间 */
    if (buffer != RT_NULL)
        rt_free(buffer);
}

MSH_CMD_EXPORT(weather, Get weather by webclient);

