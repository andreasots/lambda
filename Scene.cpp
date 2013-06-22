#include "Scene.h"

#include <fstream>

#include <json/json.h>
#include "Triangle.h"

Scene::Scene(const std::string& filename) {
  open(filename);
}

void Scene::open(const std::string& filename) {
  Json::Value root;
  {
    Json::Reader reader;
    std::ifstream file(filename);
    if (!reader.parse(file, root))
      throw std::runtime_error(reader.getFormatedErrorMessages());
  }
  if (!root.isConvertibleTo(Json::objectValue))
    throw std::runtime_error("Root not convertible to object.");
  
  if (root.isMember("triangles")) {
  }

  if (root.isMember("meshes")) {
    if (!root["meshes"].isConvertibleTo(Json::arrayValue))
      throw std::runtime_error("Mesh array not an array.");
    for (auto file : root["meshes"])
      std::printf("mesh: '%s'\n", file.asString().c_str());
  }
}

std::array<IntersectData, 4> Scene::intersect(const RayPacket& rays) const {
  std::array<IntersectData, 4> ret;
  for (auto tri: _triangles) {
    std::array<IntersectData, 4> temp = tri.intersect(rays);
    for (int i = 0; i < 4; i++)
      if (temp[i].valid &&
          ((ret[i].valid && temp[i].distance < ret[i].distance) ||
           !ret[i].valid))
        ret[i] = temp[i];
  }
  return ret;
}

IntersectData Scene::intersect(const Ray& ray) const {
  IntersectData ret;
  for (auto tri : _triangles) {
    IntersectData temp = tri.intersect(ray);
    if (temp.valid &&
        ((ret.valid && temp.distance < ret.distance) || !ret.valid))
      ret = temp;
  }
  return ret;
}
