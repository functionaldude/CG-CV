#pragma once
#include "vector.h"
class Ray
{
public:
  float3 start;
  float3 dir;

  Ray(const float3& start, const float3& dir);
  virtual ~Ray();
};

