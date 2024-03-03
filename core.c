
#include "core.h"
#include "engine/DSA/cvector.h"
#include "engine/Renderer/renderer.h"
#include "engine/utils.h"
#include "ext/nanovg/nanovg_gl.h"
#include "ext/nanovg/nanovg_gl_utils.h"
#include <stdio.h>

void engine_start(EngineContext* engine_context)
{
  // glfw: initialize and configure
  // LOG("GLFW Init", stdout);  
  glfwInit();
  glfwWindowHint(GLFW_SAMPLES, 4); 
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0); 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
  // glfwWindowHint(GLFW_RESIZABLE, 1);
  // glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
  
  // glfw: window creation
  f32 screen_width  = 1920 * 0.5f;
  f32 screen_height = 1080 * 0.5f;
  GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "Steiner View", NULL, NULL);
 
  if(window == NULL){
    glfwTerminate();
    ERROR_EXIT("ERROR: Failed to create GLFW window\n");
  }
  
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetCursorPosCallback(window, cursor_position_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  
  // glad: load all OpenGL function pointers
  // gladLoadGL(glfwGetProcAddress);  
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    ERROR_EXIT("ERROR: Failed to initialize GLAD");
  }    

  // Global
  engine_context->window = window;
  engine_context->vg = nvgCreateGLES3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);

  // Delta Time
  engine_context->curr_time  = 0;
  engine_context->delta_time = 0;
  engine_context->prev_time  = 0;
  
  // Camera
  engine_context->cam.zoom = 1.0f;
  engine_context->cam.is_zooming  = false;
  engine_context->cam.is_dragging = false;    
  engine_context->cam.offset = (vec2){ screen_width * 0.5f, screen_height * 0.5f };
  engine_context->cam.target = (vec2){ 0.0f, 0.0f }; 
  engine_context->cam.zoom = 0.75f;
  engine_context->cam.zoom_increment = 0.125f;
  engine_context->cam.screen_width   = screen_width;
  engine_context->cam.screen_height  = screen_height;
  
  // Steiner Tree  
  engine_context->anim_timer     = 0.3;
  engine_context->inner_radius   = 18;
  engine_context->outer_radius   = 24; 
  engine_context->line_thickness = 8; 

  glfwSetWindowUserPointer(window, engine_context); 
}

// engine: core loop with update and render
void core_loop(void* args)
{
  EngineContext* ctx = (EngineContext*) args;
 
  // delta time
  ctx->curr_time  = glfwGetTime();
  ctx->delta_time = ctx->curr_time - ctx->prev_time;
  ctx->prev_time  = ctx->curr_time;
  f32 dt          = ctx->delta_time;

  FLOG(stdout, "%.9f", dt);
   
  // inputs
  process_input(ctx->window);

  // background 
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
  glClear(GL_COLOR_BUFFER_BIT);
    
  f32 zoom = ctx->cam.zoom;
  
  nvgBeginFrame(ctx->vg, ctx->cam.screen_width, ctx->cam.screen_height, 1);  
  draw_grid(ctx->vg, &ctx->cam);

  for(int i = 1; i < cvector_size(ctx->node_terminals); i++){
    t_color black = (t_color){0,0,0,255};

    t_node* prev_node = &ctx->node_terminals[i-1]; 
    t_node* curr_node = &ctx->node_terminals[i];

    vec2 t;  
    t.x = EaseCubicIn(curr_node->anim_counter, prev_node->pos.x, curr_node->pos.x - prev_node->pos.x, curr_node->duration);
    t.y = EaseCubicIn(curr_node->anim_counter, prev_node->pos.y, curr_node->pos.y - prev_node->pos.y, curr_node->duration); 
    draw_line(t, ctx->node_terminals[i-1].pos, ctx->line_thickness, black, ctx->vg, &ctx->cam); 
  }  
    
  for(int i = 0; i < cvector_size(ctx->node_terminals); i++){ 
    t_node* curr_node = &ctx->node_terminals[i];
    draw_node(curr_node, ctx->inner_radius, ctx->outer_radius, dt, ctx->vg, &ctx->cam);    
  } 
 
  nvgEndFrame(ctx->vg); 
  
  glfwSwapBuffers(ctx->window);   
  glfwPollEvents(); 
}

void engine_terminate(EngineContext* engine_context){
  glfwTerminate();
  cvector_free(engine_context->node_terminals);
}

