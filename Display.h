#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <GL/gl.h>

#include <random>

class Color;
class Scene;

class Display {
 public:
  static Display& instance();
  void init(int& argc, char** argv, int w = 300, int h = 300);
  void scene(const Scene*);
  [[noreturn]] void run();

 protected:
  Display() = default;
  Display(Display&) = delete;
  Display& operator=(Display&) = delete;

  void reshape(int, int);
  void draw();
  void idle();
  void update();

  static Display* _instance;
  const Scene* _scene = nullptr;
  int _width = 300, _height = 300, _tex_width = 300, _tex_height = 300;
  GLuint _textures[1];
  Color* _framebuffer = nullptr;
  std::default_random_engine _engine;
};

#endif
