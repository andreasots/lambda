#include "ARB_debug_output_callback.h"

#include <cstdio>

static const char* format_source(GLenum source) {
  switch (source) {
    case GL_DEBUG_SOURCE_API_ARB:
      return "API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:
      return "WINDOW_SYSTEM";
    case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB:
      return "SHADER_COMPILER";
    case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:
      return "THIRD_PARTY";
    case GL_DEBUG_SOURCE_APPLICATION_ARB:
      return "APPLICATION";
    case GL_DEBUG_SOURCE_OTHER_ARB:
      return "OTHER";
    default:
      return nullptr;
  }
}

static const char* format_type(GLenum type) {
  switch (type) {
    case GL_DEBUG_TYPE_ERROR_ARB:
      return "ERROR";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB:
      return "DEPRECATED_BEHAVIOR";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:
      return "UNDEFINED_BEHAVIOR";
    case GL_DEBUG_TYPE_PORTABILITY_ARB:
      return "PORTABILITY";
    case GL_DEBUG_TYPE_PERFORMANCE_ARB:
      return "PERFORMANCE";
    case GL_DEBUG_TYPE_OTHER_ARB:
      return "OTHER";
    default:
      return nullptr;
  }
}

void ARB_debug_output_callback(GLenum source, GLenum type, GLuint, GLenum,
    GLsizei, const char* msg, GLvoid*) {
  std::fprintf(stderr, "OpenGL: %s: %s: %s\n",
      format_source(source), format_type(type), msg);
}
