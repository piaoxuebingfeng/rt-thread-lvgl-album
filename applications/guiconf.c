#include "guiconf.h"

#define DBG_ENABLE
#define DBG_SECTION_NAME               "guiconf"
#define DBG_LEVEL                      DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>

// ��д�����ļ�����


#define GUICONFIG_FILENAME "/conf/gui.conf"


// gui ȫ������
guiconf_t guiconf_global;




void guiconf_read(guiconf_t *guiconf)
{
	int fd=0;
	int ret=0;
	int total_length =0 ;
	int read_len =0 ;
	struct stat file_stat;
	char *read_buf;
	
	static cJSON *root = RT_NULL, *object = RT_NULL, *item = RT_NULL;
	
	if(guiconf == RT_NULL)
	{
		return ;
	}
	
	ret = stat(GUICONFIG_FILENAME, &file_stat);
	if(ret == 0)
	{
		total_length = file_stat.st_size;
		rt_kprintf("%s file size = %d\n", GUICONFIG_FILENAME,file_stat.st_size);
	}
	else
		rt_kprintf("%s file not fonud\n",GUICONFIG_FILENAME);
	
	
	fd = open(GUICONFIG_FILENAME, O_RDONLY , 0);
	if (fd < 0)
	{
			LOG_E("get file failed, open file(%s) error.", GUICONFIG_FILENAME);
			return ;
	}

	read_buf = (char *)rt_malloc(total_length*sizeof(char));
	if (read_buf == RT_NULL)
	{
			LOG_E("news_mem_buffer malloc failed \n");
			goto __exit;
	}
	read_len = read(fd,read_buf,total_length);
	LOG_I("read data len from file %s :%d\n",GUICONFIG_FILENAME,read_len);
	
	
	root = cJSON_Parse((const char *)read_buf);
	if (!root)
	{
			rt_kprintf("No memory for cJSON root!\n");
			goto __exit;
	}
	
	// get ssid
	item = cJSON_GetObjectItem(root,"ssid");
	rt_memset(guiconf->wifi_ssid,0,CONF_STR_MIN_LEN);
	rt_strcpy(guiconf->wifi_ssid,item->valuestring);
	LOG_I("read guiconf ssid:%s\n",item->valuestring);
	
	// get passwd
	item = cJSON_GetObjectItem(root,"passwd");
	rt_memset(guiconf->wifi_passwd,0,CONF_STR_MIN_LEN);
	rt_strcpy(guiconf->wifi_passwd,item->valuestring);
	LOG_I("read guiconf passwd:%s\n",item->valuestring);
	
	// get apikey
	item = cJSON_GetObjectItem(root,"apikey");
	rt_memset(guiconf->apikey,0,CONF_STR_MAX_LEN);
	rt_strcpy(guiconf->apikey,item->valuestring);
	LOG_I("read guiconf apikey:%s\n",item->valuestring);

	guiconf->valid =1;
	
	
__exit:
	if(fd)
	{
		close(fd);
	}
	if(root)
	{
		cJSON_Delete(root);
		root= RT_NULL;
	}
	if(read_buf)
	{
		rt_free(read_buf);
	}
}


void guiconf_print(guiconf_t *guiconf)
{
	if(guiconf == RT_NULL)
	{
		return ;
	}
	if(guiconf->valid ==1)
	{
		LOG_I("ssid :%s",guiconf->wifi_ssid);
		LOG_I("wifi_passwd :%s",guiconf->wifi_passwd);
		LOG_I("apikey :%s",guiconf->apikey);
	}
	else
	{
		LOG_E("guiconf is not valid \n");
	}

	
	return;
}


void guiconf_set_wifissid(guiconf_t *guiconf,const char *wifissid)
{
		if(guiconf ==RT_NULL && wifissid == RT_NULL)
		{
			return ;
		}
		rt_memset(guiconf->wifi_ssid,0,CONF_STR_MIN_LEN);
		rt_strcpy(guiconf->wifi_ssid,wifissid);
}

void guiconf_set_wifipasswd(guiconf_t *guiconf,const char *wifipasswd)
{
		if(guiconf ==RT_NULL && wifipasswd == RT_NULL)
		{
			return ;
		}
		rt_memset(guiconf->wifi_passwd,0,CONF_STR_MIN_LEN);
		rt_strcpy(guiconf->wifi_passwd,wifipasswd);
}

void guiconf_write(guiconf_t *guiconf)
{
	static cJSON *root = RT_NULL;
    char *cjsonstr=RT_NULL;
	int fd=0;
	int ret=0;

	// get json config str
	//LOG_I("ssid :%s",guiconf->wifi_ssid);
	//LOG_I("wifi_passwd :%s",guiconf->wifi_passwd);
	//LOG_I("apikey :%s",guiconf->apikey);
 

    root = cJSON_CreateObject();

	cJSON_AddStringToObject(root,"ssid",guiconf->wifi_ssid);

	cJSON_AddStringToObject(root,"passwd",guiconf->wifi_passwd);
	
	cJSON_AddStringToObject(root,"apikey",guiconf->apikey);

    cjsonstr =  cJSON_Print(root);
    
    LOG_I("cjson str : %s \n",cjsonstr);


    fd = open(GUICONFIG_FILENAME, O_WRONLY , 0);
	if (fd < 0)
	{
			LOG_E("open file failed, open file(%s) error.", GUICONFIG_FILENAME);
			goto __exit;
	}


    // write json config str to file
    write(fd,cjsonstr,rt_strlen(cjsonstr));


__exit:
    if(fd>0)
    {
		close(fd);
    }
	if(root != RT_NULL)
	{
		cJSON_Delete(root);
		root= RT_NULL;
	}  	
	return ;
}