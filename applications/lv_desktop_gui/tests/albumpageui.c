#include "albumpageui.h"


#define STM32F469_WORKSPACE  0
#define VSCODE_SIMULATOR     1


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
static imgs_mgt_t *imgs_current_show = RT_NULL;
static uint32_t img_show_count =1;

void imgs_list_init();
void imgs_list_deinit();
void imgs_list_show();
//---------------------------------------------------------------------------------------------------------


///////////////////// VARIABLES ////////////////////
static lv_obj_t * ui_albumpage;
static lv_obj_t * ui_Image1;
static lv_obj_t * ui_bottompanel;
static lv_obj_t * ui_btnleft;
static lv_obj_t * ui_Labbtnleft;
static lv_obj_t * ui_btnright;
static lv_obj_t * ui_Labbtnright;

static lv_obj_t * ui_btnswitch;
static lv_obj_t * ui_Labbtnswitch;


// test
#define IMGS_MAX_NUM 5
static uint16_t imgswitch_c=0;
const static char *imgsname[IMGS_MAX_NUM]={"S:imgs/bg_lvgl.jpg","S:imgs/holidaynight800.jpg","S:imgs/defaultbg_lvgl.jpg","S:imgs/seaandsky800.jpg","S:imgs/simplelight800.jpg"};

const static void *norflashimgname[]={&bg_lvgl,&ui_img_testbg_png,&ui_img_seaandsky800_png};

///////////////////// TEST LVGL SETTINGS ////////////////////
 #if LV_COLOR_DEPTH != 16
     #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
 #endif
 #if LV_COLOR_16_SWAP !=0
     #error "#error LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
 #endif

void imganmitoleft()
{
    imgswitch_c++;
    if(imgswitch_c==5)
    {
        imgswitch_c=0;
    }
    lv_img_set_src(ui_Image1, norflashimgname[imgswitch_c]);
}


void imganmitoright()
{
    if(imgswitch_c==0)
    {
        imgswitch_c =4;
    }
    else if(imgswitch_c >0)
    {
        imgswitch_c--;
    }
    lv_img_set_src(ui_Image1, norflashimgname[imgswitch_c]);
}



///////////////////// FUNCTIONS ////////////////////
static void ui_event_btnleft(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
			imganmitoleft();
    }
}
static void ui_event_btnright(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
			imganmitoright();
    }
}


static void ui_event_btnswitch(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
//        imgswitch_c++;
//        if(imgswitch_c==5 )
//        {
//            imgswitch_c =0 ;
//        }
//        lv_img_set_src(ui_Image1, imgsname[imgswitch_c]);
			lv_albumpage_auto_update();
    }
}

///////////////////// SCREENS ////////////////////
void ui_albumpage_screen_init(lv_obj_t *parent)
{

    // ui_albumpage

    ui_albumpage = lv_obj_create(parent);

    lv_obj_clear_flag(ui_albumpage, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(ui_albumpage, LV_HOR_RES, LV_VER_RES);       // 设置到屏幕大小
    lv_obj_set_style_bg_color(ui_albumpage, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_albumpage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(ui_albumpage,0,LV_STATE_DEFAULT);
    lv_obj_center(ui_albumpage);
    // ui_Image1

    ui_Image1 = lv_img_create(ui_albumpage);
		lv_obj_set_style_border_width(ui_Image1,0,LV_STATE_DEFAULT);

		lv_img_set_src(ui_Image1, &bg_lvgl);
    lv_obj_set_width(ui_Image1, 800);
    lv_obj_set_height(ui_Image1, 480);

    lv_obj_set_x(ui_Image1, 0);
    lv_obj_set_y(ui_Image1, 0);

    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);
    // ui_btnleft

    ui_btnleft = lv_btn_create(ui_albumpage);

    lv_obj_set_width(ui_btnleft, 80);
    lv_obj_set_height(ui_btnleft,80);

		lv_obj_align(ui_btnleft,LV_ALIGN_LEFT_MID,0,0);
    lv_obj_add_flag(ui_btnleft, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_btnleft, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_btnleft, ui_event_btnleft, LV_EVENT_ALL, NULL);
    lv_obj_set_style_radius(ui_btnleft, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_btnleft, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_btnleft, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_btnleft, 40, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui_btnleft, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_btnleft, 50, LV_PART_MAIN | LV_STATE_PRESSED);
		

    // ui_Labbtnleft

    ui_Labbtnleft = lv_label_create(ui_btnleft);

    lv_obj_set_width(ui_Labbtnleft, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Labbtnleft, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Labbtnleft, 0);
    lv_obj_set_y(ui_Labbtnleft, 0);

    lv_obj_set_align(ui_Labbtnleft, LV_ALIGN_CENTER);

    // lv_label_set_text(ui_Labbtnleft, "LEFT");
    lv_label_set_text(ui_Labbtnleft, LV_SYMBOL_LEFT);
    // ui_btnswitch

    ui_btnswitch = lv_btn_create(ui_albumpage);

    lv_obj_set_width(ui_btnswitch, 80);
    lv_obj_set_height(ui_btnswitch,80);

//    lv_obj_set_x(ui_btnswitch, 0);
//    lv_obj_set_y(ui_btnswitch, 0);

//    lv_obj_set_align(ui_btnswitch, LV_ALIGN_CENTER);
		lv_obj_align(ui_btnswitch,LV_ALIGN_BOTTOM_MID,0,0);
		
    lv_obj_add_flag(ui_btnswitch, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_btnswitch, LV_OBJ_FLAG_SCROLLABLE);

    //lv_obj_add_event_cb(ui_btnswitch, ui_event_btnleft, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_btnswitch, ui_event_btnswitch, LV_EVENT_ALL, NULL);
    lv_obj_set_style_radius(ui_btnswitch, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_btnswitch, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_btnswitch, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_btnswitch, 40, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui_btnswitch, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_btnswitch, 50, LV_PART_MAIN | LV_STATE_PRESSED);

    // ui_Labbtnswitch

    ui_Labbtnswitch = lv_label_create(ui_btnswitch);

    lv_obj_set_width(ui_Labbtnswitch, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Labbtnswitch, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Labbtnswitch, 0);
    lv_obj_set_y(ui_Labbtnswitch, 0);

    lv_obj_set_align(ui_Labbtnswitch, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Labbtnswitch, "SWITCH");
    // ui_btnright

    ui_btnright = lv_btn_create(ui_albumpage);

    lv_obj_set_width(ui_btnright, 80);
    lv_obj_set_height(ui_btnright,80);
		lv_obj_align(ui_btnright,LV_ALIGN_RIGHT_MID,0,0);
    lv_obj_add_flag(ui_btnright, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_btnright, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_btnright, ui_event_btnright, LV_EVENT_ALL, NULL);
    lv_obj_set_style_radius(ui_btnright, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_btnright, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_btnright, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_btnright, 40, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui_btnright, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_btnright, 50, LV_PART_MAIN | LV_STATE_PRESSED);

    // ui_Labbtnright

    ui_Labbtnright = lv_label_create(ui_btnright);

    lv_obj_set_width(ui_Labbtnright, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Labbtnright, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Labbtnright, 0);
    lv_obj_set_y(ui_Labbtnright, 0);

    lv_obj_set_align(ui_Labbtnright, LV_ALIGN_CENTER);

    // lv_label_set_text(ui_Labbtnright, "RIGHT");
    lv_label_set_text(ui_Labbtnright, LV_SYMBOL_RIGHT);

}

void lv_albumpage_auto_update()
{
	if(imgs_current_show != RT_NULL)
	{
		if(imgs_current_show->imgs_lvgl_path)
		{
			rt_kprintf("[%d/%d]   %s  \n",imgs_current_show->imgs_count,imgs_current_show->imgs_total_nums,imgs_current_show->imgs_lvgl_path);
			lv_img_set_src(ui_Image1, imgs_current_show->imgs_lvgl_path);
			imgs_current_show = imgs_current_show->next;
			if(imgs_current_show == RT_NULL)
			{
				imgs_current_show = imgs_list_head;
			}
		}
	}
	
}














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


void imgs_set_current_img_node_head()
{
	if(imgs_list_head)
	{
		imgs_current_show = imgs_list_head;
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



