#include "clockpageui.h"
#include "lv_mycalendar.h"
// ʱ������

struct desk_gui_clockscr_obj_s 
{
    lv_obj_t *clockscreen;
    lv_obj_t *top_cond;
    lv_obj_t *clock_cond;
    //lv_obj_t *top_panel;
    //lv_obj_t *bottom_panel;
    // left
    //lv_obj_t *date_panel;   // 100
    //lv_obj_t *calendar;     // 240
    //lv_obj_t *day_news;     // 100
    //right
    lv_obj_t *clock_panel;          // 120
    //lv_obj_t *weather_panel;        // 120
    //lv_obj_t *weather_paner_below;  // 200


    // ʱ����ʾ label
    //lv_obj_t *clock_label;

    uint16_t top_cond_width; // ״̬����ʾ������� Ĭ�� 800
    uint16_t top_cond_height; // ״̬����ʾ����߶� Ĭ�� 40
    
    uint16_t clock_cond_width;  //��ʾ�������   Ĭ�� 800
    uint16_t clock_cond_height; //��ʾ����߶�   Ĭ�� 440
};

typedef struct desk_gui_clockscr_obj_s desk_gui_clockscr_obj_t;

desk_gui_clockscr_obj_t clock_screen_t={
    .clockscreen=NULL,
    .top_cond = NULL,
    .clock_cond=NULL,
    .clock_panel = NULL,
    .top_cond_width=800,
    .top_cond_height=40,
    .clock_cond_width=800,
    .clock_cond_height=440
};



static void calendar_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        if(lv_calendar_get_pressed_date(obj, &date)) {
            LV_LOG_USER("Clicked date: %02d.%02d.%d", date.day, date.month, date.year);
        }
    }
}



//static void back_btn_label_event_cb(lv_event_t *e)
//{
//    lv_obj_t * obj = lv_event_get_target(e);
//    lv_event_code_t code = lv_event_get_code(e);

//    lv_obj_t  *scr = (lv_obj_t *)lv_event_get_user_data(e);

//    if (code == LV_EVENT_CLICKED)
//    {
//        if(scr == clock_screen_t.clockscreen)
//        {
//            LV_LOG_USER("screen is clockscreen\n");
//        }
//        else   
//        {
//            LV_LOG_USER("screen is main screen\n");
//        }
//    }
//}


static void anim_y_cb(void * var, int32_t v)
{
    lv_obj_set_y(var, v);
}

static void lv_desktop_top_symbol_create(lv_obj_t* parent)
{
    if(parent == NULL)
    {
        return ;
    }

    lv_obj_t *topsymbol_panel = lv_obj_create(parent);

    lv_obj_set_size(topsymbol_panel, LV_HOR_RES, 32);       // ���õ���Ļ��С
    lv_obj_set_style_radius(topsymbol_panel,0,LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(topsymbol_panel,lv_color_make(0,0,0),LV_STATE_DEFAULT);
    lv_obj_clear_flag(topsymbol_panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_width(topsymbol_panel,0,LV_STATE_DEFAULT);
    lv_obj_align(topsymbol_panel,LV_ALIGN_TOP_MID,0,0);


    // ���� symbol
    // symbol ����  wifi ״̬  ��ص���   SD ��״̬

    
//    lv_obj_t *powerymbol  = lv_label_create(topsymbol_panel);
//    lv_obj_align(powerymbol, LV_ALIGN_RIGHT_MID, 0, 0);
//    lv_label_set_text(powerymbol,LV_SYMBOL_BATTERY_FULL);
//    lv_obj_set_style_text_color(powerymbol,lv_color_make(255,255,255),LV_STATE_DEFAULT);

    lv_obj_t *wifisymbol  = lv_label_create(topsymbol_panel);
    lv_obj_align(wifisymbol, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_label_set_text(wifisymbol,LV_SYMBOL_WIFI);
    lv_obj_set_style_text_color(wifisymbol,lv_color_make(255,255,255),LV_STATE_DEFAULT);

    lv_obj_t *sdcardymbol  = lv_label_create(topsymbol_panel);
    lv_obj_align(sdcardymbol, LV_ALIGN_RIGHT_MID,-32, 0);
    lv_label_set_text(sdcardymbol,LV_SYMBOL_SD_CARD);
    lv_obj_set_style_text_color(sdcardymbol,lv_color_make(255,255,255),LV_STATE_DEFAULT);
    

//    lv_obj_t *back_btn = lv_btn_create(topsymbol_panel);
//    lv_obj_set_size(back_btn,32,32);
//    lv_obj_align(back_btn,LV_ALIGN_LEFT_MID,0,0);
//    lv_obj_t *back_btn_label = lv_label_create(back_btn);
//    lv_obj_align(back_btn_label, LV_ALIGN_CENTER,0, 0);
//    lv_label_set_text(back_btn_label,LV_SYMBOL_LEFT);
//    lv_obj_set_style_text_color(back_btn_label,lv_color_make(255,255,255),LV_STATE_DEFAULT);


//    lv_obj_add_event_cb(back_btn,back_btn_label_event_cb,LV_EVENT_CLICKED,(void *)lv_scr_act());


    //��������״̬�����붯��
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, topsymbol_panel);
    // lv_anim_set_exec_cb(&a, [](void* var, int32_t v) {
    //     lv_obj_set_height((lv_obj_t*)var, v);
    // });
    lv_anim_set_exec_cb(&a, anim_y_cb);
    lv_anim_set_values(&a, -32, 0);
    lv_anim_set_delay(&a,500);
    lv_anim_set_time(&a, 1500);
    // lv_anim_set_ready_cb(&a, StatusBar_onAnimHeightFinish);
    lv_anim_start(&a);

}


// 
void clockpageui(lv_obj_t *page)
{
    if(page==NULL)
    {
        LV_LOG_USER("lv_obj_t page is null\n");
        return ;
    }

    clock_screen_t.clockscreen = lv_obj_create(page);

    //ɾ������������ʽ
    lv_obj_remove_style_all(clock_screen_t.clockscreen);
    lv_obj_set_size(clock_screen_t.clockscreen, LV_HOR_RES, LV_VER_RES);       // ���õ���Ļ��С
    lv_obj_center(clock_screen_t.clockscreen);
		lv_obj_set_style_bg_color(clock_screen_t.clockscreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_radius(clock_screen_t.clockscreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(clock_screen_t.clockscreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(clock_screen_t.clockscreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(clock_screen_t.clockscreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(clock_screen_t.clockscreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(clock_screen_t.clockscreen, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);

		
		
    clock_screen_t.top_cond = lv_obj_create(clock_screen_t.clockscreen);
    lv_obj_set_height(clock_screen_t.top_cond,clock_screen_t.top_cond_height);
    lv_obj_set_width(clock_screen_t.top_cond,clock_screen_t.top_cond_width);

    lv_obj_set_style_radius(clock_screen_t.top_cond,0,LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(clock_screen_t.top_cond,lv_color_make(0,0,0),LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(clock_screen_t.top_cond, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(clock_screen_t.top_cond, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(clock_screen_t.top_cond, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(clock_screen_t.top_cond, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(clock_screen_t.top_cond,LV_ALIGN_TOP_MID,0,0);

    //顶部状态栏控件
    //lv_desktop_top_symbol_create(clock_screen_t.clockscreen);
    
    clock_screen_t.clock_cond = lv_obj_create(clock_screen_t.clockscreen);
    lv_obj_set_height(clock_screen_t.clock_cond,clock_screen_t.clock_cond_height);
    lv_obj_set_width(clock_screen_t.clock_cond,clock_screen_t.clock_cond_width);

    lv_obj_set_style_radius(clock_screen_t.clock_cond,0,LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(clock_screen_t.clock_cond,lv_color_make(81,81,81),LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(clock_screen_t.clock_cond,LV_OPA_80,LV_STATE_DEFAULT);
    lv_obj_clear_flag(clock_screen_t.clock_cond, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_style_border_width(clock_screen_t.clock_cond,0,LV_STATE_DEFAULT);
    lv_obj_align(clock_screen_t.clock_cond,LV_ALIGN_CENTER,0,20);
    
		//创建自定义日历控件
		lv_my_calendar_create(clock_screen_t.clock_cond);

    clock_screen_t.clock_panel = lv_obj_create(clock_screen_t.clock_cond);
    lv_obj_clear_flag(clock_screen_t.clock_panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_style_bg_color(clock_screen_t.clock_panel,lv_color_make(255,255,255),LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(clock_screen_t.clock_panel,LV_OPA_TRANSP,LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(clock_screen_t.clock_panel,lv_color_make(255,255,255),LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(clock_screen_t.clock_panel,0,LV_STATE_DEFAULT);
    lv_obj_set_height(clock_screen_t.clock_panel,120);
    lv_obj_set_width(clock_screen_t.clock_panel,300);
    lv_obj_align(clock_screen_t.clock_panel,LV_ALIGN_RIGHT_MID,0,0);


		lv_clock_label_create(clock_screen_t.clock_panel);

}




// ʱ�Ӷ����ؼ�

#define CLOCK_LABEL_PRE 0
#define CLOCK_LABEL_CUR 1
#define CLOCK_LABEL_NUM 2

#define NUM_X_OFFSET 30
#define CLOCK_LABEL_Y_OFFSET 26

static lv_obj_t* clock_label_cond;
static lv_obj_t* clock_hour_label[CLOCK_LABEL_NUM][CLOCK_LABEL_NUM];  //��ʾСʱ
static lv_obj_t* clock_min_label[CLOCK_LABEL_NUM][CLOCK_LABEL_NUM];   //��ʾ����
static lv_obj_t* clock_sec_label[CLOCK_LABEL_NUM][CLOCK_LABEL_NUM];   //��ʾ����


void lv_clock_label_create(lv_obj_t *parent)
{
    clock_label_cond = lv_obj_create(parent);
    lv_obj_remove_style_all(clock_label_cond);
    lv_obj_set_style_bg_color(clock_label_cond, lv_color_make(0, 0, 0), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(clock_label_cond, (lv_opa_t)LV_OPA_TRANSP, LV_STATE_DEFAULT);
    lv_obj_center(clock_label_cond);
    lv_obj_set_size(clock_label_cond,280, 100);


    for (int i = 0; i < CLOCK_LABEL_NUM; i++)
    {
        clock_hour_label[CLOCK_LABEL_PRE][i] = lv_label_create(clock_label_cond);
        lv_label_set_long_mode(clock_hour_label[CLOCK_LABEL_PRE][i], LV_LABEL_LONG_WRAP);
        lv_obj_set_pos(clock_hour_label[CLOCK_LABEL_PRE][i], NUM_X_OFFSET * i, CLOCK_LABEL_Y_OFFSET);
        lv_obj_set_style_text_font(clock_hour_label[CLOCK_LABEL_PRE][i], &lv_font_montserrat_48, LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(clock_hour_label[CLOCK_LABEL_PRE][i], lv_color_make(255, 157, 0), LV_STATE_DEFAULT);
        // lv_label_set_text_fmt(clock_hour_label[CLOCK_LABEL_PRE][i], "%d", (Rx5808_Freq[Chx_count][channel_count] / lv_pow(10, fre_label_count - i - 1)) % 10);
        lv_label_set_text_fmt(clock_hour_label[CLOCK_LABEL_PRE][i],"%d",(18/ lv_pow(10, CLOCK_LABEL_NUM - i - 1)) % 10);
        lv_label_set_long_mode(clock_hour_label[CLOCK_LABEL_PRE][i], LV_LABEL_LONG_WRAP);
    }
    for (int i = 0; i < CLOCK_LABEL_NUM; i++)
    {
        clock_hour_label[CLOCK_LABEL_CUR][i] = lv_label_create(clock_label_cond);
        lv_label_set_long_mode(clock_hour_label[CLOCK_LABEL_CUR][i], LV_LABEL_LONG_WRAP);
        lv_obj_set_pos(clock_hour_label[CLOCK_LABEL_CUR][i], NUM_X_OFFSET * i, CLOCK_LABEL_Y_OFFSET);
        lv_obj_set_style_text_font(clock_hour_label[CLOCK_LABEL_CUR][i], &lv_font_montserrat_48, LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(clock_hour_label[CLOCK_LABEL_CUR][i], lv_color_make(255, 157, 0), LV_STATE_DEFAULT);
        lv_label_set_text_fmt(clock_hour_label[CLOCK_LABEL_CUR][i], "%d",(18/ lv_pow(10, CLOCK_LABEL_NUM - i - 1)) % 10);
        lv_label_set_long_mode(clock_hour_label[CLOCK_LABEL_CUR][i], LV_LABEL_LONG_WRAP);
    }

    lv_obj_t *lv_clock_hour_min = lv_label_create(clock_label_cond);
    lv_label_set_long_mode(lv_clock_hour_min, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(lv_clock_hour_min, NUM_X_OFFSET*2, CLOCK_LABEL_Y_OFFSET);
    lv_obj_set_style_text_font(lv_clock_hour_min, &lv_font_montserrat_48, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(lv_clock_hour_min, lv_color_make(255, 157, 0), LV_STATE_DEFAULT);
    lv_label_set_text(lv_clock_hour_min,":");
    lv_label_set_long_mode(lv_clock_hour_min, LV_LABEL_LONG_WRAP);

    // ����
    for (int i = 0; i < CLOCK_LABEL_NUM; i++)
    {
        clock_min_label[CLOCK_LABEL_PRE][i] = lv_label_create(clock_label_cond);
        lv_label_set_long_mode(clock_min_label[CLOCK_LABEL_PRE][i], LV_LABEL_LONG_WRAP);
        lv_obj_set_pos(clock_min_label[CLOCK_LABEL_PRE][i], NUM_X_OFFSET*2+NUM_X_OFFSET/2+NUM_X_OFFSET * i, CLOCK_LABEL_Y_OFFSET);
        lv_obj_set_style_text_font(clock_min_label[CLOCK_LABEL_PRE][i], &lv_font_montserrat_48, LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(clock_min_label[CLOCK_LABEL_PRE][i], lv_color_make(255, 157, 0), LV_STATE_DEFAULT);
        lv_label_set_text_fmt(clock_min_label[CLOCK_LABEL_PRE][i], "%d",(30/ lv_pow(10, CLOCK_LABEL_NUM - i - 1)) % 10);
        lv_label_set_long_mode(clock_min_label[CLOCK_LABEL_PRE][i], LV_LABEL_LONG_WRAP);
    }
    for (int i = 0; i < CLOCK_LABEL_NUM; i++)
    {
        clock_min_label[CLOCK_LABEL_CUR][i] = lv_label_create(clock_label_cond);
        lv_label_set_long_mode(clock_min_label[CLOCK_LABEL_CUR][i], LV_LABEL_LONG_WRAP);
        lv_obj_set_pos(clock_min_label[CLOCK_LABEL_CUR][i], NUM_X_OFFSET*2+NUM_X_OFFSET/2+NUM_X_OFFSET * i, CLOCK_LABEL_Y_OFFSET);
        lv_obj_set_style_text_font(clock_min_label[CLOCK_LABEL_CUR][i], &lv_font_montserrat_48, LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(clock_min_label[CLOCK_LABEL_CUR][i], lv_color_make(255, 157, 0), LV_STATE_DEFAULT);
        lv_label_set_text_fmt(clock_min_label[CLOCK_LABEL_CUR][i], "%d",(30/ lv_pow(10, CLOCK_LABEL_NUM - i - 1)) % 10);
        lv_label_set_long_mode(clock_min_label[CLOCK_LABEL_CUR][i], LV_LABEL_LONG_WRAP);
    }

    lv_obj_t *lv_clock_min_sec = lv_label_create(clock_label_cond);
    lv_label_set_long_mode(lv_clock_min_sec, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(lv_clock_min_sec, NUM_X_OFFSET*4+NUM_X_OFFSET/2, CLOCK_LABEL_Y_OFFSET);
    lv_obj_set_style_text_font(lv_clock_min_sec, &lv_font_montserrat_48, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(lv_clock_min_sec, lv_color_make(255, 157, 0), LV_STATE_DEFAULT);
    lv_label_set_text(lv_clock_min_sec,":");
    lv_label_set_long_mode(lv_clock_min_sec, LV_LABEL_LONG_WRAP);

    for (int i = 0; i < CLOCK_LABEL_NUM; i++)
    {
        clock_sec_label[CLOCK_LABEL_PRE][i] = lv_label_create(clock_label_cond);
        lv_label_set_long_mode(clock_sec_label[CLOCK_LABEL_PRE][i], LV_LABEL_LONG_WRAP);
        lv_obj_set_pos(clock_sec_label[CLOCK_LABEL_PRE][i], NUM_X_OFFSET*5+NUM_X_OFFSET * i, CLOCK_LABEL_Y_OFFSET);
        lv_obj_set_style_text_font(clock_sec_label[CLOCK_LABEL_PRE][i], &lv_font_montserrat_48, LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(clock_sec_label[CLOCK_LABEL_PRE][i], lv_color_make(255, 157, 0), LV_STATE_DEFAULT);
        lv_label_set_text_fmt(clock_sec_label[CLOCK_LABEL_PRE][i], "%d",(0/ lv_pow(10, CLOCK_LABEL_NUM - i - 1)) % 10);
        lv_label_set_long_mode(clock_sec_label[CLOCK_LABEL_PRE][i], LV_LABEL_LONG_WRAP);
    }
    for (int i = 0; i < CLOCK_LABEL_NUM; i++)
    {
        clock_sec_label[CLOCK_LABEL_CUR][i] = lv_label_create(clock_label_cond);
        lv_label_set_long_mode(clock_sec_label[CLOCK_LABEL_CUR][i], LV_LABEL_LONG_WRAP);
        lv_obj_set_pos(clock_sec_label[CLOCK_LABEL_CUR][i], NUM_X_OFFSET*5+NUM_X_OFFSET * i, CLOCK_LABEL_Y_OFFSET);
        lv_obj_set_style_text_font(clock_sec_label[CLOCK_LABEL_CUR][i], &lv_font_montserrat_48, LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(clock_sec_label[CLOCK_LABEL_CUR][i], lv_color_make(255, 157, 0), LV_STATE_DEFAULT);
        lv_label_set_text_fmt(clock_sec_label[CLOCK_LABEL_CUR][i], "%d",(0/ lv_pow(10, CLOCK_LABEL_NUM - i - 1)) % 10);
        lv_label_set_long_mode(clock_sec_label[CLOCK_LABEL_CUR][i], LV_LABEL_LONG_WRAP);
    }
}

static void lv_clock_label_pre_label_update()
{

    for (int i = 0; i < CLOCK_LABEL_NUM; i++)
    {
        if(clock_hour_label[CLOCK_LABEL_PRE][i])
        {
            lv_label_set_text_fmt(clock_hour_label[CLOCK_LABEL_PRE][i], "%c", lv_label_get_text(clock_hour_label[CLOCK_LABEL_CUR][i])[0]);
        }
        if(clock_min_label[CLOCK_LABEL_PRE][i])
        {
            lv_label_set_text_fmt(clock_min_label[CLOCK_LABEL_PRE][i], "%c", lv_label_get_text(clock_min_label[CLOCK_LABEL_CUR][i])[0]);
        }
        if(clock_sec_label[CLOCK_LABEL_PRE][i])
        {
            lv_label_set_text_fmt(clock_sec_label[CLOCK_LABEL_PRE][i], "%c", lv_label_get_text(clock_sec_label[CLOCK_LABEL_CUR][i])[0]);
        }
    }
}

void lv_clock_label_update(uint8_t hour, uint8_t min,uint8_t sec)
{
		for(int i = 0; i < CLOCK_LABEL_NUM; i++)
		{
			if(!clock_hour_label[CLOCK_LABEL_CUR][i])
			{
				return ;
			}
		}
    for (int i = 0; i < CLOCK_LABEL_NUM; i++)
    {
        lv_label_set_text_fmt(clock_hour_label[CLOCK_LABEL_CUR][i], "%d", (hour/ lv_pow(10, CLOCK_LABEL_NUM - i - 1)) % 10);
        lv_label_set_text_fmt(clock_min_label[CLOCK_LABEL_CUR][i], "%d", (min/ lv_pow(10, CLOCK_LABEL_NUM - i - 1)) % 10);
        lv_label_set_text_fmt(clock_sec_label[CLOCK_LABEL_CUR][i], "%d", (sec/ lv_pow(10, CLOCK_LABEL_NUM - i - 1)) % 10);

        if (lv_label_get_text(clock_hour_label[CLOCK_LABEL_PRE][i])[0] != lv_label_get_text(clock_hour_label[CLOCK_LABEL_CUR][i])[0])
        {
            // lv_amin_start(clock_hour_label[CLOCK_LABEL_CUR][i], lv_pow(-1, (i % 2)) * 50, 0, 1, 100, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, lv_anim_path_ease_in);
            // lv_amin_start(clock_hour_label[CLOCK_LABEL_PRE][i], 0, lv_pow(-1, (i % 2)) * -50, 1,100, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, lv_anim_path_ease_in);
            lv_amin_start(clock_hour_label[CLOCK_LABEL_CUR][i], 50+CLOCK_LABEL_Y_OFFSET, 0+CLOCK_LABEL_Y_OFFSET, 1, 100, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, lv_anim_path_ease_in);
            lv_amin_start(clock_hour_label[CLOCK_LABEL_PRE][i], 0+CLOCK_LABEL_Y_OFFSET,-50-CLOCK_LABEL_Y_OFFSET, 1,100, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, lv_anim_path_ease_in);
        }

        if (lv_label_get_text(clock_min_label[CLOCK_LABEL_PRE][i])[0] != lv_label_get_text(clock_min_label[CLOCK_LABEL_CUR][i])[0])
        {
            // lv_amin_start(clock_min_label[CLOCK_LABEL_CUR][i], lv_pow(-1, (i % 2)) * 50, 0, 1, 100, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, lv_anim_path_ease_in);
            // lv_amin_start(clock_min_label[CLOCK_LABEL_PRE][i], 0, lv_pow(-1, (i % 2)) * -50, 1, 100, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, lv_anim_path_ease_in);
            lv_amin_start(clock_min_label[CLOCK_LABEL_CUR][i], 50+CLOCK_LABEL_Y_OFFSET, 0+CLOCK_LABEL_Y_OFFSET, 1, 100, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, lv_anim_path_ease_in);
            lv_amin_start(clock_min_label[CLOCK_LABEL_PRE][i], 0+CLOCK_LABEL_Y_OFFSET, -50-CLOCK_LABEL_Y_OFFSET, 1, 100, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, lv_anim_path_ease_in);
        }

        if (lv_label_get_text(clock_sec_label[CLOCK_LABEL_PRE][i])[0] != lv_label_get_text(clock_sec_label[CLOCK_LABEL_CUR][i])[0])
        {
            // lv_amin_start(clock_sec_label[CLOCK_LABEL_CUR][i], lv_pow(-1, (i % 2)) * 50, 0, 1, 100, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, lv_anim_path_ease_in);
            // lv_amin_start(clock_sec_label[CLOCK_LABEL_PRE][i], 0, lv_pow(-1, (i % 2)) * -50, 1, 100, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, lv_anim_path_ease_in);
            lv_amin_start(clock_sec_label[CLOCK_LABEL_CUR][i], 50+CLOCK_LABEL_Y_OFFSET, 0+CLOCK_LABEL_Y_OFFSET, 1, 100, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, lv_anim_path_ease_in);
            lv_amin_start(clock_sec_label[CLOCK_LABEL_PRE][i], 0+CLOCK_LABEL_Y_OFFSET, -50-CLOCK_LABEL_Y_OFFSET, 1, 100, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, lv_anim_path_ease_in);
        
        }
    }
    lv_fun_delayed(lv_clock_label_pre_label_update, 200);
}


// void lv_clock_calendar_set_date(uint32_t year,uint32_t month,uint32_t day)
// {
// 		if(clock_screen_t.calendar!=NULL)
// 		{
// 			lv_calendar_set_today_date(clock_screen_t.calendar,year , month,day);
// 			lv_calendar_set_showed_date(clock_screen_t.calendar, year, month);	
// 		}
// }


// void lv_clock_set_time(const char* time_str)
// {
// 	if(clock_screen_t.clock_label !=NULL)
// 	{
//     lv_label_set_text(clock_screen_t.clock_label, time_str);		
// 	}
// }


//void clockscr_timer_cb(lv_timer_t * timer)
//{
//    uint32_t * user_data = timer->user_data;
//	  char clocktime[10]={0};   
//		time_t now;
//	  struct tm *p;
//		/* output current time */
//		now = time(RT_NULL);
//		p = localtime(&now); 
////		rt_kprintf("%.*s", 25, ctime(&now));
//		if(p)
//		{

//			rt_snprintf(clocktime,10,"%02d:%02d",p->tm_hour,p->tm_min);
//			lv_clock_set_time(clocktime);
//		}
//		// ��������
//		lv_clock_calendar_set_date(p->tm_year+1900, p->tm_mon+1, p->tm_mday);

//}

//void clockscr_timer_task_init(void)
//{
//    static uint32_t timer_delay = 1000; // 1s
//    static uint32_t clock_second = 0;
//    lv_timer_t *imgscr_timer = lv_timer_create(clockscr_timer_cb,timer_delay,&clock_second);
//}


