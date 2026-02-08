#ifndef PIXY_MATH_H
#define PIXY_MATH_H

typedef struct {
  float x;
  float y;
  float z;
} vect3;

typedef struct {
  float mat[4][4];
} mat4;

vect3 Vec3(float x, float y, float z) {
  vect3 temp;
  temp.x = x;
  temp.y = y;
  temp.z = z;
  return temp;
}
vect3 mulVec3(vect3 v1, vect3 v2) {
  v1.x *= v2.x;
  v1.y *= v2.y;
  v1.z *= v2.z;
  return v1;
}
mat4 Mat4(float x) {
  mat4 mat1 = {{{x, x, x, x}, {x, x, x, x}, {x, x, x, x}, {x, x, x, x}}};
  return mat1;
}
mat4 iMat4() {
  mat4 mat1 = {{
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1},
  }};
  return mat1;
}
mat4 SclMulMat4(mat4 mat1,float x) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      mat1.mat[i][j] *= x;
    }
  }
  return mat1;
}

mat4 SclAddMat4(mat4 mat1,float x) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      mat1.mat[i][j] += x;
    }
  }
  return mat1;
}

mat4 SclSubMat4(mat4 mat1,float x) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      mat1.mat[i][j] -= x;
    }
  }
  return mat1;
}

mat4 MulMat4(mat4 mat1, mat4 mat2) {
  mat4 result={0};
  short r = 0;
  for (int k = 0; k < 4; k++) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        result.mat[k][i] += (mat1.mat[i][j] * mat2.mat[j][i]);
      }
    }
  }
  return result;
}

#endif
