#include "Plane.h"

Plane::Plane()
  : point_(float3(0, 0, 0))
  , normal_(float3(0, 0, 1))
{
}

Plane::Plane(const float3& point, const float3& normal)
  : point_(point)
  , normal_(normal)
{
}

Plane::~Plane()
{
}

const float3 Plane::getPoint() const
{
  return point_;
}

const float3 Plane::getNormal() const
{
  return normal_;
}


void Plane::setPoint(const float3& p)
{
  point_ = p;
}
void Plane::setNormal(const float3& n)
{
  normal_ = n;
}
