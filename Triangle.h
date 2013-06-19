#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <array>

#include <xmmintrin.h>

struct IntersectData;
class Ray;
class RayPacket;

class Triangle {
 public:
  Triangle();
  std::array<IntersectData, 4> intersect(const RayPacket&) const;
  IntersectData intersect(const Ray&) const;

 private:
  __m128 _A, _B, _C;
};

#endif
