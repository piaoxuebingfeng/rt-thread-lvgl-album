#include "albumpageui.h"


#define STM32F469_WORKSPACE  0
#define VSCODE_SIMULATOR     1


///////////////////// VARIABLES ////////////////////
static lv_obj_t * ui_albumpage;
static lv_obj_t * ui_Image1;
static lv_obj_t * ui_Image2;
static lv_obj_t * ui_Image3;
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

///////////////////// ANIMATIONS ////////////////////

// ui_EloAnimation0
// FUNCTION HEADER
static void albumshowleft_Animation(lv_obj_t * TargetObject, int delay);


static int32_t _ui_anim_callback_get_opacity(lv_anim_t * a)
{
    return lv_obj_get_style_opa((lv_obj_t *)a->user_data, 0);
}

static void _ui_anim_callback_set_opacity(lv_anim_t * a, int32_t v)
{
    lv_obj_set_style_opa((lv_obj_t *)a->user_data, v, 0);
}

static int32_t _ui_anim_callback_get_x(lv_anim_t * a)
{
    return lv_obj_get_x_aligned((lv_obj_t *)a->user_data);
}

static void _ui_anim_callback_set_x(lv_anim_t * a, int32_t v)
{
    lv_obj_set_x((lv_obj_t *)a->user_data, v);
}


// FUNCTION
void albumshowleft_Animation(lv_obj_t * TargetObject, int delay)
{

    //
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 2000);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_0, 255, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_in);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_opacity);
    lv_anim_start(&PropertyAnimation_0);

}

// ui_EloAnimation0
// FUNCTION HEADER
void imgxmoveanmi_Animation(lv_obj_t * TargetObject, int delay);

// FUNCTION
void imgxmoveanmi_Animation(lv_obj_t * TargetObject, int delay)
{

    //
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 2000);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_0, 0, 800);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_in_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_x);
    lv_anim_start(&PropertyAnimation_0);

}

// ui_EloAnimation0
// FUNCTION HEADER
void img2xmoveanmi_Animation(lv_obj_t * TargetObject, int delay);

// FUNCTION
void img2xmoveanmi_Animation(lv_obj_t * TargetObject, int delay)
{

    //
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 2000);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_0, 0, 800);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_in_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_x);
    lv_anim_start(&PropertyAnimation_0);

}



//void imganmitoleft()
//{
//    lv_anim_t anim_left;
//    lv_anim_init(&anim_left);
//    lv_anim_t anim_left2;
//    lv_anim_init(&anim_left2);

//    uint16_t right_img_c = imgswitch_c +1;
//    if(right_img_c>=5)
//    {
//        right_img_c =0;
//    }
//    LV_LOG_USER("imgsname[%d]=%s\n",imgswitch_c,imgsname[imgswitch_c]);
//    LV_LOG_USER("imgsname[%d]=%s\n",right_img_c,imgsname[right_img_c]);

//    lv_obj_set_x(ui_Image1, 0);
//    lv_obj_set_x(ui_Image2, -800);
//    lv_obj_set_x(ui_Image3, 800);
//    lv_img_set_src(ui_Image1, imgsname[imgswitch_c]);
//    lv_img_set_src(ui_Image3, imgsname[right_img_c]);
//    imgswitch_c++;
//    if(imgswitch_c==5)
//    {
//        imgswitch_c=0;
//    }

//    lv_anim_set_time(&anim_left, 2000);
//    lv_anim_set_user_data(&anim_left, ui_Image1);
//    lv_anim_set_custom_exec_cb(&anim_left, _ui_anim_callback_set_x);
//    lv_anim_set_values(&anim_left, 0, -800);
//    lv_anim_set_path_cb(&anim_left, lv_anim_path_ease_in_out);
//    lv_anim_set_delay(&anim_left,  0);
//    lv_anim_set_early_apply(&anim_left, false);
//    lv_anim_set_get_value_cb(&anim_left, &_ui_anim_callback_get_x);
//    lv_anim_start(&anim_left);

//    lv_anim_set_time(&anim_left2, 2000);
//    lv_anim_set_user_data(&anim_left2, ui_Image3);
//    lv_anim_set_custom_exec_cb(&anim_left2, _ui_anim_callback_set_x);
//    lv_anim_set_values(&anim_left2, 0, -800);
//    lv_anim_set_path_cb(&anim_left2, lv_anim_path_ease_in_out);
//    lv_anim_set_delay(&anim_left2,  0);
//    lv_anim_set_early_apply(&anim_left2, false);
//    lv_anim_set_get_value_cb(&anim_left2, &_ui_anim_callback_get_x);
//    lv_anim_start(&anim_left2);


//}


//void imganmitoright()
//{
//    lv_anim_t anim_right;
//    lv_anim_init(&anim_right);
//    lv_anim_t anim_right2;
//    lv_anim_init(&anim_right2);
//    uint16_t left_img_c =0;

//    if(imgswitch_c==0)
//    {
//        left_img_c = 4;
//    }
//    else if(imgswitch_c>0)
//    {
//        left_img_c = imgswitch_c -1;
//    }
//    if(left_img_c>=5)
//    {
//        left_img_c =0;
//    }

//    LV_LOG_USER("imgsname[%d]=%s\n",imgswitch_c,imgsname[imgswitch_c]);
//    LV_LOG_USER("imgsname[%d]=%s\n",left_img_c,imgsname[left_img_c]);

//    lv_obj_set_x(ui_Image1, 0);
//    lv_obj_set_x(ui_Image2, -800);
//    lv_obj_set_x(ui_Image3, 800);
//    lv_img_set_src(ui_Image1, imgsname[imgswitch_c]);
//    lv_img_set_src(ui_Image2, imgsname[left_img_c]);
//    if(imgswitch_c==0)
//    {
//        imgswitch_c =4;
//    }
//    else if(imgswitch_c >0)
//    {
//        imgswitch_c--;
//    }

//    lv_anim_set_time(&anim_right, 2000);
//    lv_anim_set_user_data(&anim_right, ui_Image1);
//    lv_anim_set_custom_exec_cb(&anim_right, _ui_anim_callback_set_x);
//    lv_anim_set_values(&anim_right, 0, 800);
//    lv_anim_set_path_cb(&anim_right, lv_anim_path_ease_in_out);
//    lv_anim_set_delay(&anim_right,  0);
//    lv_anim_set_early_apply(&anim_right, false);
//    lv_anim_set_get_value_cb(&anim_right, &_ui_anim_callback_get_x);
//    lv_anim_start(&anim_right);

//    lv_anim_set_time(&anim_right2, 2000);
//    lv_anim_set_user_data(&anim_right2, ui_Image2);
//    lv_anim_set_custom_exec_cb(&anim_right2, _ui_anim_callback_set_x);
//    lv_anim_set_values(&anim_right2, 0, 800);
//    lv_anim_set_path_cb(&anim_right2, lv_anim_path_ease_in_out);
//    lv_anim_set_delay(&anim_right2,  0);
//    lv_anim_set_early_apply(&anim_right2, false);
//    lv_anim_set_get_value_cb(&anim_right2, &_ui_anim_callback_get_x);
//    lv_anim_start(&anim_right2);


//}



void imganmitoleft()
{
    lv_anim_t anim_left;
    lv_anim_init(&anim_left);
    lv_anim_t anim_left2;
    lv_anim_init(&anim_left2);

    uint16_t right_img_c = imgswitch_c +1;
    if(right_img_c>=3)
    {
        right_img_c =0;
    }
//    LV_LOG_USER("imgsname[%d]=%s\n",imgswitch_c,imgsname[imgswitch_c]);
//    LV_LOG_USER("imgsname[%d]=%s\n",right_img_c,imgsname[right_img_c]);

    lv_obj_set_x(ui_Image1, 0);
    lv_obj_set_x(ui_Image2, -800);
    lv_obj_set_x(ui_Image3, 800);
    lv_img_set_src(ui_Image1, norflashimgname[imgswitch_c]);
    lv_img_set_src(ui_Image3, norflashimgname[right_img_c]);
    imgswitch_c++;
    if(imgswitch_c==3)
    {
        imgswitch_c=0;
    }

    lv_anim_set_time(&anim_left, 500);
    lv_anim_set_user_data(&anim_left, ui_Image1);
    lv_anim_set_custom_exec_cb(&anim_left, _ui_anim_callback_set_x);
    lv_anim_set_values(&anim_left, 0, -800);
    lv_anim_set_path_cb(&anim_left, lv_anim_path_ease_in_out);
    lv_anim_set_delay(&anim_left,  0);
    lv_anim_set_early_apply(&anim_left, false);
    lv_anim_set_get_value_cb(&anim_left, &_ui_anim_callback_get_x);
    lv_anim_start(&anim_left);

    lv_anim_set_time(&anim_left2, 500);
    lv_anim_set_user_data(&anim_left2, ui_Image3);
    lv_anim_set_custom_exec_cb(&anim_left2, _ui_anim_callback_set_x);
    lv_anim_set_values(&anim_left2, 0, -800);
    lv_anim_set_path_cb(&anim_left2, lv_anim_path_ease_in_out);
    lv_anim_set_delay(&anim_left2,  0);
    lv_anim_set_early_apply(&anim_left2, false);
    lv_anim_set_get_value_cb(&anim_left2, &_ui_anim_callback_get_x);
    lv_anim_start(&anim_left2);


}


void imganmitoright()
{
    lv_anim_t anim_right;
    lv_anim_init(&anim_right);
    lv_anim_t anim_right2;
    lv_anim_init(&anim_right2);
    uint16_t left_img_c =0;

    if(imgswitch_c==0)
    {
        left_img_c = 2;
    }
    else if(imgswitch_c>0)
    {
        left_img_c = imgswitch_c -1;
    }
    if(left_img_c>=3)
    {
        left_img_c =0;
    }


    lv_obj_set_x(ui_Image1, 0);
    lv_obj_set_x(ui_Image2, -800);
    lv_obj_set_x(ui_Image3, 800);
    lv_img_set_src(ui_Image1, norflashimgname[imgswitch_c]);
    lv_img_set_src(ui_Image2, norflashimgname[left_img_c]);
    if(imgswitch_c==0)
    {
        imgswitch_c =2;
    }
    else if(imgswitch_c >0)
    {
        imgswitch_c--;
    }

    lv_anim_set_time(&anim_right, 500);
    lv_anim_set_user_data(&anim_right, ui_Image1);
    lv_anim_set_custom_exec_cb(&anim_right, _ui_anim_callback_set_x);
    lv_anim_set_values(&anim_right, 0, 800);
    lv_anim_set_path_cb(&anim_right, lv_anim_path_ease_in_out);
    lv_anim_set_delay(&anim_right,  0);
    lv_anim_set_early_apply(&anim_right, false);
    lv_anim_set_get_value_cb(&anim_right, &_ui_anim_callback_get_x);
    lv_anim_start(&anim_right);

    lv_anim_set_time(&anim_right2, 500);
    lv_anim_set_user_data(&anim_right2, ui_Image2);
    lv_anim_set_custom_exec_cb(&anim_right2, _ui_anim_callback_set_x);
    lv_anim_set_values(&anim_right2, 0, 800);
    lv_anim_set_path_cb(&anim_right2, lv_anim_path_ease_in_out);
    lv_anim_set_delay(&anim_right2,  0);
    lv_anim_set_early_apply(&anim_right2, false);
    lv_anim_set_get_value_cb(&anim_right2, &_ui_anim_callback_get_x);
    lv_anim_start(&anim_right2);

}



///////////////////// FUNCTIONS ////////////////////
static void ui_event_btnleft(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        // albumshowleft_Animation(ui_Image1, 500);
        
			imganmitoleft();
    }
}
static void ui_event_btnright(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        // imgxmoveanmi_Animation(ui_Image1, 0);
        // img2xmoveanmi_Animation(ui_Image2, 0);
        
			imganmitoright();
    }
}


static void ui_event_btnswitch(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        // LV_LOG_USER("switch btn clicked\n");

        // 使用动画切换图片
        // todo

        // 直接切换图片
//        LV_LOG_USER("ui_Image1 x :%d\n",lv_obj_get_x(ui_Image1));
			
//        lv_obj_set_x(ui_Image1, 0);
//        lv_obj_set_x(ui_Image2, -800);
//        lv_obj_set_x(ui_Image3, 800);
			
        lv_img_set_src(ui_Image1, imgsname[imgswitch_c]);
//					lv_img_set_src(ui_Image1, norflashimgname[imgswitch_c]);

			
//        LV_LOG_USER("ui_Image1 x :%d\n",lv_obj_get_x(ui_Image1));
//        LV_LOG_USER("imgsname[%d]=%s\n",imgswitch_c,imgsname[imgswitch_c]);
        imgswitch_c++;
        if(imgswitch_c== 3 )
        {
            imgswitch_c =0 ;
        }
        // imgxmoveanmi_Animation(ui_Image1, 0);
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
//#if STM32F469_WORKSPACE==1
//    lv_img_set_src(ui_Image1, &ui_img_testbg_png);
//#elif VSCODE_SIMULATOR==1
//    lv_img_set_src(ui_Image1, "S:imgs/holidaynight800.jpg");
//#endif
		lv_obj_set_style_border_width(ui_Image1,0,LV_STATE_DEFAULT);

		lv_img_set_src(ui_Image1, &bg_lvgl);
    lv_obj_set_width(ui_Image1, 800);
    lv_obj_set_height(ui_Image1, 480);

    lv_obj_set_x(ui_Image1, 0);
    lv_obj_set_y(ui_Image1, 0);

    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image2

    ui_Image2 = lv_img_create(ui_albumpage);
//#if STM32F469_WORKSPACE==1
//    lv_img_set_src(ui_Image2, &ui_img_bg_lvgl_png);
//#elif VSCODE_SIMULATOR==1
//    lv_img_set_src(ui_Image2, "S:imgs/bg_lvgl.jpg");
//#endif
 

    lv_obj_set_width(ui_Image2, 800);
    lv_obj_set_height(ui_Image2, 480);

    lv_obj_set_x(ui_Image2, -800);
    lv_obj_set_y(ui_Image2, 0);

    lv_obj_set_align(ui_Image2, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image3

    ui_Image3 = lv_img_create(ui_albumpage);
		
		
//#if STM32F469_WORKSPACE==1
//    lv_img_set_src(ui_Image3, &ui_img_seaandsky800_png);
//#elif VSCODE_SIMULATOR==1
//    lv_img_set_src(ui_Image3, "S:imgs/seaandsky800.jpg");
//#endif
    
    

    lv_obj_set_width(ui_Image3, 800);
    lv_obj_set_height(ui_Image3, 480);

    lv_obj_set_x(ui_Image3, 800);
    lv_obj_set_y(ui_Image3, 0);

    lv_obj_set_align(ui_Image3, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image3, LV_OBJ_FLAG_SCROLLABLE);

    // ui_bottompanel

//    ui_bottompanel = lv_obj_create(ui_albumpage);

//    lv_obj_set_width(ui_bottompanel, 800);
//    lv_obj_set_height(ui_bottompanel, 40);

//    lv_obj_set_x(ui_bottompanel, 0);
//    lv_obj_set_y(ui_bottompanel, 220);

//    lv_obj_set_align(ui_bottompanel, LV_ALIGN_CENTER);

//    lv_obj_clear_flag(ui_bottompanel, LV_OBJ_FLAG_SCROLLABLE);

//    lv_obj_set_style_radius(ui_bottompanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_color(ui_bottompanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_opa(ui_bottompanel, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_border_width(ui_bottompanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_btnleft

    ui_btnleft = lv_btn_create(ui_albumpage);

    lv_obj_set_width(ui_btnleft, 80);
    lv_obj_set_height(ui_btnleft,80);

//    lv_obj_set_x(ui_btnleft, -200);
//    lv_obj_set_y(ui_btnleft, 0);

//    lv_obj_set_align(ui_btnleft, LV_ALIGN_CENTER);
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

//    lv_obj_set_x(ui_btnright, 200);
//    lv_obj_set_y(ui_btnright, 0);

//    lv_obj_set_align(ui_btnright, LV_ALIGN_CENTER);
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

