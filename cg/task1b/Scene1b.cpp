#include "Scene1b.h"
#include "Light.h"
#include "Intersection.h"
#include "Ray.h"
#include "BoundingBox.h"

using math::length;
using math::normalize;

float3 traceRay(const Ray &ray, const Scene1b &scene, int depth = 0);

float3 phong(const Ray &ray, const Intersection &hit, const Scene1b &scene);

bool intersectRay(const Ray &ray, const BVHTreeNode &node, const Triangle *&intersected_triangle, float &t,
                  float2 &barycentric);


Scene1b::Scene1b()
        : Scene(), ray_test(false), phong_test(false), refl_test(false), empty(true) {
}

float3 Scene1b::traceRay(const Ray &ray, int depth) const {
    if (ray_test) {
        BoundingBox bb(float3(-0.5f), float3(1.f));
        float t;
        if (bb.intersectRay(ray, &t)) {
            t = length(ray.start) - t + 1.5f;
            return float3(t / 3.f);
        }
        return float3(0.f);
    }
    else {
        return ::traceRay(ray, *this, depth);
    }
}

bool Scene1b::intersectRay(const Ray &ray, Intersection &intersection) const {
    if (phong_test) {
        BoundingBox bb(float3(-0.5f), float3(1.f));
        BoundingBox bb2(float3(-1000.f, -1000.f, -200.f), float3(2000.f, 2000.f, 10.f));
        float t;
        float3 normal;
        if ((bb.intersectRay(ray, &t, &normal) && t > 0.f) ||
            (bb2.intersectRay(ray, &t, &normal) && t > 0.f)) {
            intersection.distance = t;
            intersection.material_index = 0;
            intersection.normal = normal;
            intersection.position = ray.start + ray.dir * t;
            return true;
        }
        return false;
    }
    else if (refl_test) {
        BoundingBox bb(float3(-0.5f), float3(1.f));
        BoundingBox bb2(float3(-1000.f, -1000.f, -3.f), float3(2000.f, 2000.f, 1.f));
        BoundingBox bb3(float3(-1000.f, -1000.f, 3.f), float3(2000.f, 2000.f, 1.f));
        float t;
        float3 normal;
        if ((bb.intersectRay(ray, &t, &normal) && t > 0.f)) {
            intersection.distance = t;
            intersection.material_index = 0;
            intersection.normal = normal;
            intersection.position = ray.start + ray.dir * t;
            return true;
        }
        if (bb2.intersectRay(ray, &t, &normal) && t > 0.f) {
            intersection.distance = t;
            intersection.material_index = static_cast<int>(materials.size()) - 1;
            intersection.normal = normal;
            intersection.position = ray.start + ray.dir * t;
            return true;
        }
        if (bb3.intersectRay(ray, &t, &normal) && t > 0.f) {
            intersection.distance = t;
            intersection.material_index = static_cast<int>(materials.size()) - 1;
            intersection.normal = normal;
            intersection.position = ray.start + ray.dir * t;
            return true;
        }
        return false;
    }
    else {
        return bvh_tree.intersectRay(ray, intersection);
    }
}

float3 Scene1b::phong(const Ray &ray, const Intersection &hit) const {
    if (refl_test) {
        return materials[hit.material_index].diffuse;
    }
    return ::phong(ray, hit, *this);
}

bool BVHTree::intersectRay(const Ray &ray, const BVHTreeNode &node, const Triangle *&triangle, float &t,
                           float2 &barycentric) const {
    return ::intersectRay(ray, *root, triangle, t, barycentric);
}

bool Triangle::intersectRay(const Ray &ray, float &distance, float2 &barycentric) const {
    const float EPSILON = 0.000001f;

    float3 e1 = points[1] - points[0];
    float3 e2 = points[2] - points[0];
    float3 ray_dir = ray.dir;
    float3 ray_origin = ray.start;

    float3 P = cross(ray_dir, e2);
    float det = dot(e1, P);

    if (det > -EPSILON && det < EPSILON)
        return false;

    float det_inv = 1.f / det;

    float3 T = ray_origin - points[0];
    float u = dot(T, P) * det_inv;
    if (u < 0.f || u > 1.f)
        return false;

    float3 Q = cross(T, e1);
    float v = dot(ray_dir, Q) * det_inv;
    if (v < 0.f || u + v > 1.f)
        return false;

    float t = dot(e2, Q) * det_inv;
    if (t > EPSILON) {
        distance = t;
        barycentric.x = u;
        barycentric.y = v;
        return true;
    }

    return false;
}
