#ifndef MY_WINDOW_H
#define MY_WINDOW_H
#include <GLFW/glfw3.h>
#include "time.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct{
  GLFWwindow *window;
  int width;
  int height;
  Time time;
}My_window;

void winInit();
void winCt(My_window *window, char const *name); 

void winQt(My_window *window);
void winOut();
void winShColor(float r, float g, float b, float a);

void winUpdate(My_window *window);
void winPEvents() ;
float winDTime(My_window *window);

#ifdef __cplusplus
}
#endif


#endif // ! MY_WINDOW_H
