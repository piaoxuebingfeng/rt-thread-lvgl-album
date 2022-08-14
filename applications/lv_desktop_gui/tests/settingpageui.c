#include "settingpageui.h"
#include "lv_backbtn_test.h"
#include "guiconf.h"

extern void esp32_device_reset_wifi_info();
extern void esp32_device_wifiscanning(void *scan_res);

LV_FONT_DECLARE(HarmonyOS_Sans_SC_Medium);


///////////////////// VARIABLES ////////////////////
static lv_obj_t * ui_ScreenPage;
static lv_obj_t * ui_panel;
static lv_obj_t * ui_leftpanel;
static lv_obj_t * ui_Roller2;
static lv_obj_t * ui_topstatuspanel;
static lv_obj_t * ui_versionlabel;
static lv_obj_t * ui_rightpanelwifi;
static lv_obj_t * ui_wifisetbtn;
static lv_obj_t * ui_wifisetbtnlabel;
static lv_obj_t * ui_labelwifissid;
static lv_obj_t * ui_labwifipasswd;
static lv_obj_t * ui_textwifissid;
static lv_obj_t * ui_textwifipassword;
static lv_obj_t * ui_Keyboard2;


// 添加页面
static lv_obj_t * ui_rightpanelwifiscan;
static lv_obj_t * ui_wifiscan_btn;
static lv_obj_t * ui_lab_wifiscan_btn;
static lv_obj_t * ui_wifiscanres_roller;



static lv_obj_t * ui_rightpanelfontpage;
static lv_obj_t * ui_rightpanelupdatepage;


static lv_obj_t * ui_rightpanelsystempage;
static lv_obj_t * system_version_label;


///////////////////// TEST LVGL SETTINGS ////////////////////
// #if LV_COLOR_DEPTH != 16
//     #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
// #endif
// #if LV_COLOR_16_SWAP !=0
//     #error "#error LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
// #endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////





static void desktop_bg_img_dd_event_handler(lv_event_t * e)
{
		int select_id;
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Option: %s", buf);
				select_id= lv_dropdown_get_selected(obj);
				lv_desktop_set_bg_img(select_id);
    }
}


//static void desktop_bg_img_roller_event_handler(lv_event_t * e)
//{
//    lv_event_code_t code = lv_event_get_code(e);
//    lv_obj_t * obj = lv_event_get_target(e);
//    if(code == LV_EVENT_VALUE_CHANGED) {
//        char buf[32];
//        lv_roller_get_selected_str(obj, buf, sizeof(buf));
//        LV_LOG_USER("Selected value: %s", buf);
//    }
//}


// roller 选择页面事件

static void ui_Roller2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
        // LV_LOG_USER("Selected :%d   %s\n",lv_roller_get_selected(obj), buf);

        switch (lv_roller_get_selected(obj))
        {
        case 0:   // wifi setting panel
            lv_obj_clear_flag(ui_rightpanelwifi,LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(ui_rightpanelfontpage,LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(ui_rightpanelupdatepage,LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(ui_rightpanelsystempage,LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_rightpanelwifiscan,LV_OBJ_FLAG_HIDDEN);
						
            break;
        case 1:   // font panel
            lv_obj_add_flag(ui_rightpanelwifi,LV_OBJ_FLAG_HIDDEN);
						lv_obj_clear_flag(ui_rightpanelfontpage,LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(ui_rightpanelupdatepage,LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(ui_rightpanelsystempage,LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_rightpanelwifiscan,LV_OBJ_FLAG_HIDDEN);
						
            break;
        case 2:   // wifi scaning panel
            lv_obj_clear_flag(ui_rightpanelwifiscan,LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(ui_rightpanelfontpage,LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(ui_rightpanelupdatepage,LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(ui_rightpanelsystempage,LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_rightpanelwifi,LV_OBJ_FLAG_HIDDEN);
            break;
        case 3:  // update panel
						lv_obj_add_flag(ui_rightpanelwifiscan,LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(ui_rightpanelfontpage,LV_OBJ_FLAG_HIDDEN);
						lv_obj_clear_flag(ui_rightpanelupdatepage,LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(ui_rightpanelsystempage,LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_rightpanelwifi,LV_OBJ_FLAG_HIDDEN);
            break;
        case 4: // system panel
            lv_obj_add_flag(ui_rightpanelwifiscan,LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(ui_rightpanelfontpage,LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(ui_rightpanelupdatepage,LV_OBJ_FLAG_HIDDEN);
						lv_obj_clear_flag(ui_rightpanelsystempage,LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_rightpanelwifi,LV_OBJ_FLAG_HIDDEN);
						break;
        default:
            break;
        }
    }
}


// text area 事件

static void textarea_event(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_FOCUSED) {
        if(ui_Keyboard2)
        {
            lv_keyboard_set_textarea(ui_Keyboard2, obj);
        }
    }
}


// wifi 配置按键事件

static void wifisetbtn_event(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED)
    {
				// 获取配置好的SSID 和密码 写入配置文件中
        if(ui_textwifissid && ui_textwifipassword)
        {
           LV_LOG_USER("SSID: %s\n",lv_textarea_get_text(ui_textwifissid));
					
					guiconf_set_wifissid(&guiconf_global,lv_textarea_get_text(ui_textwifissid));

					LV_LOG_USER("password: %s\n",lv_textarea_get_text(ui_textwifipassword));
					guiconf_set_wifipasswd(&guiconf_global,lv_textarea_get_text(ui_textwifipassword));
					
					guiconf_write(&guiconf_global);
					
					
					esp32_device_reset_wifi_info();
        }



    }
}



static void msgbox_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_current_target(e);
    LV_LOG_USER("Button %s clicked", lv_msgbox_get_active_btn_text(obj));
		lv_msgbox_close(obj);
}	


static void update_check_btn_event(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t * obj = lv_event_get_target(e);
	static const char * btns[] ={"OK", ""};

	
	if(code == LV_EVENT_CLICKED)
	{
    lv_obj_t * mbox1 = lv_msgbox_create(NULL, "", "待开发.", btns, false);
		lv_obj_set_style_text_font(mbox1, &HarmonyOS_Sans_SC_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(mbox1, msgbox_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_center(mbox1);
	}
}

static void software_update_btn_event(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t * obj = lv_event_get_target(e);
	static const char * btns[] ={"OK", ""};

	
	if(code == LV_EVENT_CLICKED)
	{
    lv_obj_t * mbox1 = lv_msgbox_create(NULL, "", "待开发.", btns, false);
		lv_obj_set_style_text_font(mbox1, &HarmonyOS_Sans_SC_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(mbox1, msgbox_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_center(mbox1);
	}
}



static void wifiscan_btn_event(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t * obj = lv_event_get_target(e);
	char *res = RT_NULL;
	
	res = rt_malloc(5120*sizeof(char));
	
	if(res == RT_NULL)
	{
		rt_kprintf("res malloc error\n");
		return;
	}
	
	
	if(code == LV_EVENT_CLICKED)
	{
		rt_kprintf("wifi scan begin ...\n");
		esp32_device_wifiscanning(res);
	}
	
	if(res !=RT_NULL)
	{
		rt_free(res);
	}
	return ;
}



///////////////////// SCREENS ////////////////////
void ui_settingpage_screen_init(lv_obj_t *parent)
{
		ui_ScreenPage = lv_obj_create(parent);
    lv_obj_clear_flag(ui_ScreenPage, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(ui_ScreenPage, LV_HOR_RES, LV_VER_RES);       // 设置到屏幕大小
    lv_obj_set_style_bg_color(ui_ScreenPage, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenPage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_radius(ui_ScreenPage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(ui_ScreenPage,0,LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_align(ui_ScreenPage,LV_ALIGN_CENTER,0,0);
	
    // ui_panel

    ui_panel = lv_obj_create(ui_ScreenPage);

    lv_obj_clear_flag(ui_panel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(ui_panel, LV_HOR_RES, LV_VER_RES-40);       // 设置到屏幕大小
    lv_obj_set_style_bg_color(ui_panel, lv_color_hex(0xECEBEB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_panel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_align(ui_panel,LV_ALIGN_CENTER,0,20);

    // ui_leftpanel

    ui_leftpanel = lv_obj_create(ui_panel);

    lv_obj_set_width(ui_leftpanel, 250);
    lv_obj_set_height(ui_leftpanel, 430);

//    lv_obj_set_x(ui_leftpanel, -255);
//    lv_obj_set_y(ui_leftpanel, 20);
		lv_obj_align(ui_leftpanel,LV_ALIGN_LEFT_MID,-10,0);
	
//    lv_obj_set_align(ui_leftpanel, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_leftpanel, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_radius(ui_leftpanel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_leftpanel, lv_color_hex(0x0D1423), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_leftpanel, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_leftpanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Roller2

    ui_Roller2 = lv_roller_create(ui_leftpanel);
		lv_obj_set_style_border_width(ui_Roller2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_color(ui_Roller2,lv_color_make(255,255,255),LV_STATE_DEFAULT);
    lv_roller_set_options(ui_Roller2, "WIFI\nFONT\nSCANNING\nUPDATE\nSYSTEM\n", LV_ROLLER_MODE_NORMAL);

    lv_obj_set_width(ui_Roller2, 275);
    lv_obj_set_height(ui_Roller2, 425);

//    lv_obj_set_x(ui_Roller2, 0);
//    lv_obj_set_y(ui_Roller2, 0);

    lv_obj_set_align(ui_Roller2, LV_ALIGN_CENTER);

    lv_obj_set_style_bg_color(ui_Roller2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Roller2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // add by pxbf
    lv_obj_add_event_cb(ui_Roller2, ui_Roller2_event_handler, LV_EVENT_ALL, NULL);

    // ui_rightpanelwifi

    ui_rightpanelwifi = lv_obj_create(ui_panel);

    lv_obj_set_width(ui_rightpanelwifi, 500);
    lv_obj_set_height(ui_rightpanelwifi, 430);

//    lv_obj_set_x(ui_rightpanelwifi, 145);
//    lv_obj_set_y(ui_rightpanelwifi, 20);
		lv_obj_align(ui_rightpanelwifi,LV_ALIGN_RIGHT_MID,10,0);

//    lv_obj_set_align(ui_rightpanelwifi, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_rightpanelwifi,
                      LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_bg_color(ui_rightpanelwifi, lv_color_hex(0xD6BBA6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rightpanelwifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_rightpanelwifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_wifisetbtn

    ui_wifisetbtn = lv_btn_create(ui_rightpanelwifi);

    lv_obj_set_width(ui_wifisetbtn, 100);
    lv_obj_set_height(ui_wifisetbtn, 50);

    lv_obj_set_x(ui_wifisetbtn, 0);
    lv_obj_set_y(ui_wifisetbtn, -50);

    lv_obj_set_align(ui_wifisetbtn, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_wifisetbtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_wifisetbtn, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_radius(ui_wifisetbtn, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_wifisetbtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_wifisetbtn, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_wifisetbtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_wifisetbtn, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_wifisetbtn,wifisetbtn_event,LV_EVENT_CLICKED,NULL);
    // ui_wifisetbtnlabel

    ui_wifisetbtnlabel = lv_label_create(ui_wifisetbtn);

    lv_obj_set_width(ui_wifisetbtnlabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_wifisetbtnlabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_wifisetbtnlabel, 0);
    lv_obj_set_y(ui_wifisetbtnlabel, 0);

    lv_obj_set_align(ui_wifisetbtnlabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_wifisetbtnlabel, "Setting");

    lv_obj_set_style_text_color(ui_wifisetbtnlabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_wifisetbtnlabel, 250, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_labelwifissid

    ui_labelwifissid = lv_label_create(ui_rightpanelwifi);

    lv_obj_set_width(ui_labelwifissid, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_labelwifissid, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_labelwifissid, -178);
    lv_obj_set_y(ui_labelwifissid, -150);

    lv_obj_set_align(ui_labelwifissid, LV_ALIGN_CENTER);

    lv_label_set_text(ui_labelwifissid, "SSID:");

    lv_obj_set_style_text_color(ui_labelwifissid, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_labelwifissid, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_labelwifissid, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_labwifipasswd

    ui_labwifipasswd = lv_label_create(ui_rightpanelwifi);

    lv_obj_set_width(ui_labwifipasswd, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_labwifipasswd, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_labwifipasswd, -188);
    lv_obj_set_y(ui_labwifipasswd, -112);

    lv_obj_set_align(ui_labwifipasswd, LV_ALIGN_CENTER);

    lv_label_set_text(ui_labwifipasswd, "PSWD:");

    lv_obj_set_style_text_color(ui_labwifipasswd, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_labwifipasswd, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_labwifipasswd, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_textwifissid

    ui_textwifissid = lv_textarea_create(ui_rightpanelwifi);

    lv_obj_set_width(ui_textwifissid, 300);
    lv_obj_set_height(ui_textwifissid, 40);

    lv_obj_set_x(ui_textwifissid, 13);
    lv_obj_set_y(ui_textwifissid, -151);

    lv_obj_set_align(ui_textwifissid, LV_ALIGN_CENTER);

    // lv_obj_add_state(ui_textwifissid, LV_STATE_FOCUSED); 

    // if("" == "") lv_textarea_set_accepted_chars(ui_textwifissid, NULL);
    // else lv_textarea_set_accepted_chars(ui_textwifissid, "");

    lv_textarea_set_text(ui_textwifissid, "");
    lv_textarea_set_placeholder_text(ui_textwifissid, "Your wifi ssid");

    lv_obj_add_state(ui_textwifissid, LV_STATE_CHECKED | LV_STATE_FOCUSED);

    lv_obj_clear_flag(ui_textwifissid, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_text_color(ui_textwifissid, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_textwifissid, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_textwifissid, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_textwifissid, lv_color_hex(0xEEEEEE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_textwifissid, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_textwifissid, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_textwifissid, lv_color_hex(0xFF0000), LV_STATE_FOCUSED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_textwifissid, 255, LV_STATE_FOCUSED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_textwifissid, LV_TEXT_ALIGN_AUTO, LV_STATE_FOCUSED | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_textwifissid,textarea_event, LV_EVENT_FOCUSED, NULL);
		lv_textarea_set_text(ui_textwifissid,guiconf_global.wifi_ssid);
    // ui_textwifipassword

    ui_textwifipassword = lv_textarea_create(ui_rightpanelwifi);

    lv_obj_set_width(ui_textwifipassword, 300);
    lv_obj_set_height(ui_textwifipassword, 40);

    lv_obj_set_x(ui_textwifipassword, 13);
    lv_obj_set_y(ui_textwifipassword, -106);

    lv_obj_set_align(ui_textwifipassword, LV_ALIGN_CENTER);

    // if("" == "") lv_textarea_set_accepted_chars(ui_textwifipassword, NULL);
    // else lv_textarea_set_accepted_chars(ui_textwifipassword, "");

    lv_textarea_set_text(ui_textwifipassword, "");
    lv_textarea_set_placeholder_text(ui_textwifipassword, "Your wifi password");
    //密码 可见时间可以通过 lv_conf.h 中的 LV_TEXTAREA_DEF_PWD_SHOW_TIME  进行调整
    lv_textarea_set_password_mode(ui_textwifipassword, true);  // 密码模式
    lv_obj_clear_flag(ui_textwifipassword,
                      LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);
                      
    lv_obj_set_style_text_color(ui_textwifipassword, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_textwifipassword, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_textwifipassword, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_textwifipassword, lv_color_hex(0xEEEEEE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_textwifipassword, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_textwifipassword, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(ui_textwifipassword, lv_color_hex(0xFF0000), LV_STATE_FOCUSED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_textwifipassword, 255, LV_STATE_FOCUSED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_textwifipassword, LV_TEXT_ALIGN_AUTO, LV_STATE_FOCUSED | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_textwifipassword,textarea_event, LV_EVENT_FOCUSED, NULL);
		lv_textarea_set_text(ui_textwifipassword,guiconf_global.wifi_passwd);
    // ui_Keyboard2

    ui_Keyboard2 = lv_keyboard_create(ui_rightpanelwifi);

    lv_obj_set_width(ui_Keyboard2, 480);
    lv_obj_set_height(ui_Keyboard2, 200);

    lv_obj_set_x(ui_Keyboard2, 0);
    lv_obj_set_y(ui_Keyboard2, 100);

    lv_obj_set_align(ui_Keyboard2, LV_ALIGN_CENTER);

    // POST CALLS
    lv_keyboard_set_textarea(ui_Keyboard2, ui_textwifissid);



    // ui

    ui_rightpanelwifiscan = lv_obj_create(ui_panel);

    lv_obj_set_width(ui_rightpanelwifiscan, 500);
    lv_obj_set_height(ui_rightpanelwifiscan, 430);

//    lv_obj_set_x(ui_rightpanelwifiscan, 145);
//    lv_obj_set_y(ui_rightpanelwifiscan, 20);

//    lv_obj_set_align(ui_rightpanelwifiscan, LV_ALIGN_CENTER);
		lv_obj_align(ui_rightpanelwifiscan,LV_ALIGN_RIGHT_MID,0,0);
    lv_obj_clear_flag(ui_rightpanelwifiscan,
                      LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_bg_color(ui_rightpanelwifiscan, lv_color_hex(0xD6BBA6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rightpanelwifiscan, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_rightpanelwifiscan, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_flag(ui_rightpanelwifiscan,LV_OBJ_FLAG_HIDDEN);


    ui_wifiscan_btn = lv_btn_create(ui_rightpanelwifiscan);
    lv_obj_set_height(ui_wifiscan_btn,60);
    lv_obj_align(ui_wifiscan_btn,LV_ALIGN_BOTTOM_MID,0,0);
		lv_obj_add_event_cb(ui_wifiscan_btn,wifiscan_btn_event,LV_EVENT_CLICKED,NULL);

    ui_lab_wifiscan_btn = lv_label_create(ui_wifiscan_btn);
    lv_obj_center(ui_lab_wifiscan_btn);
    lv_label_set_text(ui_lab_wifiscan_btn, "Scanning");


    // wifi scan result roller
    // 
    ui_wifiscanres_roller = lv_roller_create(ui_rightpanelwifiscan);
    lv_roller_set_options(ui_wifiscanres_roller, "SSID1\nSSID2\nSSID3\nSSID4\n", LV_ROLLER_MODE_NORMAL);

    lv_obj_set_width(ui_wifiscanres_roller, 500);
    lv_obj_set_height(ui_wifiscanres_roller, 370);

    // lv_obj_set_x(ui_wifiscanres_roller, 0);
    // lv_obj_set_y(ui_wifiscanres_roller, 0);

    lv_obj_align(ui_wifiscanres_roller, LV_ALIGN_TOP_MID,0,-20);

    lv_obj_set_style_bg_color(ui_wifiscanres_roller, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_wifiscanres_roller, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_wifiscanres_roller,0,LV_STATE_DEFAULT);
		
		
		ui_rightpanelfontpage = lv_obj_create(ui_panel);

    lv_obj_set_width(ui_rightpanelfontpage, 500);
    lv_obj_set_height(ui_rightpanelfontpage, 430);

		lv_obj_align(ui_rightpanelfontpage,LV_ALIGN_RIGHT_MID,0,0);
    lv_obj_clear_flag(ui_rightpanelfontpage,
                      LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_bg_color(ui_rightpanelfontpage, lv_color_hex(0xD6BBA6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rightpanelfontpage, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_rightpanelfontpage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_flag(ui_rightpanelfontpage,LV_OBJ_FLAG_HIDDEN);
		
		// ui_rightpanelupdatepage
		
		
    ui_rightpanelupdatepage = lv_obj_create(ui_panel);

    lv_obj_set_width(ui_rightpanelupdatepage, 500);
    lv_obj_set_height(ui_rightpanelupdatepage, 430);

		lv_obj_align(ui_rightpanelupdatepage,LV_ALIGN_RIGHT_MID,0,0);
    lv_obj_clear_flag(ui_rightpanelupdatepage,
                      LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_bg_color(ui_rightpanelupdatepage, lv_color_hex(0xD6BBA6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rightpanelupdatepage, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_rightpanelupdatepage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_flag(ui_rightpanelupdatepage,LV_OBJ_FLAG_HIDDEN);

		// 固件版本信息
		lv_obj_t * current_software_ver_label = lv_label_create(ui_rightpanelupdatepage);
		lv_obj_set_width(current_software_ver_label, 300);
    lv_obj_set_height(current_software_ver_label,30);
		lv_obj_align(current_software_ver_label,LV_ALIGN_TOP_LEFT,0,0);
		lv_obj_set_style_text_font(current_software_ver_label, &HarmonyOS_Sans_SC_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_label_set_text(current_software_ver_label,"当前版本: V1.0");
		
		lv_obj_t * new_software_ver_label = lv_label_create(ui_rightpanelupdatepage);
		lv_obj_set_width(new_software_ver_label, 300);
    lv_obj_set_height(new_software_ver_label,30);
		lv_obj_align_to(new_software_ver_label,current_software_ver_label,LV_ALIGN_OUT_BOTTOM_MID,0,10);
		lv_obj_set_style_text_font(new_software_ver_label, &HarmonyOS_Sans_SC_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_label_set_text(new_software_ver_label,"新版本:  TODO");
		
		// 检查固件按钮
		lv_obj_t * update_check_btn = lv_btn_create(ui_rightpanelupdatepage);
    lv_obj_set_height(update_check_btn,60);
    lv_obj_align(update_check_btn,LV_ALIGN_BOTTOM_LEFT,50,0);
		lv_obj_add_event_cb(update_check_btn,update_check_btn_event,LV_EVENT_CLICKED,NULL);

    lv_obj_t *  update_check_btn_label = lv_label_create(update_check_btn);
    lv_obj_center(update_check_btn_label);
		lv_obj_set_style_text_font(update_check_btn_label, &HarmonyOS_Sans_SC_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(update_check_btn_label, "检查固件");
		
		lv_obj_t * software_update_btn = lv_btn_create(ui_rightpanelupdatepage);
    lv_obj_set_height(software_update_btn,60);
    lv_obj_align(software_update_btn,LV_ALIGN_BOTTOM_RIGHT,-50,0);
		lv_obj_add_event_cb(software_update_btn,software_update_btn_event,LV_EVENT_CLICKED,NULL);

    lv_obj_t *  software_update_btn_label = lv_label_create(software_update_btn);
    lv_obj_center(software_update_btn_label);
		lv_obj_set_style_text_font(software_update_btn_label, &HarmonyOS_Sans_SC_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(software_update_btn_label, "更新固件");
		
		
		// ui_rightpanelsystempage
		
    ui_rightpanelsystempage = lv_obj_create(ui_panel);

    lv_obj_set_width(ui_rightpanelsystempage, 500);
    lv_obj_set_height(ui_rightpanelsystempage, 430);

		lv_obj_align(ui_rightpanelsystempage,LV_ALIGN_RIGHT_MID,0,0);
    lv_obj_clear_flag(ui_rightpanelsystempage,
                      LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_bg_color(ui_rightpanelsystempage, lv_color_hex(0xD6BBA6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rightpanelsystempage, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_rightpanelsystempage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_flag(ui_rightpanelsystempage,LV_OBJ_FLAG_HIDDEN);
		
		
		system_version_label = lv_label_create(ui_rightpanelsystempage);
		lv_obj_set_width(system_version_label, 300);
    lv_obj_set_height(system_version_label, 30);
		lv_obj_align(system_version_label,LV_ALIGN_TOP_LEFT,10,10);
		lv_label_set_text(system_version_label,"VERSION: 1.0");

		lv_obj_t * cpu_label = lv_label_create(ui_rightpanelsystempage);
		lv_obj_set_width(cpu_label, 300);
    lv_obj_set_height(cpu_label, 30);
		lv_obj_align_to(cpu_label,system_version_label,LV_ALIGN_OUT_BOTTOM_MID,0,0);
		lv_label_set_text(cpu_label,"MCU: STM32F469NIH6U");
		
		lv_obj_t * desktop_bg_set_label = lv_label_create(ui_rightpanelsystempage);
		lv_obj_set_width(desktop_bg_set_label, 120);
    lv_obj_set_height(desktop_bg_set_label, 30);
		lv_obj_set_style_text_font(desktop_bg_set_label, &HarmonyOS_Sans_SC_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);

		lv_obj_align_to(desktop_bg_set_label,cpu_label,LV_ALIGN_OUT_BOTTOM_LEFT,0,5);
		lv_label_set_text(desktop_bg_set_label,"桌面背景:");
		
		
		// 桌面背景样式设置滚轮
		/*A style to make the selected option larger*/
//    static lv_style_t style_sel;
//    lv_style_init(&style_sel);
//    lv_style_set_text_font(&style_sel, &HarmonyOS_Sans_SC_Medium);

//    const char * opts = "样式1\n样式2\n样式3";
//    lv_obj_t *bg_img_set_roller;

//    /*A roller on the left with left aligned text, and custom width*/
//    bg_img_set_roller = lv_roller_create(ui_rightpanelsystempage);
//    lv_roller_set_options(bg_img_set_roller, opts, LV_ROLLER_MODE_NORMAL);
//    lv_roller_set_visible_row_count(bg_img_set_roller, 2);
//    lv_obj_set_width(bg_img_set_roller, 150);
//    lv_obj_add_style(bg_img_set_roller, &style_sel, LV_PART_SELECTED);
//    lv_obj_set_style_text_align(bg_img_set_roller, LV_TEXT_ALIGN_LEFT, 0);
//    lv_obj_align_to(bg_img_set_roller,desktop_bg_set_label, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
//    lv_obj_add_event_cb(bg_img_set_roller, desktop_bg_img_roller_event_handler, LV_EVENT_ALL, NULL);
//    lv_roller_set_selected(bg_img_set_roller, 0, LV_ANIM_OFF);


    lv_obj_t * bg_img_set_dd = lv_dropdown_create(ui_rightpanelsystempage);
		lv_obj_set_style_text_font(bg_img_set_dd, &HarmonyOS_Sans_SC_Medium, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_dropdown_set_options_static(bg_img_set_dd, "样式1\n"
                                "样式2\n"
                                "样式3");
		lv_dropdown_set_dir(bg_img_set_dd, LV_DIR_BOTTOM);
		lv_dropdown_set_symbol(bg_img_set_dd, LV_SYMBOL_DOWN);
		lv_dropdown_set_selected(bg_img_set_dd,0);
		lv_obj_align_to(bg_img_set_dd,desktop_bg_set_label, LV_ALIGN_OUT_RIGHT_BOTTOM, 0, 0);
    lv_obj_add_event_cb(bg_img_set_dd, desktop_bg_img_dd_event_handler, LV_EVENT_ALL, NULL);

}
