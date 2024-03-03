#ifndef CONTEXT_H
#define CONTEXT_H

#define CVECTOR_LOGARITHMIC_GROWTH
#include "DSA/cvector.h"

#include "../ext/glad/glad.h"
#include "../ext/glfw/zig-out/include/GLFW/glfw3.h"

#include "../ext/nanovg/nanovg.h"
#define NANOVG_GLES3_IMPLEMENTATION

#include "types.h" 
#include "utils.h"
#include "Camera2D/camera2D.h"
#include "Renderer/renderer.h"

typedef struct EngineContext {
  // EngineContext Lifetime
  bool start_context;
  bool end_context;
 
  // glfw 
  GLFWwindow* window;
 
  // NanoVG
  NVGcontext* vg;
  
  // Camera 2D
  Camera2D cam;
 
  // Steiner Tree
  f32 anim_timer; 
  f32 outer_radius;
  f32 inner_radius;
  f32 line_thickness; 
  cvector(t_node) node_terminals;
  cvector(t_vertex) all_vertex;
  cvector(t_vertex) MST;
  
  // update related
  f32 curr_time;
  f32 prev_time;
  f32 delta_time;
  
} EngineContext;

#endif

