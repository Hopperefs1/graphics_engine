#include "glad.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void render(GLFWwindow *window, unsigned int shaderProgram, unsigned int VAO);
void shaders_Creation();
// simple vertex shader source code store in constant char string

unsigned int vertexShader, fragmentShader;
unsigned int shaderProgram;

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location =0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z,1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "uniform vec4 ourColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "FragColor = ourColor;\n"
                                   "}\n\0";

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

  // Calling the shaders creation function
  shaders_Creation();

  // TRIANGLE
  // vertex input
  float vertices[] = {// triangle 1
                      0.5f,  0.5f, 0.0f,  0.5f, -0.5f, 0.0f, -0.5f,
                      -0.5f, 0.0f, -0.5f, 0.5f, 0.0f

  };
  unsigned int indices[] = {
      0, 1, 3, // tri 1
      1, 2, 3  // tri 2
  };

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

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  //----------------------------------

  render(window, shaderProgram, VAO);
  glfwTerminate();
  return 0;
}

// dont use now created problem
// function which will be called each time the glfw window is resized

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

// SHADERS CREATION FUNCTION
void shaders_Creation() {
  // VERTEX SHADER
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  // checking vertex shader compile error
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  //---------------------------

  // FRAGMENT SHADER (Calculates colour output)
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  //-----------------------------

  // SHADER PROGRAM (LINKS THE TWO SHADERS)
  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // shader linking error checking
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "SHADER PROGRAM LINKING FAILED\n" << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);

  glDeleteShader(fragmentShader);
  //-------------------------------
}

void render(GLFWwindow *window, unsigned int shaderProgram, unsigned int VAO) {
  while (glfwWindowShouldClose(window) == false) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // this is the colour which is shown
                                          // when the colour buffer is cleared
    glClear(GL_COLOR_BUFFER_BIT);         // this clears the colour buffer

    glUseProgram(shaderProgram);
    float timeValue = glfwGetTime();
    float greenValue = sin(timeValue) / 2.0f + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glfwPollEvents(); // this processes events such as user input
    glfwSwapBuffers(
        window); // swaps the front buffer with the back buffer (image is
                 // rendered in the back buffer) this prevents flickering
  }
}
