#include "guiconf.h"

#define DBG_ENABLE
#define DBG_SECTION_NAME               "guiconf"
#define DBG_LEVEL                      DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>

// 读写配置文件操作


#define GUICONFIG_FILENAME "/conf/gui.conf"
#define GUICONFIG_FILENAMEBAK "/conf/gui.conf.bak"

// gui 全局配置
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

	// get cityname
	item = cJSON_GetObjectItem(root,"cityname");
	if(item)
	{
		rt_memset(guiconf->cityname,0,CONF_STR_MAX_LEN);
		rt_strcpy(guiconf->cityname,item->valuestring);
		LOG_I("read guiconf cityname:%s\n",item->valuestring);
	}
	else
	{
		LOG_E("not found cityname conf\n");
	}

	
	// get cityid
	item = cJSON_GetObjectItem(root,"cityid");
	if(item)
	{
		rt_memset(guiconf->cityid,0,CONF_STR_MIN_LEN);
		rt_strcpy(guiconf->cityid,item->valuestring);
		LOG_I("read guiconf cityid:%s\n",item->valuestring);
	}
	else
	{
		LOG_E("not found cityid conf\n");
	}

	
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
		LOG_I("ssid        :%s",guiconf->wifi_ssid);
		LOG_I("wifi_passwd :%s",guiconf->wifi_passwd);
		LOG_I("apikey      :%s",guiconf->apikey);
		LOG_I("cityname    :%s",guiconf->cityname);
		LOG_I("cityid      :%s",guiconf->cityid);
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

void guiconf_set_cityname(guiconf_t *guiconf,const char *cityname)
{
		if(guiconf ==RT_NULL && cityname == RT_NULL)
		{
			return ;
		}
		rt_memset(guiconf->cityname,0,CONF_STR_MAX_LEN);
		rt_strcpy(guiconf->cityname,cityname);
}


void guiconf_set_cityid(guiconf_t *guiconf,const char *cityid)
{
		if(guiconf ==RT_NULL && cityid == RT_NULL)
		{
			return ;
		}
		rt_memset(guiconf->cityid,0,CONF_STR_MIN_LEN);
		rt_strcpy(guiconf->cityid,cityid);
}





void guiconf_write(guiconf_t *guiconf)
{
	static cJSON *root = RT_NULL;
	char *cjsonstr=RT_NULL;
	struct stat file_stat;
	int fd=0;
	int ret=0;

	// get json config str
	//LOG_I("ssid :%s",guiconf->wifi_ssid);
	//LOG_I("wifi_passwd :%s",guiconf->wifi_passwd);
	//LOG_I("apikey :%s",guiconf->apikey);
 
	
	ret = stat(GUICONFIG_FILENAMEBAK, &file_stat);
	if(ret == 0)
	{
		rt_kprintf("%s file size = %d\n", GUICONFIG_FILENAMEBAK,file_stat.st_size);
		ret = unlink(GUICONFIG_FILENAMEBAK);
		if(ret ==0)
		{
			rt_kprintf("%s file delete success\n", GUICONFIG_FILENAMEBAK);
		}
		else
		{
			rt_kprintf("%s file delete failed. return \n", GUICONFIG_FILENAMEBAK);
			return ;
		}
	}
	else
	{
		rt_kprintf("%s file not fonud\n",GUICONFIG_FILENAMEBAK);
		
	}
	
	ret =rename(GUICONFIG_FILENAME, GUICONFIG_FILENAMEBAK);
	if(ret<0)
	{
		LOG_E("rename file %s to %s error. return ", GUICONFIG_FILENAME,GUICONFIG_FILENAMEBAK);
		return ;
	}
	
	
	root = cJSON_CreateObject();

	cJSON_AddStringToObject(root,"ssid",guiconf->wifi_ssid);

	cJSON_AddStringToObject(root,"passwd",guiconf->wifi_passwd);
	
	cJSON_AddStringToObject(root,"apikey",guiconf->apikey);
	
	cJSON_AddStringToObject(root,"cityname",guiconf->cityname);
	
	cJSON_AddStringToObject(root,"cityid",guiconf->cityid);
	cjsonstr =  cJSON_Print(root);
    
    LOG_I("cjson str : %s \n",cjsonstr);


		// O_CREAT 如果要打开的文件不存在，则建立该文件
		// O_TRUNC 如果文件已经存在，则清空文件中的内容
    fd = open(GUICONFIG_FILENAME, O_WRONLY|O_CREAT|O_TRUNC , 0);
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
