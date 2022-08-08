#include <lvgl.h>
#include "lv_backbtn_test.h"
#include "lv_clockscreen_page.h"

LV_FONT_DECLARE(lv_font_han_sans_bold_number_only_114);





// 桌面相册显示页面 示例

// 800 * 480

// 一个界面显示两张图片 每张图片 320*240 
// 图片外框大小设置为 340*260

struct imgscr_obj_s 
{
    lv_obj_t *imgscreen;
    lv_obj_t *top_cond; // 状态栏显示区域
    lv_obj_t *img_cond; // 图像显示区域

    lv_obj_t *top_panel; // 顶部状态栏
    lv_obj_t *img_panel; // 图像显示

    lv_obj_t *img_layout_left;   // 340 * 260
    lv_obj_t *img_layout_right;  // 340 * 260

    lv_obj_t *img_left;         // 320 * 240
    lv_obj_t *img_right;        // 320 * 240

    uint16_t top_cond_width; // 状态栏显示区域宽度 默认 800
    uint16_t top_cond_height; // 状态栏显示区域高度 默认 40
    
    uint16_t img_cond_width;  // 图像显示区域宽度   默认 800
    uint16_t img_cond_height; // 图像显示区域高度   默认 440
};


typedef struct imgscr_obj_s imgscr_obj_t;

imgscr_obj_t imgscr={
    .imgscreen=NULL,
    .top_cond=NULL,
    .img_cond=NULL,
    .top_panel=NULL,
    .img_panel= NULL,
    .img_layout_left=NULL,
    .img_layout_right=NULL,
    .img_left=NULL,
    .img_right=NULL,
    .top_cond_width=800,
    .top_cond_height=40,
    .img_cond_width=800,
    .img_cond_height=440
};



static void img_opa_anim_cb(void * var, int32_t v);


static lv_style_t label_time_style;


void lv_imgscr_page_create(lv_obj_t* parent)
{
    if(parent == NULL)
    {
        return;
    }

    imgscr.imgscreen = lv_obj_create(parent);

    
    // 删除对象所有样式
    lv_obj_remove_style_all(imgscr.imgscreen);
    lv_obj_set_size(imgscr.imgscreen, LV_HOR_RES, LV_VER_RES);       // 设置到屏幕大小
    lv_obj_center(imgscr.imgscreen);
    lv_obj_clear_flag(imgscr.imgscreen, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);


    imgscr.top_cond = lv_obj_create(imgscr.imgscreen);
    lv_obj_set_height(imgscr.top_cond,imgscr.top_cond_height);
    lv_obj_set_width(imgscr.top_cond,imgscr.top_cond_width);

    lv_obj_set_style_radius(imgscr.top_cond,0,LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(imgscr.top_cond,lv_color_make(0,0,0),LV_STATE_DEFAULT);
    lv_obj_clear_flag(imgscr.top_cond, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(imgscr.top_cond,LV_ALIGN_TOP_MID,0,0);

    imgscr.img_cond = lv_obj_create(imgscr.imgscreen);
    lv_obj_set_height(imgscr.img_cond,imgscr.img_cond_height);
    lv_obj_set_width(imgscr.img_cond,imgscr.img_cond_width);

    lv_obj_set_style_radius(imgscr.img_cond,0,LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(imgscr.img_cond,lv_color_make(81,81,81),LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imgscr.img_cond,LV_OPA_80,LV_STATE_DEFAULT);
    lv_obj_clear_flag(imgscr.img_cond, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(imgscr.img_cond,LV_ALIGN_BOTTOM_MID,0,0);


    
    imgscr.img_panel = lv_obj_create(imgscr.img_cond);
    lv_obj_set_height(imgscr.img_panel,imgscr.img_cond_height-40);
    lv_obj_set_width(imgscr.img_panel,imgscr.img_cond_width-20);

    lv_obj_set_style_radius(imgscr.img_panel,5,LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(imgscr.img_panel,lv_color_make(181,181,181),LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imgscr.img_panel,LV_OPA_40,LV_STATE_DEFAULT);
    lv_obj_clear_flag(imgscr.img_panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    // lv_obj_align(imgscr.img_panel,LV_ALIGN_BOTTOM_MID,0,0);
    lv_obj_center(imgscr.img_panel);


    imgscr.img_layout_left = lv_obj_create(imgscr.img_panel);
    lv_obj_set_height(imgscr.img_layout_left,340);
    lv_obj_set_width(imgscr.img_layout_left,260);

    lv_obj_set_style_radius(imgscr.img_layout_left,10,LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(imgscr.img_layout_left,lv_color_make(200,200,200),LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imgscr.img_layout_left,LV_OPA_TRANSP,LV_STATE_DEFAULT);
    lv_obj_clear_flag(imgscr.img_layout_left, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(imgscr.img_layout_left,LV_ALIGN_CENTER,-195,0);

    imgscr.img_layout_right = lv_obj_create(imgscr.img_panel);
    lv_obj_set_height(imgscr.img_layout_right,340);
    lv_obj_set_width(imgscr.img_layout_right,260);

    lv_obj_set_style_radius(imgscr.img_layout_right,10,LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(imgscr.img_layout_right,lv_color_make(200,200,200),LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imgscr.img_layout_right,LV_OPA_TRANSP,LV_STATE_DEFAULT);
    lv_obj_clear_flag(imgscr.img_layout_right, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(imgscr.img_layout_right,LV_ALIGN_CENTER,195,0);

    // 显示 320*240 图像
//    imgscr.img_left = lv_img_create(imgscr.img_layout_left);
//    lv_img_set_src(imgscr.img_left,"S:imgs/esp32show.jpg");
//    lv_obj_center(imgscr.img_left);
		
		
//    lv_anim_t img_anim;
//    lv_anim_init(&img_anim);
//    lv_anim_set_var(&img_anim, imgscr.img_left);
//    lv_anim_set_exec_cb(&img_anim, img_opa_anim_cb);
//    lv_anim_set_values(&img_anim, 0, 255);
//    lv_anim_set_delay(&img_anim,1000);
//    lv_anim_set_time(&img_anim, 2000);
//    lv_anim_set_playback_delay(&img_anim, 10000);
//    lv_anim_set_playback_time(&img_anim, 2000);
//    lv_anim_start(&img_anim);

//    imgscr.img_right = lv_img_create(imgscr.img_layout_right);
//    lv_img_set_src(imgscr.img_right,"S:imgs/tiger.jpg");
//    lv_obj_center(imgscr.img_right);

}

// 实现桌面相册切换


static void img_opa_anim_cb(void * var, int32_t v)
{
    // lv_obj_set_y(var, v);
    lv_obj_set_style_opa(var,v,LV_STATE_DEFAULT);
}



static void imgscr_run_loop(const char *imgsrc)
{
    if(imgsrc ==NULL)
    {
        return ;
    }
    //创建图片切换动画
    // lv_anim_t a1;
    // lv_anim_init(&a1);
    // lv_anim_set_var(&a1, imgscr.img_left);
    // lv_anim_set_exec_cb(&a1, img_opa_anim_cb);
    // lv_anim_set_values(&a1, 255, 0);
    // lv_anim_set_delay(&a1,1000);
    // lv_anim_set_time(&a1, 1500);
    // lv_anim_start(&a1);

    lv_img_set_src(imgscr.img_left,imgsrc);

    //创建图片切换动画
    lv_anim_t a2;
    lv_anim_init(&a2);
    lv_anim_set_var(&a2, imgscr.img_left);
    lv_anim_set_exec_cb(&a2, img_opa_anim_cb);
    lv_anim_set_values(&a2, 0, 255);
    lv_anim_set_delay(&a2,1000);
    lv_anim_set_time(&a2, 2000);
    lv_anim_set_playback_delay(&a2, 10000);
    lv_anim_set_playback_time(&a2, 2000);
    lv_anim_start(&a2);

}

// void my_timer(lv_timer_t * timer)
// {
//   uint32_t * user_data = timer->user_data;
//   printf("my_timer called with user data: %d\n", *user_data);

//   if(something_happened) {
//     something_happened = false;
//     lv_btn_create(lv_scr_act(), NULL);
//   }
// }


// static uint32_t user_data = 10;
// lv_timer_t * timer = lv_timer_create(my_timer, 500,  &user_data);


static char *imgsrc_path[2]={"S:imgs/tiger.jpg","S:imgs/esp32show.jpg"};


void imgscr_timer_cb(lv_timer_t * timer)
{
    uint32_t * user_data = timer->user_data;
    LV_LOG_USER("imgscr_timer called with user data: %d\n", *user_data);
    imgscr_run_loop(imgsrc_path[*user_data]);
    (*user_data)++;
    if(*user_data==2)
    {
        *user_data=0;
    }
}

void imgscr_timer_task_init(void)
{
    static uint32_t timer_delay = 15000; // 15s
    static uint32_t user_data = 0;
    lv_timer_t *imgscr_timer = lv_timer_create(imgscr_timer_cb,timer_delay,&user_data);
}



// ------------------------------------------------------------------------

// clockscr_obj_t clock_screen_t={
//     .clockscreen=NULL,
//     .top_cond = NULL,
//     .clock_cond=NULL,
//     .top_panel=NULL,
//     .bottom_panel=NULL,
//     .date_panel = NULL,
//     .calendar = NULL,
//     .day_news = NULL,
//     .clock_panel = NULL,
//     .weather_panel=NULL,
//     .weather_paner_below= NULL,
//     .clock_label = NULL,
//     .top_cond_width=800,
//     .top_cond_height=40,
//     .clock_cond_width=800,
//     .clock_cond_height=440
// };



// static void calendar_event_handler(lv_event_t * e)
// {
//     lv_event_code_t code = lv_event_get_code(e);
//     lv_obj_t * obj = lv_event_get_current_target(e);

//     if(code == LV_EVENT_VALUE_CHANGED) {
//         lv_calendar_date_t date;
//         if(lv_calendar_get_pressed_date(obj, &date)) {
//             LV_LOG_USER("Clicked date: %02d.%02d.%d", date.day, date.month, date.year);
//         }
//     }
// }


// // 
// void lv_clockscr_create(lv_obj_t *parent)
// {
//     if(parent==NULL)
//     {
//         LV_LOG_USER("lv_obj_t parent is null\n");
//         return ;
//     }

//     clock_screen_t.clockscreen = lv_obj_create(parent);

//     //删除对象所有样式
//     lv_obj_remove_style_all(clock_screen_t.clockscreen);
//     lv_obj_set_size(clock_screen_t.clockscreen, LV_HOR_RES, LV_VER_RES);       // 设置到屏幕大小
//     lv_obj_center(clock_screen_t.clockscreen);
//     lv_obj_clear_flag(clock_screen_t.clockscreen, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);

//     clock_screen_t.top_cond = lv_obj_create(clock_screen_t.clockscreen);

//     lv_obj_set_height(clock_screen_t.top_cond,clock_screen_t.top_cond_height);
//     lv_obj_set_width(clock_screen_t.top_cond,clock_screen_t.top_cond_width);

//     lv_obj_set_style_radius(clock_screen_t.top_cond,0,LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_color(clock_screen_t.top_cond,lv_color_make(0,0,0),LV_STATE_DEFAULT);
//     lv_obj_clear_flag(clock_screen_t.top_cond, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
//     lv_obj_align(clock_screen_t.top_cond,LV_ALIGN_TOP_MID,0,0);


//     lv_desktop_top_symbol_create(clock_screen_t.clockscreen);

//     clock_screen_t.clock_cond = lv_obj_create(clock_screen_t.clockscreen);
//     lv_obj_set_height(clock_screen_t.clock_cond,clock_screen_t.clock_cond_height);
//     lv_obj_set_width(clock_screen_t.clock_cond,clock_screen_t.clock_cond_width);

//     lv_obj_set_style_radius(clock_screen_t.clock_cond,0,LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_color(clock_screen_t.clock_cond,lv_color_make(81,81,81),LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_opa(clock_screen_t.clock_cond,LV_OPA_80,LV_STATE_DEFAULT);
//     lv_obj_clear_flag(clock_screen_t.clock_cond, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
//     lv_obj_align(clock_screen_t.clock_cond,LV_ALIGN_BOTTOM_MID,0,0);


//     clock_screen_t.date_panel = lv_obj_create(clock_screen_t.clock_cond);
//     lv_obj_set_height(clock_screen_t.date_panel,80);
//     lv_obj_set_width(clock_screen_t.date_panel,480);
//     lv_obj_set_style_bg_color(clock_screen_t.date_panel,lv_color_make(81,0,0),LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_opa(clock_screen_t.date_panel,LV_OPA_50,LV_STATE_DEFAULT);
//     lv_obj_align(clock_screen_t.date_panel,LV_ALIGN_TOP_LEFT,-10,-10);



//     clock_screen_t.calendar = lv_calendar_create(clock_screen_t.clock_cond);
//     lv_obj_set_size(clock_screen_t.calendar, 300, 300);
//     // lv_obj_set_style_bg_color(clock_screen_t.calendar,lv_color_make(255,255,255),LV_STATE_DEFAULT);
//     // lv_obj_set_style_bg_opa(clock_screen_t.date_panel,LV_OPA_COVER,LV_STATE_DEFAULT);
//     lv_obj_align(clock_screen_t.calendar, LV_ALIGN_TOP_LEFT,150, 75);
    
//     lv_obj_add_event_cb(clock_screen_t.calendar, calendar_event_handler, LV_EVENT_ALL, NULL);

//     lv_calendar_set_today_date(clock_screen_t.calendar, 2022, 07, 04);
//     lv_calendar_set_showed_date(clock_screen_t.calendar, 2022, 07);

//     // /*Highlight a few days*/
//     // static lv_calendar_date_t highlighted_days[3];       /*Only its pointer will be saved so should be static*/
//     // highlighted_days[0].year = 2021;
//     // highlighted_days[0].month = 02;
//     // highlighted_days[0].day = 6;

//     // highlighted_days[1].year = 2021;
//     // highlighted_days[1].month = 02;
//     // highlighted_days[1].day = 11;

//     // highlighted_days[2].year = 2022;
//     // highlighted_days[2].month = 02;
//     // highlighted_days[2].day = 22;

//     // lv_calendar_set_highlighted_dates(clock_screen_t.calendar, highlighted_days, 3);

// #if LV_USE_CALENDAR_HEADER_DROPDOWN
//     lv_calendar_header_dropdown_create(clock_screen_t.calendar);
// #elif LV_USE_CALENDAR_HEADER_ARROW
//     lv_calendar_header_arrow_create(clock_screen_t.calendar);
// #endif
//     lv_calendar_set_showed_date(clock_screen_t.calendar, 2022, 07);
    
    
//     // 新闻

//     clock_screen_t.day_news = lv_obj_create(clock_screen_t.clock_cond);
//     lv_obj_clear_flag(clock_screen_t.day_news, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);

//     lv_obj_set_height(clock_screen_t.day_news,40);
//     lv_obj_set_width(clock_screen_t.day_news,480);
//     lv_obj_set_style_bg_color(clock_screen_t.day_news,lv_color_make(0,81,0),LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_opa(clock_screen_t.day_news,LV_OPA_TRANSP,LV_STATE_DEFAULT);
//     lv_obj_align(clock_screen_t.day_news,LV_ALIGN_TOP_LEFT,-10,375);


//     // 时间

//     clock_screen_t.clock_panel = lv_obj_create(clock_screen_t.clock_cond);
//     lv_obj_clear_flag(clock_screen_t.clock_panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
//     lv_obj_set_height(clock_screen_t.clock_panel,120);
//     lv_obj_set_width(clock_screen_t.clock_panel,300);
//     lv_obj_align(clock_screen_t.clock_panel,LV_ALIGN_TOP_RIGHT,20,-10);

    
//     lv_style_init(&label_time_style);
//     lv_style_set_text_opa(&label_time_style, LV_OPA_COVER);
//     lv_style_set_text_color(&label_time_style, lv_color_hex(0xF4AA56));
//     lv_style_set_text_font(&label_time_style, &lv_font_montserrat_48);
//     // lv_style_set_text_font(&label_time_style, &lv_font_han_sans_bold_number_only_114);
    

//     clock_screen_t.clock_label = lv_label_create(clock_screen_t.clock_panel);
//     lv_obj_add_style(clock_screen_t.clock_label, &label_time_style,LV_STATE_DEFAULT);
//     lv_obj_align(clock_screen_t.clock_label, LV_ALIGN_CENTER, 0, 0);
//     lv_label_set_text(clock_screen_t.clock_label, "18:00");

//     // 天气
//     clock_screen_t.weather_panel = lv_obj_create(clock_screen_t.clock_cond);
//     lv_obj_clear_flag(clock_screen_t.weather_panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
//     lv_obj_set_style_bg_color(clock_screen_t.weather_panel,lv_color_make(0,0,150),LV_STATE_DEFAULT);
//     lv_obj_set_height(clock_screen_t.weather_panel,120);
//     lv_obj_set_width(clock_screen_t.weather_panel,300);
//     lv_obj_align(clock_screen_t.weather_panel,LV_ALIGN_TOP_RIGHT,20,110);


//     clock_screen_t.weather_paner_below = lv_obj_create(clock_screen_t.clock_cond);
//     lv_obj_clear_flag(clock_screen_t.weather_paner_below, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
//     lv_obj_set_style_bg_color(clock_screen_t.weather_paner_below,lv_color_make(0,150,150),LV_STATE_DEFAULT);
//     lv_obj_set_height(clock_screen_t.weather_paner_below,180);
//     lv_obj_set_width(clock_screen_t.weather_paner_below,300);
//     lv_obj_align(clock_screen_t.weather_paner_below,LV_ALIGN_TOP_RIGHT,20,230);
// }

// void lv_clock_set_time(const char* time_str)
// {
//     lv_label_set_text(clock_screen_t.clock_label, time_str);
// }


// void clockscr_timer_cb(lv_timer_t * timer)
// {
//     uint32_t * clock_second = timer->user_data;
//     // LV_LOG_USER("clockscr_timer_cb called with clock_second: %d\n", *clock_second);
//     if((*clock_second)%2==0)
//     {
//         lv_clock_set_time("18 00");
//     }
//     else
//     {
//         lv_clock_set_time("18:00");
//     }
//     (*clock_second)++;
//     if(*clock_second==60)
//     {
//         *clock_second=0;
//     }
// }

// void clockscr_timer_task_init(void)
// {
//     static uint32_t timer_delay = 1000; // 1s
//     static uint32_t clock_second = 0;
//     lv_timer_t *imgscr_timer = lv_timer_create(clockscr_timer_cb,timer_delay,&clock_second);
// }


