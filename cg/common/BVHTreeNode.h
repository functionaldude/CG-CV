#pragma once
#include "BoundingBox.h"
#include <vector>
#include <memory>
#include "Triangle.h"

class BVHTreeNode
{
public:
  typedef std::shared_ptr<BVHTreeNode> StrongNodePtr;
  typedef std::vector<StrongNodePtr> StrongNodePtrVector;

  BoundingBox bounds;
  StrongNodePtr left;
  StrongNodePtr right;
  std::vector<Triangle> triangles;

  BVHTreeNode();
  BVHTreeNode(Triangle* triangles, int num_triangles, int leaf_size, StrongNodePtrVector& test_left_leafes);
  virtual ~BVHTreeNode();

protected:
  void sortTriangles(Triangle* triangles, int num_triangles, int sort_axis);
};

