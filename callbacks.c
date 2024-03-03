
#include "core.h"
#include "engine/types.h"

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  EngineContext* ctx = glfwGetWindowUserPointer(window);
  Camera2D* cam = &ctx->cam; 
  glViewport(0, 0, width, height);
  cam->screen_width  = width;
  cam->screen_height = height;
}

// glfw: whenever the mouse scrool wheel move 
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  EngineContext* ctx = glfwGetWindowUserPointer(window);
  Camera2D* cam = &ctx->cam;
 
  double mouse_x; double mouse_y;
  glfwGetCursorPos(window, &mouse_x, &mouse_y); 

  vec2 mouse_pos = (vec2){mouse_x, mouse_y};
  screen_to_world(mouse_pos, &cam->target, cam);

  cam->offset = mouse_pos;

  cam->zoom += yoffset * cam->zoom_increment;
  if(cam->zoom < 2*cam->zoom_increment) cam->zoom = 2*cam->zoom_increment;
  cam->is_zooming = true;
}

// glfw: whenever the mouse move
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
  EngineContext* ctx = glfwGetWindowUserPointer(window);
  Camera2D* cam = &ctx->cam;
   
  if(cam->is_dragging){ 
    double dx = xpos - cam->last_mouse_x;
    double dy = ypos - cam->last_mouse_y;

    cam->target.x += dx * -1/cam->zoom;
    cam->target.y += dy * -1/cam->zoom;

    cam->last_mouse_x = xpos;
    cam->last_mouse_y = ypos;
  }
}

// glfw: whenever the mouse buttons are pressed
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {   
  EngineContext* ctx = glfwGetWindowUserPointer(window);
  Camera2D* cam = &ctx->cam;
  
  if(button == GLFW_MOUSE_BUTTON_LEFT) {    
    if (action == GLFW_PRESS) {
      cam->is_dragging = true;
      glfwGetCursorPos(window, &cam->last_mouse_x, &cam->last_mouse_y);
    } 
    else if (action == GLFW_RELEASE) {
      cam->is_dragging = false;
    }
  }

  // add node on click
  if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
    double mouse_x, mouse_y;
    glfwGetCursorPos(window, &mouse_x, &mouse_y);
 
    vec2 mouse_world_pos;
    screen_to_world((vec2){mouse_x, mouse_y}, &mouse_world_pos, cam);
    bool remove_pt = false;
   
    for(int i = 0; i < cvector_size(ctx->node_terminals); i++){ 
      if(dist_vec2(ctx->node_terminals[i].pos, mouse_world_pos) < ctx->outer_radius){
        remove_pt = true;
        cvector_erase(ctx->node_terminals, i);
        break;
      }
    } 
   
    t_node new_node;
    new_node.pos   = mouse_world_pos;
    new_node.ready = false;
    new_node.anim_counter = 0;
    new_node.duration = ctx->anim_timer;
    new_node.id    = cvector_size(ctx->node_terminals) + 1;
    if(!remove_pt) cvector_push_back(ctx->node_terminals, new_node);
  }
  
}

// glfw: query to check state of relevants keys
void process_input(GLFWwindow* window)
{
  EngineContext* ctx = glfwGetWindowUserPointer(window);
  Camera2D* cam = &ctx->cam;
   
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){ 
    glfwSetWindowShouldClose(window, true);
  }
  if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){ 
    cam->zoom = 1.0;
  }
  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){ 
    cam->is_zooming = !cam->is_zooming;
  }  
}
