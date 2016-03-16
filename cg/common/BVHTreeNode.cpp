#include "BVHTreeNode.h"
#include "vector.h"
#include "Triangle.h"
#include <limits>
#include <vector>

BVHTreeNode::BVHTreeNode()
{
}

BVHTreeNode::BVHTreeNode(Triangle* triangles, int num_triangles, int leaf_size, StrongNodePtrVector& test_left_leafes)
{
  float float_max = std::numeric_limits<float>::max();
  float3 min(float_max), max(-float_max);
  float3 sum(0.f);
  for (int triangle_index = 0; triangle_index < num_triangles; triangle_index++)
  {
    Triangle& triangle = triangles[triangle_index];
    for (int i = 0; i < 3; i++)
    {
      const float3& v = triangle.points[i];
      min = float3(std::min(min.x, v.x),
        std::min(min.y, v.y),
        std::min(min.z, v.z));
      max = float3(std::max(max.x, v.x),
        std::max(max.y, v.y),
        std::max(max.z, v.z));
      sum = sum + v;
    }
  }

  float3 size = max - min;
  bounds = BoundingBox(min, size);

  if (num_triangles <= leaf_size)
  {
    this->triangles = std::vector<Triangle>(triangles,
      triangles + num_triangles);
    left = StrongNodePtr();
    right = StrongNodePtr();
  }
  else
  {
    float max_axis = std::max(size.x, std::max(size.y, size.z));
    int sort_axis = (size.x == max_axis ? 0 : (size.y == max_axis ? 1 : 2));
    sortTriangles(triangles, num_triangles, sort_axis);

    int split_index = 0;
    float curr_value = -float_max;
    float split_value = sum(sort_axis) / static_cast<float>(num_triangles * 3);
    while (curr_value < split_value && split_index < num_triangles - 1)
    {
      curr_value = triangles[split_index].minValueOnAxis(sort_axis);
      split_index++;
    }

    left = StrongNodePtr(new BVHTreeNode(triangles, split_index, leaf_size, test_left_leafes));
    if (split_index <= leaf_size)
      test_left_leafes.push_back(left);

    right = StrongNodePtr(new BVHTreeNode(&triangles[split_index],
      num_triangles - split_index, leaf_size, test_left_leafes));
  }
}

BVHTreeNode::~BVHTreeNode()
{
}

void BVHTreeNode::sortTriangles(Triangle* triangles, int num_triangles,
  int sort_axis)
{
  switch (sort_axis)
  {
  case 0:
    std::sort(triangles, triangles + num_triangles, &Triangle::compareByX);
    break;
  case 1:
    std::sort(triangles, triangles + num_triangles, &Triangle::compareByY);
    break;
  case 2:
    std::sort(triangles, triangles + num_triangles, &Triangle::compareByZ);
    break;
  }
}
