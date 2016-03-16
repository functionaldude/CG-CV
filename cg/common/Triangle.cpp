#include "Triangle.h"
#include "Ray.h"

Triangle::Triangle()
{
}

Triangle::Triangle(const math::float3& p1,
  const math::float3& p2,
  const math::float3& p3,
  const math::float3& normal1,
  const math::float3& normal2,
  const math::float3& normal3,
  int material_index)
  : material_index(material_index)
{
  points[0] = p1;
  points[1] = p2;
  points[2] = p3; 
  normals[0] = normal1;
  normals[1] = normal2;
  normals[2] = normal3;
  cacheFaceNormal();
}

Triangle::~Triangle()
{
}

void Triangle::cacheFaceNormal()
{
  triangle_normal = normalize(cross(points[1] - points[0], 
    points[2] - points[0]));
}

float Triangle::minValueOnAxis(int axis) const
{
  return std::min(points[0](axis), std::min(points[1](axis),
    points[2](axis)));
}

bool Triangle::compareByAxis(const Triangle& b, int axis) const
{
  float a_min = minValueOnAxis(axis);
  float b_min = b.minValueOnAxis(axis);
  return a_min < b_min;
}

bool Triangle::compareByX(const Triangle& a, const Triangle& b)
{
  return a.compareByAxis(b, 0);
}

bool Triangle::compareByY(const Triangle& a, const Triangle& b)
{
  return a.compareByAxis(b, 1);
}

bool Triangle::compareByZ(const Triangle& a, const Triangle& b)
{
  return a.compareByAxis(b, 2);
}
