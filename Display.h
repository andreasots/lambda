#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <GL/gl.h>

class Color;

class Display {
 public:
  static Display& instance();
  void init(int& argc, char** argv, int w = 300, int h = 300);
  [[noreturn]] void run();

  void pixels(int x, int y, int w, int h, Color* pixels);
  void redisplay();
  
 protected:
  Display() = default;
  Display(Display&) = delete;
  Display& operator=(Display&) = delete;

  void reshape(int, int);
  void draw();
  void idle();

  static Display* _instance;
  int _width = 300, _height = 300, _tex_width = 300, _tex_height = 300;
  GLuint _textures[1];
};

#endif
