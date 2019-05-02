#include <iostream>

#include "include/mat2.h"
#include "include/vec2.h"
#include "app.h"

void printMat(Mat2& mat)
{
  std::cout << "|" << mat.at(0,0) << " " << mat.at(0,1) << "|" << std::endl;
  std::cout << "|" << mat.at(1,0) << " " << mat.at(1,1) << "|" << std::endl;
}

void printVec(Vec2& vec)
{
  std::cout << "|" << vec.at(0) << "|" << std::endl;
  std::cout << "|" << vec.at(1) << "|" << std::endl;
}

int main()
{
  Mat2 id;
  id.at(0,0) = 1.0f;
  id.at(0,1) = 0.0f;
  id.at(1,0) = 0.0f;
  id.at(1,1) = 1.0f;

  Mat2 mat_1;
  mat_1.at(0,0) = 2.0f;
  mat_1.at(0,1) = 3.0f;
  mat_1.at(1,0) = 4.0f;
  mat_1.at(1,1) = 5.0f;

  printMat(id);  
  std::cout << " ----------  " << std::endl;

  Mat2 mul = id* mat_1;
  printMat(mul);

  Vec2 vec(2,1);
  printVec(vec);

  Vec2 vecMul = id*vec;
  printVec(vecMul);

  Vec2 vecMul2 = mat_1*vec;
  printVec(vecMul2);

  App app;
  app.run();

  return 0;
}