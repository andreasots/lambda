#include <cstdio>
#include <cstdlib>
#include <exception>
#include "Display.h"
#include "Scene.h"

[[noreturn]] int main(int argc, char** argv) {
  try {
    Display::instance().init(argc, argv);
    if (argc != 2)
      throw std::runtime_error("Wrong number of arguments");
    Scene scene(argv[1]);
    Display::instance().scene(&scene);
    Display::instance().run();
  } catch (const std::exception& e) {
    std::fprintf(stderr, "Error: %s\n", e.what());
    std::exit(1);
  }
}
