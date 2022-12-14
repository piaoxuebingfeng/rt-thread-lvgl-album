#include "lv_sun_canvas.h"
#include "math.h"

static lv_obj_t * canvas ;
// 太阳位置
static lv_obj_t * sun_loc;
static lv_obj_t * sun_up_time_label;
static lv_obj_t * sun_down_time_label;


// 设置日出日落时间

void lv_sun_canvas_set_text(const char *sun_on_time_text,const char *sun_off_time_text)
{
//    // 设置日出日落时间
//    if(!canvas)
//        return;
//    if(!sun_on_time_text || !sun_off_time_text)
//        return;
//    lv_draw_label_dsc_t label_dsc;
//    lv_draw_label_dsc_init(&label_dsc);
//    label_dsc.color = lv_palette_main(LV_PALETTE_ORANGE);
//    // sun on time
//		
//    lv_canvas_draw_text(canvas,5, CANVAS_HEIGHT-45, 80, &label_dsc, sun_on_time_text);
//    lv_canvas_draw_text(canvas, CANVAS_WIDTH/2+60, CANVAS_HEIGHT-45, 80, &label_dsc, sun_off_time_text);
	
	if(sun_up_time_label && sun_up_time_label)
	{
		lv_label_set_text(sun_up_time_label,sun_on_time_text);
		lv_label_set_text(sun_down_time_label,sun_off_time_text);
	}
}


// 设置太阳位置
void lv_sun_set_position(int sun_ang)
{
    if(!canvas)
        return;
  // 绘制太阳
//  lv_draw_arc_dsc_t sun_arc_dsc;
//  lv_draw_arc_dsc_init(&sun_arc_dsc);
//  sun_arc_dsc.color = lv_palette_main(LV_PALETTE_RED);
//  sun_arc_dsc.width = 10;  // 宽度和圆形半径保持一致

  // 太阳的坐标需要根据太阳运行的轨迹计算得出
  
  // 定义圆心坐标
  lv_point_t circle_center;
  circle_center.x = CANVAS_WIDTH/2;
  circle_center.y = CANVAS_HEIGHT-50;

  // 圆弧半径
  int r = 80;

  // 定义太阳坐标
  lv_point_t sun_point;
//   sun_point.x = CANVAS_WIDTH/2 ;
//   sun_point.y = CANVAS_HEIGHT-50 ;

  // 定义太阳角度  用于测试

  if(sun_ang>=0 && sun_ang <=90)
  {
    sun_point.x = circle_center.x - r*cos(MATH_PI/180.0 *sun_ang)  - 10;
    sun_point.y = circle_center.y - r*sin(MATH_PI/180.0 *sun_ang)  - 10;
  }
  else if(sun_ang > 90 && sun_ang <=180)
  {
    sun_point.x = circle_center.x + r*cos(MATH_PI/180.0 *(180-sun_ang)) - 10;
    sun_point.y = circle_center.y - r*sin(MATH_PI/180.0 *(180-sun_ang)) - 10;
  }

//  lv_canvas_draw_arc(canvas,sun_point.x,sun_point.y,10,0,360,&sun_arc_dsc);
	
	lv_obj_set_x(sun_loc,sun_point.x);
	lv_obj_set_y(sun_loc,sun_point.y);

}


void lv_sun_canvas_create(lv_obj_t *parent)
{
  static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(CANVAS_WIDTH, CANVAS_HEIGHT)];

  canvas = lv_canvas_create(parent);
  lv_canvas_set_buffer(canvas, cbuf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_IMG_CF_TRUE_COLOR);
  lv_obj_center(canvas);
  lv_canvas_fill_bg(canvas, lv_palette_lighten(LV_PALETTE_NONE, 3), LV_OPA_COVER);

  lv_draw_line_dsc_t line_dsc;
  lv_draw_line_dsc_init(&line_dsc);
  line_dsc.color = lv_palette_main(LV_PALETTE_RED);
  line_dsc.width = 1;
  lv_point_t point_array[2]= {{0,CANVAS_HEIGHT-50},{CANVAS_WIDTH,CANVAS_HEIGHT-50}};
  lv_canvas_draw_line(canvas,point_array,2,&line_dsc);

  // draw arc
  lv_draw_arc_dsc_t arc_dsc;
  lv_draw_arc_dsc_init(&arc_dsc);
  arc_dsc.color = lv_palette_main(LV_PALETTE_ORANGE);
  arc_dsc.width = 1;

  // 按照角度 绘制半圆形线段
  for(int ang=180;ang<=360;ang+=4)
  {
    if(ang+2<=360)
    {
      lv_canvas_draw_arc(canvas,CANVAS_WIDTH/2,CANVAS_HEIGHT-50,ARC_R,ang,ang+2,&arc_dsc);
    }
    else
    {
      lv_canvas_draw_arc(canvas,CANVAS_WIDTH/2,CANVAS_HEIGHT-50,ARC_R,ang,360,&arc_dsc);
    }
  }
	
	// 日出日落时间 
	sun_up_time_label = lv_label_create(parent);
	lv_obj_set_width(sun_up_time_label,80);
	lv_obj_set_height(sun_up_time_label,20);
	lv_obj_align_to(sun_up_time_label,canvas,LV_ALIGN_OUT_BOTTOM_LEFT,5,-45);
	lv_obj_set_style_text_color(sun_up_time_label, lv_palette_main(LV_PALETTE_ORANGE), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_label_set_text(sun_up_time_label,"05:00");
	
	
	sun_down_time_label = lv_label_create(parent);
	lv_obj_set_width(sun_down_time_label,80);
	lv_obj_set_height(sun_down_time_label,20);
	lv_obj_align_to(sun_down_time_label,canvas,LV_ALIGN_OUT_BOTTOM_RIGHT,40,-45);
	lv_obj_set_style_text_color(sun_down_time_label, lv_palette_main(LV_PALETTE_ORANGE), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_label_set_text(sun_down_time_label,"20:00");
	
	
	sun_loc = lv_btn_create(canvas);
	lv_obj_set_width(sun_loc,20);
	lv_obj_set_height(sun_loc,20);
	lv_obj_set_style_radius(sun_loc,10,LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(sun_loc,lv_color_make(255,0,0),LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(sun_loc,0,LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(sun_loc,0,LV_STATE_DEFAULT);
//	lv_obj_center(sun_loc);

	
	//  lv_sun_set_position(45);
//  lv_sun_canvas_set_text("05:32","20:06");
}
