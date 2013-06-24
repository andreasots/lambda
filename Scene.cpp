#include "Scene.h"

#include <fstream>

#include <json/json.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Triangle.h"

static __m128 json_point(const Json::Value& point) {
  alignas(16) float values[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  for (int i = 0; i < std::min<std::size_t>(4, point.size()); i++)
    values[i] = point[i].asDouble();
  return _mm_load_ps(values);
}

static Triangle::Raw json_triangle(const Json::Value& triangle) {
  Triangle::Raw ret;
  if (triangle.size() != 3)
    throw std::runtime_error("not a triangle");
  for (int i = 0; i < 3; i++) {
    if (!triangle[i].isConvertibleTo(Json::arrayValue))
      throw std::runtime_error("not a point");
    ret[i] = json_point(triangle[i]);
  }
  return ret;
}

static void assimp_loader(const std::string& file,
    std::vector<Triangle::Raw>& triangles) {
   Assimp::Importer importer;
   importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE,
       aiPrimitiveType_POINT | aiPrimitiveType_LINE);
   importer.SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS,
       aiComponent_NORMALS | aiComponent_TANGENTS_AND_BITANGENTS |
       aiComponent_TEXCOORDS | aiComponent_BONEWEIGHTS |
       aiComponent_ANIMATIONS | aiComponent_TEXTURES | aiComponent_LIGHTS |
       aiComponent_CAMERAS);
   const aiScene* scene = importer.ReadFile(file,
       aiProcess_Triangulate | aiProcess_PreTransformVertices |
       aiProcess_FindDegenerates | aiProcess_OptimizeMeshes |
       aiProcess_OptimizeGraph | aiProcess_RemoveComponent |
       aiProcess_SortByPType);
}

Scene::Scene(const std::string& filename) {
  open(filename);
}

void Scene::open(const std::string& filename) {
  std::vector<Triangle::Raw> triangles;
  Json::Value root;
  {
    Json::Reader reader;
    std::ifstream file(filename);
    if (!reader.parse(file, root))
      throw std::runtime_error(reader.getFormatedErrorMessages());
  }

  if (!root.isConvertibleTo(Json::objectValue))
    throw std::runtime_error("Root not convertible to object.");

  if (root.isMember("scene")) {
    if (!root["scene"].isConvertibleTo(Json::arrayValue))
      throw std::runtime_error("Scene not convertible to array");
    for (auto object : root["scene"]) {
      if (!object.isConvertibleTo(Json::objectValue))
        throw std::runtime_error("Object not convertible to object");
      if (object.isMember("material"))
        if (!object["material"].isConvertibleTo(Json::stringValue))
          throw std::runtime_error("Material name not convertible to string");
        std::printf("Default material: %s\n",
            object["material"].asString().c_str());
      if (object.isMember("triangles")) {
        if (!object["triangles"].isConvertibleTo(Json::arrayValue))
          throw std::runtime_error("Triangle data not convertible to array");
        for (auto triangle : object["triangles"]) {
          if (triangle.isConvertibleTo(Json::arrayValue))
            triangles.push_back(json_triangle(triangle));
          else if (triangle.isConvertibleTo(Json::stringValue))
            assimp_loader(triangle.asString(), triangles);
          else
            throw std::runtime_error("Triangle not convertible to array "
                "nor a string");
        }
      }
    }
  } else {
    std::fprintf(stderr, "Warning: empty scene");
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
