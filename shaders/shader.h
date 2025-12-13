#ifndef SHADER_H
#define SHADER_H

#include "../src/glad.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
class shader {
  string vertPath, vSourceStr;
  string fragPath, fSourceStr;

  unsigned int vertexShader, fragmentShader;

public:
  shader(string vertPath, string fragPath) {
    this->vertPath = vertPath;
    this->fragPath = fragPath;
  }

  void vert_frag_ShaderRead() {
    // creating the filestreams object for readding
    fstream vert(vertPath, ios::in);
    fstream frag(fragPath, ios::in);

    // checking whether opend or not lol
    if (vert.is_open() == false) {
      cerr << "VERTEX SHADER FILE FAILED TO OPEN" << endl;
    }
    if (frag.is_open() == false) {
      cerr << "FRAGMENT SHADER FILE FAILED TO OPEN" << endl;
    }
    stringstream vertStream, fragStream;
    vertStream << vert.rdbuf();
    fragStream << frag.rdbuf();

    vSourceStr = vertStream.str();
    fSourceStr = fragStream.str();

    vert.close();
    frag.close();
    // uhh creating a c like string by eliminating null will take some time to
    // understand lol
  }

  void vertexShader_Compile() {

    const char *vSource = vSourceStr.c_str();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      std::cerr << "VERTEX SHADER COMPILE FAILED XD" << infoLog << std::endl;
    }
  }
  void fragmentShader_Compile() {

    const char *fSource = fSourceStr.c_str();
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fSource, NULL);
    glCompileShader(fragmentShader);
    int success;
    char infoLog[512];
    // error Checking
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      std::cerr << "FRAGMENT SHADER COMPILE FAILED XD" << infoLog << std::endl;
    }
  }
  void shader_Compile(unsigned int &shaderProgram) {
    vert_frag_ShaderRead();
    vertexShader_Compile();
    fragmentShader_Compile();
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    int success;
    char infoLog[512];
    // error checking
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      std::cerr << "SHADEr PROGRAM LINKING FAILED LMAOO DED" << infoLog
                << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
  }
};
#endif
