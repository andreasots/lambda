#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <array>

#include <xmmintrin.h>

#include "aligned_new.h"
#include "Allocator.h"

struct IntersectData;
class Ray;
class RayPacket;

class alignas(16) Triangle : public aligned_new<16> {
 public:
  class Raw : public std::array<__m128, 3>, public aligned_new<16> {
  };

  Triangle();
  std::array<IntersectData, 4> intersect(const RayPacket&) const;
  IntersectData intersect(const Ray&) const;

 private:
  __m128 _A, _B, _C;
};

USE_ALLOCATOR_AS_DEFAULT(Triangle)
USE_ALLOCATOR_AS_DEFAULT(Triangle::Raw)

#endif
