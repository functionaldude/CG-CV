#pragma once
#include "vector.h"
class Ray;
class BoundingBox
{
public:
  float3 position;
  float3 size;

  BoundingBox();
  BoundingBox(const float3& position, const float3& size);
  virtual ~BoundingBox();

    bool intersectRay(const Ray &ray, float *t = 0, float3 *normal = 0) const;
};

