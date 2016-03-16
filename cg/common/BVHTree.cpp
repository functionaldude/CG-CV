#include "BVHTree.h"
#include "BVHTreeNode.h"
#include "Intersection.h"
#include "Triangle.h"
#include "Ray.h"
#include "vector.h"
#include <vector>

BVHTree::BVHTree()
{
}

BVHTree::~BVHTree()
{
}

void BVHTree::construct(std::vector<Triangle>& triangles, int leaf_size)
{
  root = StrongNodePtr(new BVHTreeNode(&triangles[0], static_cast<int>(triangles.size()), leaf_size, test_leaf_nodes));
}

bool BVHTree::intersectRay(const Ray& ray, Intersection & intersection)
{
  if (root)
  {
    float intersected_distance = std::numeric_limits<float>::max();
    const Triangle* intersected_triangle = 0;
    float2 barycentric;
    bool intersected = intersectRay(ray, root.get(),
      intersected_triangle, intersected_distance, barycentric);
    if (intersected)
    {
      intersection.intersectedFace = (*intersected_triangle);
      intersection.position = ray.start + ray.dir * intersected_distance;
      intersection.normal = normalize((1 - barycentric(0) - barycentric(1)) * intersected_triangle->normals[0] +
        barycentric(0) * intersected_triangle->normals[1] +
        barycentric(1) * intersected_triangle->normals[2]);
      intersection.material_index = intersected_triangle->material_index;
      intersection.distance = intersected_distance;
    }
    return intersected;
  }
  return false;
}
