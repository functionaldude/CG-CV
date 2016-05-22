#pragma once
#include <vector>
#include <memory>
#include "vector.h"

class BVHTreeNode;
class Intersection;
class Triangle;
class Ray;
class BVHTree
{
public:
  typedef std::shared_ptr<BVHTreeNode> StrongNodePtr;
  typedef std::vector<StrongNodePtr> StrongNodePtrVector;
  StrongNodePtr root;
  StrongNodePtrVector test_leaf_nodes;

  BVHTree();

  void construct(std::vector<Triangle>& triangles, int leaf_size);

    bool intersectRay(const Ray &ray, Intersection &intersection) const;

protected:

    bool intersectRay(const Ray &ray, const BVHTreeNode &node, const Triangle *&triangle, float &t,
                      float2 &barycentric) const;
};
