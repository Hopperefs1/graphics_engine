#ifndef HOPPO_MATH_H
#define HOPPO_MATH_H

typedef struct {
  float x;
  float y;
  float z;
} vect3;

typedef struct {
  float mat[4][4];
} mat4;

vect3 setVec3(float x, float y, float z) {
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
mat4 setMat4(float x) {
	mat4 mat1 = {{
		{x,x,x,x},
		{x,x,x,x},
		{x,x,x,x},
		{x,x,x,x}
	}};
	return mat1;
}
mat4 iMat4(){
	mat4 mat1 = {{
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1},
	}};
	return mat1;
}
mat4 scaleMat4(float x){
	mat4 mat1;
	for(int i =0;i<4;i++){
		for(int j=0;j<4;j++){
			mat1.mat[i][j] *= x;
		}
	}
	return mat1;
}





#endif
