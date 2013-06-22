#ifndef COLOR_H_
#define COLOR_H_

#include <xmmintrin.h>

#include "aligned_new.h"

class alignas(16) Color : public aligned_new<16> {
 public:
  Color() = default;
  Color(float r, float g, float b, float a = 1.0f);

 protected:
  __m128 _data;
};

#endif
