//#include <rtthread.h>
#include <lvgl.h>
#include <lv_conf.h>


#define LV_EXP_DESKTOP_TEST1 0
#define LV_EXP_DESKTOP_TEST2 0

#if LV_EXP_DESKTOP_TEST2==1
void lv_desktop(void)
{
	    // 创建桌面
    lv_obj_t *desktop = lv_obj_create(lv_scr_act());
	
	    // 删除对象所有样式
    lv_obj_remove_style_all(desktop);
    lv_obj_set_size(desktop, LV_HOR_RES, LV_VER_RES);       // 设置到屏幕大小
	
#if 0
    // 设置图片背景
    // 直接获取原始图片
    lv_obj_t *bg_img = lv_img_create(desktop);
	// 显示 jpg 刷屏比较慢 不能接受
//		lv_img_set_src(bg_img,"S:imgs/test.jpg");
	// 显示 sjpg  稍微快一些
		lv_img_set_src(bg_img,"S:imgs/testbg.sjpg");
    lv_obj_center(bg_img);
#endif

	
#if 0
	// 设置桌面背景,这种方法最快
		LV_IMG_DECLARE(bg_lvgl);
		lv_obj_t *bg_img = lv_img_create(desktop);
		lv_img_set_src(bg_img,&bg_lvgl);
    lv_obj_center(bg_img);
#endif
}
#endif

#if LV_EXP_DESKTOP_TEST1==1
void lv_desktop(void)
{
    /* menu item style */
    static lv_style_t page_round_out;
    lv_style_init(&page_round_out);
    lv_style_set_bg_opa(&page_round_out,LV_OPA_80); // 设置色彩透明度
    lv_style_set_radius(&page_round_out,100);       // 设置圆角
    lv_style_set_bg_color(&page_round_out,lv_color_hex(0xFFFFFF)); //设置颜色

    static lv_style_t page_round_in;
    lv_style_init(&page_round_in);
    lv_style_set_bg_opa(&page_round_in, LV_OPA_30); // 设置色彩透明度
    lv_style_set_radius(&page_round_in, 100); // 设置圆角
    lv_style_set_bg_color(&page_round_in, lv_color_hex(0xFFFFFF)); //设置颜色


    /* desktop style */
    static lv_style_t style_tabview_desktop;
    lv_style_init(&style_tabview_desktop);
    lv_style_set_bg_opa(&style_tabview_desktop, LV_OPA_0); // 设置色彩透明度


    // 设置当前界面背景色
    lv_obj_t * main_container = lv_obj_create(lv_scr_act());
    if (main_container == NULL)
	{
		// printf("[%s:%d] create main_container failed\n", __FUNCTION__, __LINE__);
		return;
	}
 
    lv_obj_set_style_pad_all(main_container, 0, 0);
    lv_obj_set_style_border_width(main_container, 0, 0);//边框宽
    lv_obj_set_style_radius(main_container, 0, 0);//圆角大小
    lv_obj_set_size(main_container, LV_PCT(100), LV_PCT(100)); // 设置尺寸
    lv_obj_set_style_bg_opa(main_container, LV_OPA_100, 0); // 设置背景不透明度

    
    //lv_obj_set_style_bg_color(main_container, lv_color_hex(0x355edc), 0); // 设置背景颜色  浅蓝色
    lv_obj_set_style_bg_color(main_container, lv_color_hex(0x333333), 0); // 设置背景颜色
    
    lv_obj_center(main_container);


    lv_obj_t *tabview_desktop = lv_tabview_create(main_container, LV_DIR_TOP,50);
    lv_obj_add_style(tabview_desktop, &style_tabview_desktop,LV_STATE_DEFAULT);
    // lv_tabview_set_btns_pos(tabview_desktop, LV_TABVIEW_TAB_POS_NONE);
    lv_obj_t *tab_left  = lv_tabview_add_tab(tabview_desktop, "left_desktop");
    lv_obj_t *tab_main  = lv_tabview_add_tab(tabview_desktop, "main_desktop");
    lv_obj_t *tab_right = lv_tabview_add_tab(tabview_desktop, "right_desktop");
    // lv_tabview_set_tab_act(tabview_desktop, 1, LV_ANIM_ON);
    lv_tabview_set_act(tabview_desktop, 1, LV_ANIM_ON);

      /* 左菜单指示 */
    // lv_obj_t * left_round1 = lv_cont_create(tab_left, NULL);         // 中间
    lv_obj_t * left_round1 = lv_obj_create(tab_left);
    lv_obj_add_style(left_round1,  &page_round_out,LV_STATE_DEFAULT);
    lv_obj_set_size(left_round1, 8, 8);
    lv_obj_align(left_round1, LV_ALIGN_CENTER, 0, 50);

    // lv_obj_t * left_round2 = lv_cont_create(tab_left, left_round1);  // 右边
    lv_obj_t * left_round2 = lv_obj_create(tab_left);
    lv_obj_add_style(left_round2, &page_round_out,LV_STATE_DEFAULT);
    lv_obj_set_size(left_round2, 8, 8);
    lv_obj_align(left_round2, LV_ALIGN_CENTER, 20, 50);

    // lv_obj_t * left_round3 = lv_cont_create(tab_left, left_round1);  // 左边
    lv_obj_t * left_round3 = lv_obj_create(tab_left);
    lv_obj_add_style(left_round3,&page_round_in,LV_STATE_DEFAULT);
    lv_obj_set_size(left_round3, 8, 8);
    lv_obj_align(left_round3, LV_ALIGN_CENTER, -20, 50);

    /* 主菜单指示 */
    // lv_obj_t * main_round1 = lv_cont_create(tab_main, NULL);         // 中间
    lv_obj_t * main_round1 = lv_obj_create(tab_main);
    lv_obj_add_style(main_round1, &page_round_in,LV_STATE_DEFAULT);
    lv_obj_set_size(main_round1, 8, 8);
    lv_obj_align(main_round1, LV_ALIGN_CENTER, 0, 50);

    // lv_obj_t * main_round2 = lv_cont_create(tab_main, main_round1);  // 右边
    lv_obj_t * main_round2 = lv_obj_create(tab_main);
    lv_obj_add_style(main_round2, &page_round_out,LV_STATE_DEFAULT);
    lv_obj_set_size(main_round2, 8, 8);
    lv_obj_align(main_round2,  LV_ALIGN_CENTER, 20, 50);

    // lv_obj_t * main_round3 = lv_cont_create(tab_main, main_round1);  // 左边
    lv_obj_t * main_round3 = lv_obj_create(tab_main);
    lv_obj_add_style(main_round3, &page_round_out,LV_STATE_DEFAULT);
    lv_obj_set_size(main_round3, 8, 8);
    lv_obj_align(main_round3, LV_ALIGN_CENTER, -20, 50);


    /* 右菜单指示 */
    // lv_obj_t * right_round1 = lv_cont_create(tab_right, NULL);         // 中间
    lv_obj_t * right_round1 = lv_obj_create(tab_right);
    lv_obj_add_style(right_round1, &page_round_out,LV_STATE_DEFAULT);
    lv_obj_set_size(right_round1, 8, 8);
    lv_obj_align(right_round1, LV_ALIGN_CENTER, 0, 50);

    // lv_obj_t * right_round2 = lv_cont_create(tab_right, right_round1);  // 右边
    lv_obj_t * right_round2 = lv_obj_create(tab_right);
    lv_obj_add_style(right_round2, &page_round_in,LV_STATE_DEFAULT);
    lv_obj_set_size(right_round2, 8, 8);
    lv_obj_align(right_round2,  LV_ALIGN_CENTER, 20, 50);

    // lv_obj_t * right_round3 = lv_cont_create(tab_right, right_round1);  // 左边
    lv_obj_t * right_round3 = lv_obj_create(tab_right);
    lv_obj_add_style(right_round3, &page_round_out,LV_STATE_DEFAULT);
    lv_obj_set_size(right_round3, 8, 8);
    lv_obj_align(right_round3, LV_ALIGN_CENTER, -20, 50);


    lv_obj_t * label = lv_label_create(tab_left);
    lv_label_set_text(label, "first tab\n\n");
    lv_obj_set_style_text_color(label,lv_color_make(255,255,255),LV_STATE_DEFAULT);

    label = lv_label_create(tab_main);
    lv_label_set_text(label, "Second tab");
    lv_obj_set_style_text_color(label,lv_color_make(255,255,255),LV_STATE_DEFAULT);

    label = lv_label_create(tab_right);
    lv_label_set_text(label, "Third tab");
    lv_obj_set_style_text_color(label,lv_color_make(255,255,255),LV_STATE_DEFAULT);

    lv_obj_scroll_to_view_recursive(label, LV_ANIM_ON);

}
#endif