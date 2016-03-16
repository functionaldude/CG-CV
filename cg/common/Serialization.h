#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/archives/portable_binary.hpp>
//#include <cereal/archives/json.hpp>
#include <fstream>
#include "Scene.h"
#include "BVHTree.h"
#include "BVHTreeNode.h"
#include "BoundingBox.h"
#include "vector.h"
#include "Triangle.h"

template<class Archive>
void serialize(Archive & archive, Scene& scene)
{
  archive(scene.bvh_tree, scene.materials, scene.area_lights);
}

template<class Archive>
void serialize(Archive & archive, Material& m)
{
  archive(m.ambient.x, m.ambient.y, m.ambient.z,
    m.diffuse.x, m.diffuse.y, m.diffuse.z,
    m.specular.x, m.specular.y, m.specular.z,
    m.emissive.x, m.emissive.y, m.emissive.z,
    m.shininess, m.reflective, m.density, m.transparent);
}

template<class Archive>
void serialize(Archive & archive, BVHTree& tree)
{
  archive(tree.root, tree.test_leaf_nodes);
}

template<class Archive>
void serialize(Archive & archive, BVHTreeNode& node)
{
  archive(node.left, node.right, node.bounds, node.triangles);
}

template<class Archive>
void serialize(Archive & archive, BoundingBox& bb)
{
  archive(bb.position.x, bb.position.y, bb.position.z,
    bb.size.x, bb.size.y, bb.size.z);
}

template<class Archive>
void serialize(Archive & archive, Triangle& t)
{
  archive(t.points[0].x, t.points[0].y, t.points[0].z,
    t.points[1].x, t.points[1].y, t.points[1].z,
    t.points[2].x, t.points[2].y, t.points[2].z, 
    t.normals[0].x, t.normals[0].y, t.normals[0].z,
    t.normals[1].x, t.normals[1].y, t.normals[1].z,
    t.normals[2].x, t.normals[2].y, t.normals[2].z,
    t.triangle_normal.x, t.triangle_normal.y, t.triangle_normal.z,
    t.material_index);
}

void serializeToFile(const std::string& filename, const Scene& scene)
{
  std::ofstream archive_ofs(filename, std::ios::binary);
  cereal::PortableBinaryOutputArchive archive(archive_ofs);
  //cereal::JSONOutputArchive archive(archive_ofs);
  archive(scene);
}

void serializeFromFile(const std::string& filename, Scene& scene)
{
  std::ifstream archive_ifs(filename, std::ios::binary);
  cereal::PortableBinaryInputArchive archive(archive_ifs);
  archive(scene);
}
