#pragma once

#include <vector>
#include "Material.h"
#include "Triangle.h"
#include "BVHTree.h"

class Scene
{
public:
  std::vector<Material> materials;
  BVHTree bvh_tree;
  std::vector<Triangle> area_lights;
  //std::vector<Light*> lights;
  //Camera* cam;

  Scene();
  virtual ~Scene();

  //bool intersectRay(const Ray& ray, Intersection& intersection);
  //bool intersectRayEarlyExitDistance(const Ray& ray, float max_distance, 
  //  Intersection& intersection);
};

