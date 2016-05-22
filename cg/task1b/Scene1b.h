#pragma once

#include <vector>
#include "Scene.h"
#include "Light.h"
#include "Camera.h"
#include "vector.h"

class Scene1b : public Scene {
public:
    std::vector<Light *> lights;
    Camera *cam;
    bool ray_test;
    bool phong_test;
    bool refl_test;
    bool empty;

    Scene1b();

    float3 traceRay(const Ray &ray, int depth = 0) const;

    bool intersectRay(const Ray &ray, Intersection &intersection) const;

    float3 phong(const Ray &ray, const Intersection &hit) const;
};

