
#include "camera2D.h" 

// Convert screen coordinates to world coordinates
void screen_to_world(vec2 screen_coords, vec2* world_coords, Camera2D* cam) {
 
  vec2 translated_screen_coords = add_vec2(screen_coords, neg_vec2(cam->offset));
  vec2 scaled_coords = scale_vec2(translated_screen_coords, 1/cam->zoom); 
  vec2 translated_coords = add_vec2(scaled_coords, cam->target);

  (*world_coords).x = translated_coords.x;
  (*world_coords).y = translated_coords.y;  
}

// Convert world coordinates to screen coordinates
void world_to_screen(vec2 world_coords, vec2* screen_coords, Camera2D* cam) { 

  vec2 translated_world_coords = add_vec2(world_coords, neg_vec2(cam->target));
  vec2 scaled_coords = scale_vec2(translated_world_coords, cam->zoom); 
  vec2 translated_coords = add_vec2(scaled_coords, cam->offset);

  (*screen_coords).x = translated_coords.x;
  (*screen_coords).y = translated_coords.y;  
}
