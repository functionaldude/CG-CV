#pragma once
#include <vector>
#include "Sphere.h"
#include "Plane.h"
class Scene1a
{
public:
  Scene1a();
  virtual ~Scene1a();

  void add(Item* item);
  const std::vector<Item*>& getItems() const;
  void setViewBox(float from, float to);
  
  bool renderRays_ = false;
  
  // DO NOT MODIFY THESE
  // funktion pointer to intersect spheres 
  bool (*intersectRayWithSphere_)(const float3& p, const float3& d, const float3& c, float r, float& t);
  // function pointer to intersect cubes
  bool (*intersectRayWithPlane_)(const float3& p, const float3& d, const float3& p_0, const float3& n, float& t);
  
  /*
   * This method performs an intersection with the
   * given ray and all the objects in the scene.
   * 
   * It returns true iff an intersection occured.
   * 
   * The distance to the intersection point is 
   * provided in @param distance.
   * 
   * @param ray - the direction of the ray 
   *              with origin in (0,0,0)
   *
   * @param distance - will be set when intersection occurs
   *
   * @returns whether or not an intersection occured 
   */
  bool intersectWithRay(float3 ray, float& distance) const;

protected:
  struct ViewBox{
      float from;
      float to;
  };
  struct ViewBox viewbox_;
  std::vector<Item*> items_;
  
  // scales distance according to viewbox 
  float scaleDistance(float d) const;
};

