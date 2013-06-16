#ifndef COLOR_H_
#define COLOR_H_

class Color {
 public:
  Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);

 protected:
  float _data[4];
};

#endif
