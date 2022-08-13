#ifndef _GUICONF_H__
#define _GUICONF_H__

#include "rtthread.h"
#include "dfs.h"
#include "fcntl.h"
#include "unistd.h"
#include <cJSON.h>


#define CONF_STR_MIN_LEN 50
#define CONF_STR_MAX_LEN 100


struct guiconf_s {
	char valid;
	char wifi_ssid[CONF_STR_MIN_LEN];
	char wifi_passwd[CONF_STR_MIN_LEN];
	char apikey[CONF_STR_MAX_LEN];
	char cityid[CONF_STR_MIN_LEN];
};


typedef struct guiconf_s guiconf_t;


extern  guiconf_t guiconf_global;


void guiconf_set_wifissid(guiconf_t *guiconf,const char *wifissid);
void guiconf_set_wifipasswd(guiconf_t *guiconf,const char *wifipasswd);
void guiconf_set_cityid(guiconf_t *guiconf,const char *cityid);

void guiconf_read(guiconf_t *guiconf);
void guiconf_print(guiconf_t *guiconf);
void guiconf_write(guiconf_t *guiconf);


//-------------------------------------------------------------------------
// ÃÏ∆¯≈‰÷√
#define WEATHER_URL_MIN_LEN 100
#define WEATHER_URL_MAX_LEN 200
struct weatherconf_s
{
	char weather_get_url[WEATHER_URL_MAX_LEN];
	char weather_get_key[WEATHER_URL_MIN_LEN];
};

typedef struct weatherconf_s weatherconf_t;




#endif


