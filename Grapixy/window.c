#include "window.h"
#include "time.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

void framebuffer_size_callback(GLFWwindow *window1, int width, int height) {
  glViewport(0, 0, width, height);
}
void winInit() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
void winCt(My_window *window,char const *name) {
  // CREATING WINDOW
  window->window =
      glfwCreateWindow(window->width, window->height, "hello", NULL, NULL);

  if (window->window == NULL) {
    printf("FAILED TO CREATE WINDOW\n");
    glfwTerminate();
    return;
  } else {
    printf("Window created successfully\n");
  }
  glfwMakeContextCurrent(window->window);
  glfwSetFramebufferSizeCallback(window->window, framebuffer_size_callback);
}
void winQt(My_window *window){
glfwSetWindowShouldClose(window->window,GLFW_TRUE);
}
void winOut() { glfwTerminate(); }
void winShColor(float r, float g, float b, float a) {
                                // depth testing
}

void winUpdate(My_window *window) {
  glfwSwapBuffers(
      window->window); // swaps the front buffer with the back buffer (image is
                       // rendered in the back buffer) this prevents flickering
}
void winPollEvents() { glfwPollEvents(); }

float winDTime(My_window *window) {
  window->time.currentFrame = glfwGetTime();
  float deltaTime = window->time.currentFrame - window->time.lastFrame;
  window->time.lastFrame = window->time.currentFrame;
  return deltaTime;
}
bool IswinClosed(My_window window){
	return glfwWindowShouldClose(window.window);
}
