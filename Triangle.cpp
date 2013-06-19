#include "Triangle.h"
#include "Ray.h"
#include "Scene.h"
#include <stdexcept>

Triangle::Triangle() {
  throw std::runtime_error("Not implemented");
}

std::array<IntersectData, 4> Triangle::intersect(const RayPacket&) const {
  throw std::runtime_error("Not implemented");
}

IntersectData Triangle::intersect(const Ray&) const {
  throw std::runtime_error("Not implemented");
}
