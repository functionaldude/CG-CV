#pragma once
#include "vector.h"
class Material
{
public:
  float3 diffuse;
  float3 specular;
  float3 ambient;
  float3 emissive;
  float shininess;
  bool reflective;
  float density;
  bool transparent;

  Material();
  Material(const float3& ke, const float3& ks, const float3& ka, 
    const float3& kd, float ns);
  virtual ~Material();

  bool isLight() const;
};

