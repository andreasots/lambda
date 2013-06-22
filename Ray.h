#ifndef RAY_H_
#define RAY_H_

#include <xmmintrin.h>

struct alignas(16) Ray {
  __m128 origin, dir;
};

struct alignas(16) RayPacket {
  __m128 origin_x, origin_y, origin_z;
  __m128 padding;
  __m128 dir_x, dir_y, dir_z;
  __m128 valid;
};

#endif
