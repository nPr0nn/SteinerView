
#ifndef RENDER_H
#define RENDER_H

#include "../types.h"
#include "../Camera2D/camera2D.h"

#include "../../ext/nanovg/nanovg.h"
#define NANOVG_GLES3_IMPLEMENTATION

#include "../../ext/rayeasing.h"

void draw_circle(vec2 pos, f32 radius, t_color color, NVGcontext* vg, Camera2D* camera);
void draw_line(vec2 A, vec2 B, f32 thickness, t_color color, NVGcontext* vg, Camera2D* cam);
void draw_grid(NVGcontext* vg, Camera2D* cam);
void draw_node(t_node* node, f32 inner_radius, f32 outer_radius, f32 dt, NVGcontext* vg, Camera2D* cam);

#endif
 
