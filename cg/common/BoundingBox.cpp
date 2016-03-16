#include "BoundingBox.h"
#include "Ray.h"

BoundingBox::BoundingBox()
  : position(0.f)
  , size(0.f)
{
}

BoundingBox::BoundingBox(const float3& position, const float3& size)
  : position(position)
  , size(size)
{
}

BoundingBox::~BoundingBox()
{
}

bool BoundingBox::intersectRay(const Ray & ray, float* t) const
{
  const float3& bb_min = position;
  const float3 bb_max = position + size;
  const float3& r_o = ray.start;
  const float3& r_d = ray.dir;

  auto swap = [](float& a, float& b)
  {
    auto c = a;
    a = b;
    b = c;
  };

  float tmin = (bb_min.x - r_o.x) / r_d.x;
  float tmax = (bb_max.x - r_o.x) / r_d.x;

  if (tmin > tmax) swap(tmin, tmax);

  float tymin = (bb_min.y - r_o.y) / r_d.y;
  float tymax = (bb_max.y - r_o.y) / r_d.y;

  if (tymin > tymax) swap(tymin, tymax);

  if ((tmin > tymax) || (tymin > tmax))
    return false;

  if (tymin > tmin)
    tmin = tymin;

  if (tymax < tmax)
    tmax = tymax;

  float tzmin = (bb_min.z - r_o.z) / r_d.z;
  float tzmax = (bb_max.z - r_o.z) / r_d.z;

  if (tzmin > tzmax) swap(tzmin, tzmax);

  if ((tmin > tzmax) || (tzmin > tmax))
    return false;

  if (tzmin > tmin)
    tmin = tzmin;

  if (tzmax < tmax)
    tmax = tzmax;

  if (t)
    *t = tmin;

  return true;
}
