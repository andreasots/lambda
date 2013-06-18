#include "Color.h"

#include <xmmintrin.h>

Color::Color(float r, float g, float b, float a)
  : _data(_mm_set_ps(a, b, g, r)) {
}
