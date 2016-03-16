#include "Material.h"

#define EPSILON 0.001f

Material::Material()
  : diffuse(0.2f, 0.2f, 0.2f)
  , specular(0.6f, 0.6f, 0.6f)
  , shininess(30.f)
  , emissive(0.0f, 0.0f, 0.0f)
  , ambient(0.6f, 0.6f, 0.6f)
  , reflective(false)
  , density(1.f)
  , transparent(false)
{
}

Material::Material(const float3& ke, const float3& ks, 
  const float3& ka, const float3& kd, float ns)
{
  this->ambient = ka;
  this->diffuse = kd;
  this->emissive = ke;
  this->specular = ks;
  this->shininess = ns;
  this->reflective = false;
  this->density = 1.f;
  this->transparent = false;
}

Material::~Material()
{
}

bool Material::isLight() const
{
	return math::length(emissive) > EPSILON;
}
