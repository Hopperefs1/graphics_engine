#include "src/glad.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
class shader {

public:
  string vertSource;

public:
  void ShaderRead(string v) {
    fstream vert(v, ios::in);

    if (vert.is_open() == false) {
      cerr << "FILE FAILED TO OPEN" << endl;
      exit(1);
    }
    string line;
    while (getline(vert, line)) {
      vertSource += line + "\n";
    }
    vert.close();
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *vSource = vertSource.c_str();
    glShaderSource(vertexShader, 1, &vSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      std::cerr << "VERTEX SHADER COMPILE FAILED XD" << infoLog << std::endl;
    }

    cout << vertSource << endl;
  }
};

int main() {
  shader sh;
  sh.ShaderRead("vertex.vert");
  return 0;
}
