#ifndef PIXY_GL_H
#define PIXY_GL_H
#include "Dependencies/glad.h"


void ClrColor(float r, float g, float b, float a) {
  glClearColor(r, g, b, a);     // sets the window colour
  glClear(GL_COLOR_BUFFER_BIT); // clears the color buffer and the z-buffer for
}
void EnDepthTest() { glEnable(GL_DEPTH_TEST); }
void DisDepthTest() { glDisable(GL_DEPTH_TEST); }

void ClrBuffers() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void start3D(bool x) {
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
#endif // !PIXY_GL_H
