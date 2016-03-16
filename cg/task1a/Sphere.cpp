#include "Sphere.h"

Sphere::Sphere()
  : center_(float3(0, 0, 0))
  , radius_(1)
{
}

Sphere::Sphere(const float3& center, float radius)
  : center_(center)
  , radius_(radius)
{
}

Sphere::~Sphere()
{
}

const float3 Sphere::getCenter() const
{
  return center_;
}

float Sphere::getRadius() const
{
  return radius_;
}

void Sphere::setCenter(const float3 & center)
{
  center_ = center;
}

void Sphere::setRadius(float radius)
{
  radius_ = radius;
}
