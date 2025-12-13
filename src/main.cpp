#include "../shaders/shader.h"
#include "glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void render(GLFWwindow *window, unsigned int VAO, unsigned int texture1,
            unsigned int texture2, unsigned int shaderProgram);
// simple vertex shader source code store in constant char string

int main() {
  // INITIALIZING GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // CREATING WINDOW
  GLFWwindow *window = glfwCreateWindow(800, 600, "hello", NULL, NULL);

  if (window == NULL) {
    std::cout << "FAILED TO CREATE GLFW WINDOW" << std::endl;
    glfwTerminate();

    return -1;
  }
  glfwMakeContextCurrent(window);

  //---------------------------------

  // INITIALIZING GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "FAILED TO INITIALIZE GLAD" << std::endl;
    return -1;
  }
  glViewport(0, 0, 800, 600);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  //----------------------------------

  // TRIANGLE
  // vertex input

  float vertices[] = {
      // positions       // colors        // tex coords
      0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // top right
      0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // top left
  };
  unsigned int indices[] = {
      0, 1, 2, // tri 1
      2, 3, 0  // tri 2
  };

  unsigned int texture1, texture2;
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glPixelStorei(
      GL_UNPACK_ALIGNMENT,
      1); // whatever happens remember this one line for your whole life this
          // makes opengl read the bytes of a image byte by byte with no padding

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data =
      stbi_load("texture/sukuna.jpg", &width, &height, &nrChannels, 0);
  if (data != NULL) {
    GLenum format = GL_RGBA;
    if (nrChannels == 3) {
      format = GL_RGB;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
  } else {
    cerr << "image not loaded properly" << endl;
  }

  stbi_image_free(data);

  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glPixelStorei(
      GL_UNPACK_ALIGNMENT,
      1); // whatever happens remember this one line for your whole life this
  //
  data = stbi_load("texture/shub.jpg", &width, &height, &nrChannels, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, data);

  stbi_image_free(data);

  unsigned int VBO, VAO, EBO; // vertex buffer object(VBO) manages memory and
                              // vertices on gpu  vertex array object(VAO)....
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO); // generating 1 vertex buffer object
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER,
               VBO); // binding the buffer object with GL_ARRAY_BUFFER.
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);
  // position attrib
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // color attrib pointer
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  //----------------------------------

  unsigned int shaderProgram;
  shader *sobj = new shader("shaders/vertex.vert", "shaders/fragment.frag");
  sobj->shader_Compile(shaderProgram);
  glUseProgram(shaderProgram);
  glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
  glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

  render(window, VAO, texture1, texture2, shaderProgram);

  glDeleteProgram(shaderProgram);
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
  glDeleteTextures(1, &texture1);
  glfwTerminate();
  return 0;
}

// dont use now created problem fuck
// function which will be called each time the glfw window is resized

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void render(GLFWwindow *window, unsigned int VAO, unsigned int texture1,
            unsigned int texture2, unsigned int shaderProgram) {

  while (glfwWindowShouldClose(window) == false) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // this is the colour which is shown
                                          // when the colour buffer is cleared
    glClear(GL_COLOR_BUFFER_BIT);         // this clears the colour buffer
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwPollEvents(); // this processes events such as user input
    glfwSwapBuffers(
        window); // swaps the front buffer with the back buffer (image is
                 // rendered in the back buffer) this prevents flickering
  }
}
