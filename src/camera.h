#ifndef MYPROJ_CAMERA_H
#define MYPROJ_CAMERA_H

// dependencies
#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glm/gtc/matrix_transform.hpp"
#include "../Dependencies/glm/gtc/quaternion.hpp"
#include "../Dependencies/glm/gtc/type_ptr.hpp"
#include "../shaders/shader.h"

typedef struct {
  glm::vec3 cameraPos;
  float cameraSpeed;
} Camera3D;

static const glm::vec3 cameraZ = glm::vec3(0.0f, 0.0f, -1.0f);
static const glm::vec3 cameraY = glm::vec3(0.0f, 1.0f, 0.0f);
static const glm::vec3 cameraX = glm::vec3(1.0f, 0.0f, 0.0f);

namespace cam {

void viewMat(Camera3D *cam, unsigned int shaderProgram) {
  glm::mat4 view = glm::mat4(1.0f);
  view = glm::lookAt(cam->cameraPos, cam->cameraPos + cameraZ, cameraY);
  int viewLoc = glGetUniformLocation(shaderProgram, "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}

void projectionMat(unsigned int shaderProgram) {
  glm::mat4 projection;
  projection =
      glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
  int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void camInput(Camera3D *cam, GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    cam->cameraPos += cam->cameraSpeed * cameraZ;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    cam->cameraPos -= cam->cameraSpeed * cameraZ;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    cam->cameraPos += cameraX * cam->cameraSpeed;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    cam->cameraPos -= cameraX * cam->cameraSpeed;
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    cam->cameraPos += cam->cameraSpeed * cameraY;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    cam->cameraPos -= cam->cameraSpeed * cameraY;
  }
}
} // namespace cam
#endif
