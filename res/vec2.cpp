#include "../include/vec2.h"
#include "../include/mat2.h"

#include <math.h>

Vec2::Vec2()
{
  nums[0] = 0.0f;
  nums[1] = 0.0f;
}

Vec2::Vec2(float num0, float num1)
{
  nums[0] = num0;
  nums[1] = num1;
}

Vec2 Vec2::operator * (float& other)
{
  Vec2 returned(nums[0] * other, nums[1]*other);
  return returned;
}

Vec2::Vec2(float numsIn[])
{
  nums[0] = numsIn[0];
  nums[1] = numsIn[1];
}

float& Vec2::at(int index)
{
  return nums[index];
}

void Vec2::rotate(float dTheta)
{
  float c = cos(dTheta);
  float s = 1 - (c*c);
  Mat2 transform(c, -1*s, s, c);

  float m = mag();

  *this = transform*(*this);
  normalize();
  *this = (*this)*m; 
}

float Vec2::mag()
{
  return sqrt(nums[0]*nums[0] + nums[1]*nums[1]);
}

Vec2 Vec2::normalize()
{
  float m = mag();
  nums[0] /= m;
  nums[1] /= m;

  return *this;
}