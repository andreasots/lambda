#include <cstdio>
#include <cstdlib>
#include <exception>
#include "Display.h"
#include "Scene.h"

[[noreturn]] int main(int argc, char** argv) {
  try {
    Scene scene(argv[1]);
    Display::instance().init(argc, argv);
    Display::instance().scene(&scene);
    Display::instance().run();
  } catch (const std::exception& e) {
    std::fprintf(stderr, "Error: %s\n", e.what());
    std::exit(1);
  }
}
