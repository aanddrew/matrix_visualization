#ifndef VEC2_H
#define VEC2_H

class Vec2
{
public:
  Vec2();
  Vec2(float num0, float num1);
  Vec2(float columnIn[]);

  float& at(int index);

  Vec2 operator * (float& other);
private:
  float nums[2];
};

#endif