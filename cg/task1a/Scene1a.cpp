#include <cmath>

#include "Scene1a.h"

Scene1a::Scene1a()
{
}

Scene1a::~Scene1a()
{
}

void Scene1a::add(Item* item)
{
  items_.push_back(item);
}

const std::vector<Item*>& Scene1a::getItems() const
{
  return items_;
}

void Scene1a::setViewBox(float from, float to){
  viewbox_.to = to;
  viewbox_.from = from;
}

float Scene1a::scaleDistance(float d) const
{
  if(d>viewbox_.to || d<viewbox_.from) return 0.0f;
  return 1.0f - ((float)((1.0 / (viewbox_.to- viewbox_.from) * (d-viewbox_.from)))); 
}

bool Scene1a::intersectWithRay(float3 ray, float& distance) const {
    if(renderRays_){
        // just render angle to z-axis
        distance = std::acos(-ray.z) * 0.63661977236758134307553505349006f;
        return true;
    }
    
    float max_distance = std::numeric_limits<float>::max();

    float tmpdistance;
    float bestdistance = max_distance;

    bool intersected = false;
    for(std::vector<Item*>::const_iterator it = items_.begin(); it != items_.end(); ++it) {
        bool intersect;
        if(Sphere* s = dynamic_cast<Sphere*>(*it)) {
            intersect = (*intersectRayWithSphere_)(float3(0.0f, 0.0f, 0.0f), ray, s->getCenter(), s->getRadius(), tmpdistance);
        } else if(Plane* p = dynamic_cast<Plane*>(*it)) {
            intersect = (*intersectRayWithPlane_)(float3(0.0f, 0.0f, 0.0f), ray, p->getPoint(), p->getNormal(), tmpdistance);
        }
        if(intersect){
            if(tmpdistance<bestdistance){
                intersected = true;
                bestdistance = tmpdistance;
            }
        }
    }
    if(intersected){
        distance = scaleDistance(bestdistance);
    }
    
    return intersected;
}
