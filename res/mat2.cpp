#include "../include/mat2.h"

Mat2::Mat2()
{
  matrix[0] = 0.0f;
  matrix[1] = 0.0f;
  matrix[2] = 0.0f;
  matrix[3] = 0.0f;
}

Mat2::Mat2(float num0,float num1,float num2,float num3)
{
  matrix[0] = num0;
  matrix[1] = num1;
  matrix[2] = num2;
  matrix[3] = num3;
}

Mat2::Mat2(float matrixIn[])
{
  matrix[0] = matrixIn[0];
  matrix[1] = matrixIn[1];
  matrix[2] = matrixIn[2];
  matrix[3] = matrixIn[3];
}

Mat2 Mat2::operator * (Mat2& other)
{
  Mat2 returned;

  returned.getMatrix()[0] = matrix[0]*other.getMatrix()[0] + matrix[1]*other.getMatrix()[2];
  returned.getMatrix()[1] = matrix[0]*other.getMatrix()[1] + matrix[1]*other.getMatrix()[3];
  returned.getMatrix()[2] = matrix[2]*other.getMatrix()[0] + matrix[3]*other.getMatrix()[2];
  returned.getMatrix()[3] = matrix[2]*other.getMatrix()[1] + matrix[3]*other.getMatrix()[3];

  return returned;
}
Mat2 Mat2::operator + (Mat2& other)
{
  Mat2 returned;

  returned.getMatrix()[0] = matrix[0] + other.getMatrix()[0];
  returned.getMatrix()[1] = matrix[1] + other.getMatrix()[1];
  returned.getMatrix()[2] = matrix[2] + other.getMatrix()[2];
  returned.getMatrix()[3] = matrix[3] + other.getMatrix()[3];

  return returned;
}
Mat2 Mat2::operator - (Mat2& other)
{
  Mat2 returned;

  returned.getMatrix()[0] = matrix[0] - other.getMatrix()[0];
  returned.getMatrix()[1] = matrix[1] - other.getMatrix()[1];
  returned.getMatrix()[2] = matrix[2] - other.getMatrix()[2];
  returned.getMatrix()[3] = matrix[3] - other.getMatrix()[3];

  return returned;
}

Vec2 Mat2::operator * (Vec2& other)
{
  Vec2 returned;

  returned.at(0) = at(0,0)*other.at(0) + at(0,1)*other.at(1);
  returned.at(1) = at(1,0)*other.at(0) + at(1,1)*other.at(1);

  return returned;
}

float& Mat2::at(int r, int c)
{
  return matrix[r*2 + c];
}

float* Mat2::getMatrix() {return matrix;}