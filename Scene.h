#ifndef SCENE_H_
#define SCENE_H_

#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include <xmmintrin.h>

class Material;
class Ray;
class RayPacket;
#include "Triangle.h"

struct alignas(16) IntersectData {
  IntersectData()
    : valid(false) {
  }

  std::uint32_t valid;
  float distance, u, v;
  __m128 normal;
  const Material* mat;
};

class Scene {
 public: 
  Scene(const std::string&);
  void open(const std::string&);

  std::array<IntersectData, 4> intersect(const RayPacket&) const;
  IntersectData intersect(const Ray&) const;

 private:
  std::vector<Triangle> _triangles;
};

#endif
