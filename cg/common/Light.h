#pragma once
#include "vector.h"
class Light
{
public:
  float3 position;
  float3 normal;
  float3 intensities;
  float3 ambient;

  Light();
  virtual ~Light();
};

