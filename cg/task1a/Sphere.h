#pragma once
#include "vector.h"
#include "Item.h"
class Sphere : public Item
{
public:
  Sphere();
  Sphere(const float3& center, float radius);
  virtual ~Sphere();

  const float3 getCenter() const;
  float getRadius() const;
  void setCenter(const float3& center);
  void setRadius(float radius);

protected:
  float3 center_;
  float radius_;
};

