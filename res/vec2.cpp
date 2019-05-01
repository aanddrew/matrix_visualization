#include "../include/vec2.h"

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