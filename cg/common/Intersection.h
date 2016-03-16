#pragma once
#include "vector.h"
#include "Triangle.h"
class Material;
class Intersection
{
public:
  Triangle intersectedFace;
  float3 position;
  float3 normal;
  int material_index;
  float distance;

  Intersection();
  virtual ~Intersection();
};

