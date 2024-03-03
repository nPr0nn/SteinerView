
#include "ext/glad/glad.h"
#include "ext/glfw/zig-out/include/GLFW/glfw3.h"
#include <stdio.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main() {
    // Initialize GLFW
  glfwInit();

  glfwWindowHint(GLFW_SAMPLES, 4);   
  // glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ES_API);

  // Create a windowed mode window and its OpenGL context
  GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL ES Line Example", NULL, NULL);
  if (window == NULL) {
      glfwTerminate();
      return -1;
  }
  glfwMakeContextCurrent(window);

  
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


  // glad: load all OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    printf("ERROR: Failed to initialize GLAD");
  }    

  // Set the viewport size
  glViewport(0, 0, 800, 600);

  // Set the callback for window resizing
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Main loop
  while (!glfwWindowShouldClose(window)) {
      // Input
      processInput(window);

      // Rendering commands here
      glClearColor(0.0f, 0.5f, 0.6f, 1.0f); // Black background
      glClear(GL_COLOR_BUFFER_BIT);
      //
      // // Set the color to white
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      //
      // // Draw a line
      glBegin(GL_LINES);
      glVertex2f(-0.5f, -0.5f);
      glVertex2f(0.5f, 0.5f);
      glEnd();
      //
      // Swap the screen buffers
      glfwSwapBuffers(window);
      // Poll for and process events
      glfwPollEvents();
  }

  // Terminate GLFW
  glfwTerminate();
  return 0;
}

// Function to handle window resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Function to process keyboard input
void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}
