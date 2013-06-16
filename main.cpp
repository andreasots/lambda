#include <cstdio>
#include <cstdlib>
#include <exception>
#include "Display.h"

[[noreturn]] int main(int argc, char** argv) {
  try {
    Display::instance().init(argc, argv);
    Display::instance().run();
  } catch (const std::exception& e) {
    std::fprintf(stderr, "Error: %s\n", e.what());
    std::exit(1);
  }
}
