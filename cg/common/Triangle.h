#pragma once
#include "vector.h"
class Ray;
class Triangle
{
public:
  math::float3 points[3];
  math::float3 normals[3];

  int material_index;

  math::float3 triangle_normal;

  Triangle();

  Triangle(const math::float3& p1,
    const math::float3& p2,
    const math::float3& p3,
    const math::float3& normal1,
    const math::float3& normal2,
    const math::float3& normal3,
    int material_index);

  void cacheFaceNormal();

  float minValueOnAxis(int axis) const;
  bool compareByAxis(const Triangle& b, int axis) const;
  static bool compareByX(const Triangle& a, const Triangle& b);
  static bool compareByY(const Triangle& a, const Triangle& b);
  static  bool compareByZ(const Triangle& a, const Triangle& b);

  bool intersectRay(const Ray& ray, float& distance, float2& barycentric) const;

  //bool intersectWithRay(Ray ray, float& t, float2& barycentric) const;
};

