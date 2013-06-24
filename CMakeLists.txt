cmake_minimum_required(VERSION 2.8.2)
project(lambda C CXX)

if(${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR
    ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(JsonCpp REQUIRED)
find_package(assimp REQUIRED)

include (CheckCXXSourceCompiles)
CHECK_CXX_SOURCE_COMPILES(
  "#include <cstddef>\nint main(){std::max_align_t a;}" HAVE_STD_MAX_ALIGN_T)
CHECK_CXX_SOURCE_COMPILES(
  "#include <cstddef>\nint main(){max_align_t a;}" HAVE_MAX_ALIGN_T)
CHECK_CXX_SOURCE_COMPILES("#include <xmmintrin.h>\nint main(){}" HAVE_SSE)
if ("x${HAVE_SSE}" STREQUAL "x")
  message(FATAL_ERROR "No SSE support. Enable SSE support")
endif()

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLUT_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${JSONCPP_INCLUDE_DIRS})
include_directories(${ASSIMP_INCLUDE_DIRS})
include_directories(${CMAKE_BINARY_DIR})
configure_file("${PROJECT_SOURCE_DIR}/config.h.in"
  "${CMAKE_BINARY_DIR}/config.h")

file(GLOB src *.cpp)

add_executable(lambda ${src})
target_link_libraries(lambda ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES}
  ${GLEW_LIBRARIES} ${JSONCPP_LIBRARIES} ${ASSIMP_LIBRARIES})

