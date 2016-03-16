#include "Ray.h"

Ray::Ray(const float3& start, const float3& dir)
  : start(start)
  , dir(dir)
{
}

Ray::~Ray()
{
}
