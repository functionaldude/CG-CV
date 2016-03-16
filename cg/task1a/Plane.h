#pragma once
#include "vector.h"
#include "Item.h"
class Plane : public Item
{
public:
  Plane();
  Plane(const float3& point, const float3& normal);
  virtual ~Plane();

  const float3 getPoint() const;
  const float3 getNormal() const;
  void setPoint(const float3& p);
  void setNormal(const float3& n);

protected:
  float3 point_;
  float3 normal_;
};

