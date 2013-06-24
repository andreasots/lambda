#ifndef ALIGNED_NEW_H_
#define ALIGNED_NEW_H_

#include <cstddef>
#include "std_max_align_t.h"
#include <new>

#ifdef _WIN32
# include <malloc.h>
#elif _POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600
# include <stdlib.h>
#else
# include <memory>
#endif

template <std::size_t align, bool use_new> class aligned_new_helper {
};

template <std::size_t align> class aligned_new_helper<align, false> {
 public:
  void* operator new(std::size_t size) {
#ifdef _WIN32
    void* mem = _aligned_malloc(size, align);
    if (!mem)
      throw std::bad_alloc();
    return mem;
#elif _POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600
    void* mem;
    if (posix_memalign(&mem, align, size) != 0)
      throw std::bad_alloc();
    return mem;
#else
    std::size_t buffer_size = size+align-alignof(std::max_align_t);
    while (true) {
      char* mem = new char[buffer_size];
      char* ret = reinterpret_cast<char*>(
          (reinterpret_cast<std::size_t>(mem)+align)/align*align);
      if (ret+size > mem+buffer_size || mem-ret < sizeof(void*)) {
        delete[] mem;
        buffer_size += align;
        continue;
      }
      *(reinterpret_cast<void**>(ret)-1) = mem;
      return ret;
    }
#endif
  }

  void* operator new[](std::size_t size) {
#ifdef _WIN32
    void* mem = _aligned_malloc(size, align);
    if (!mem)
      throw std::bad_alloc();
    return mem;
#elif _POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600
    void* mem;
    if (posix_memalign(&mem, align, size) != 0)
      throw std::bad_alloc();
    return mem;
#else
    std::size_t buffer_size = size+align-alignof(std::max_align_t);
    while (true) {
      char* mem = new char[buffer_size];
      char* ret = reinterpret_cast<char*>(
          (reinterpret_cast<std::size_t>(mem)+align)/align*align);
      if (ret+size > mem+buffer_size || mem-ret < sizeof(void*)) {
        delete[] mem;
        buffer_size += align;
        continue;
      }
      *(reinterpret_cast<void**>(ret)-1) = mem;
      return ret;
    }
#endif
  }

  void operator delete(void* ptr) {
#if defined(_WIN32) || _POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600
    free(ptr);
#else
    if (ptr)
      delete reinterpret_cast<char*>(*(reinterpret_cast<void**>(ptr)-1));
#endif
  }

  void operator delete[](void* ptr) {
#if defined(_WIN32) || _POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600
    free(ptr);
#else
    if (ptr)
      delete reinterpret_cast<char*>(*(reinterpret_cast<void**>(ptr)-1));
#endif
  }
};

template <std::size_t align> class aligned_new :
    public aligned_new_helper<align, alignof(std::max_align_t) >= align> {
  static_assert(!(align & (align-1)), "Alignment must be a power of 2");
};

#endif
