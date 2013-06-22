#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>

#include <GL/glew.h>
#include <GL/glut.h>

#include "ARB_debug_output_callback.h"
#include "Color.h"
#include "Display.h"
#include "Scene.h"

Display* Display::_instance = nullptr;

Display& Display::instance() {
  if (!_instance)
    _instance = new Display;
  return *_instance;
}

void Display::init(int& argc, char** argv, int w, int h) {
  _tex_width = _width = w;
  _tex_height = _height = h;

  _framebuffer = new Color[_tex_width*_tex_height];

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(w, h);
  glutCreateWindow(argv[0]);

  {
    GLenum error;
    if ((error = glewInit()) != GLEW_OK)
      std::fprintf(stderr, "GLEW error: %s\n", glewGetErrorString(error));
    else if (GLEW_ARB_debug_output) {
      std::printf("Enabling GL_ARB_debug_output\n");
      glDebugMessageCallbackARB(ARB_debug_output_callback, nullptr);
    }
  }
  
  glutReshapeFunc([](int w, int h){_instance->reshape(w, h);});
  glutDisplayFunc([](){_instance->draw();});
  glutIdleFunc([](){_instance->idle();});

  glGenTextures(1, _textures);
  glBindTexture(GL_TEXTURE_RECTANGLE, _textures[0]);
  glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RGBA, _tex_width, _tex_height, 0,
      GL_RGBA, GL_FLOAT, nullptr);
  glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  {
    std::random_device device;
    std::uniform_int_distribution<decltype(_engine)::result_type> distrib;
    _engine.seed(distrib(device));
  } 

  update();
}

void Display::scene(const Scene* scene) {
  _scene = scene;
}

[[noreturn]] void Display::run() {
  glutMainLoop();
  // GLUT documentation states that glutMainLoop will not return but freeglut
  // doesn't declare it with the noreturn attribute
  std::exit(0);
}

void Display::reshape(int w, int h) {
  _width = w;
  _height = h;
  glViewport(0, 0, w, h);
}

void Display::draw() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, _width, _height, 0, 0, 1);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT);

  glEnable(GL_TEXTURE_RECTANGLE);
  glBindTexture(GL_TEXTURE_RECTANGLE, _textures[0]);

  float x_offset = 0.0f, y_offset = 0.0f,
        width = _tex_width, height = _tex_height;
  if (height*_width/width > _height) {
    width = _height*width/height;
    height = _height;
    x_offset = (_width-width)/2;
  } else {
    height = height*_width/width;
    width = _width;
    y_offset = (_height-height)/2;
  }

  glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex2f(x_offset, y_offset);
    
    glTexCoord2i(_tex_width, 0);
    glVertex2f(x_offset+width, y_offset);
    
    glTexCoord2i(_tex_width, _tex_height);
    glVertex2f(x_offset+width, y_offset+height);
   
    glTexCoord2i(0, _tex_height);
    glVertex2i(x_offset, y_offset+height);
  glEnd();

  glutSwapBuffers();
}

void Display::update() {
  glutTimerFunc(40, [](int){_instance->update();}, 0);
  glBindTexture(GL_TEXTURE_RECTANGLE, _textures[0]);
  glTexSubImage2D(GL_TEXTURE_RECTANGLE, 0, 0, 0, _tex_width, _tex_height,
      GL_RGBA, GL_FLOAT, _framebuffer);
  glutPostRedisplay();
}

void Display::idle() {
  std::uniform_real_distribution<float> distrib;
  for (int i = 0; i < _tex_width*_tex_height; i++)
    _framebuffer[i] = Color(distrib(_engine), distrib(_engine), distrib(_engine));
}
