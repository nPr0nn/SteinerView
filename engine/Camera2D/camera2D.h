#ifndef CAM_H
#define CAM_H

#include "../types.h"

typedef struct Camera2D {
  
  // Mouse parameters
  double last_mouse_x, last_mouse_y;
  bool is_dragging;
  bool is_zooming;
 
  // Camera 2D
  vec2 target;
  vec2 offset;
  float zoom;
  float zoom_increment; 
  float rotation;

  // Canvas 
  int screen_width;
  int screen_height;
  
} Camera2D;

void screen_to_world(vec2 screen_coords, vec2* world_coords,  Camera2D *camera);
void world_to_screen(vec2 world_coords,  vec2* screen_coords, Camera2D *camera);

#endif
 
