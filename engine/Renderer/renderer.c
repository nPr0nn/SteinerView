
#include "renderer.h"
#include <stdio.h>

bool is_between(f32 v, f32 lower_bound, f32 upper_bound){
  if( v > lower_bound && v < upper_bound) return true;
  return false;
}

bool is_visible(vec2 pos, Camera2D* cam){
  i32 w = cam->screen_width; i32 h = cam->screen_height;
  bool cond_y = is_between(pos.y, cam->target.y - h/cam->zoom, cam->target.y + h/cam->zoom);
  bool cond_x = is_between(pos.x, cam->target.x - w/cam->zoom, cam->target.x + w/cam->zoom);
  return (cond_x && cond_y);
}

void draw_circle(vec2 pos, f32 radius, t_color color, NVGcontext* vg, Camera2D* cam){ 
  // pos.y = -1 * pos.y;
  vec2 screen_pos;
  world_to_screen(pos, &screen_pos, cam);

  if(is_visible(pos, cam)){
    nvgBeginPath(vg);
    nvgCircle(vg, screen_pos.x, screen_pos.y, radius*cam->zoom);
    nvgFillColor(vg, nvgRGBA(color.r, color.g, color.b, color.a)); 
    nvgFill(vg);  
  }
}

void draw_node(t_node* node, f32 inner_radius, f32 outer_radius, f32 dt, NVGcontext* vg, Camera2D* cam){ 
  if(node->ready == false) node->anim_counter += dt;
  if(node->anim_counter > node->duration) { 
    node->anim_counter = node->duration; 
    node->ready = true;
  }
  
  f32 current_inner_radius = EaseCubicIn(node->anim_counter, 0, inner_radius, node->duration);  
  f32 current_outer_radius = EaseCubicIn(node->anim_counter, 0, outer_radius, node->duration);  
  
  draw_circle(node->pos, current_outer_radius, (t_color) {0, 0, 0, 255}, vg, cam);  
  draw_circle(node->pos, current_inner_radius, (t_color) {255, 0, 0, 255}, vg, cam);  
}

void draw_line(vec2 A, vec2 B, float thickness, t_color color, NVGcontext* vg, Camera2D* cam){ 
  // A.y = -1 * A.y; B.y = -1 * B.y;
  vec2 screen_A; 
  vec2 screen_B;  
  world_to_screen(A, &screen_A, cam);
  world_to_screen(B, &screen_B, cam);

  if(is_visible(A, cam) || is_visible(B, cam)){ 
    nvgBeginPath(vg);
    nvgMoveTo(vg, screen_A.x, screen_A.y);
    nvgLineTo(vg, screen_B.x, screen_B.y); 
    nvgStrokeColor(vg, nvgRGBA(color.r, color.g, color.b, color.a));
    nvgStrokeWidth(vg, thickness * cam->zoom);
    nvgStroke(vg);
  }
} 

void draw_grid(NVGcontext* vg, Camera2D* cam){ 
  i32 w = cam->screen_width; i32 h = cam->screen_height;
  vec2 world_pos = (vec2){0, 0}; 
  vec2 screen_pos;
  world_to_screen(world_pos, &screen_pos, cam);

  // y-axis
  nvgBeginPath(vg);
  nvgMoveTo(vg, screen_pos.x, 0);
  nvgLineTo(vg, screen_pos.x, h); 
  nvgStrokeColor(vg, nvgRGBA(0, 0, 0, 255));
  nvgStrokeWidth(vg, 1.5);
  nvgStroke(vg); 

  // x-axis
  nvgBeginPath(vg);
  nvgMoveTo(vg, w, screen_pos.y);
  nvgLineTo(vg, 0, screen_pos.y); 
  nvgStrokeColor(vg, nvgRGBA(0, 0, 0, 255));
  nvgStrokeWidth(vg, 1.5);
  nvgStroke(vg);

  i32 step = 100;
  i32 N    = 800;

  for(int i = -N; i < N; i++){  
    world_pos  = (vec2){0, i*step}; 
    world_to_screen(world_pos, &screen_pos, cam);

    float color_tone = 0;  
    float thickness = 0.80;  
    if(i % 2) { thickness = 0.50; color_tone = 30; }
 
    if( is_between(world_pos.y, cam->target.y - h/cam->zoom, cam->target.y + h/cam->zoom) ){ 
      nvgBeginPath(vg);
      nvgMoveTo(vg, w, screen_pos.y);
      nvgLineTo(vg, 0, screen_pos.y); 
      nvgStrokeColor(vg, nvgRGBA(color_tone, color_tone, color_tone, 255));
      nvgStrokeWidth(vg, thickness);
      nvgStroke(vg);  
    }
 
    world_pos  = (vec2){i*step, 0};
    world_to_screen(world_pos, &screen_pos, cam);
    
    if( is_between(world_pos.x, cam->target.x - w/cam->zoom, cam->target.x + w/cam->zoom) ){ 
      nvgBeginPath(vg);
      nvgMoveTo(vg, screen_pos.x, 0);
      nvgLineTo(vg, screen_pos.x, h); 
      nvgStrokeColor(vg, nvgRGBA(color_tone, color_tone, color_tone, 255));
      nvgStrokeWidth(vg, thickness);
      nvgStroke(vg);
    }
  }

}
