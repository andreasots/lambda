#ifndef COLOR_H_
#define COLOR_H_

#include <xmmintrin.h>

class Color {
 public:
  Color() = default;
  Color(float r, float g, float b, float a = 1.0f);

 protected:
  __m128 _data;
};

#endif
