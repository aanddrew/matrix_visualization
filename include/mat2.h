#ifndef MAT_H
#define MAT_H

#include "vec2.h"

class Mat2
{
public:
  Mat2();
  Mat2(float num0,float num1,float num2,float num3);
  Mat2(float matrixIn[]);

  Mat2 operator * (Mat2& other);
  Mat2 operator + (Mat2& other);
  Mat2 operator - (Mat2& other);

  Vec2 operator * (Vec2& other);

  float& at(int r, int c);

  float*  getMatrix();
private:
  float matrix[4];
};

#endif