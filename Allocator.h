#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_

#include <limits>
#include <memory>
#include <utility>

template <class T> class Allocator {
  template <void*(std::size_t)> struct new_type;
  template <void(void*)> struct delete_type;

  template <class U> void* _allocate(std::size_t n,
      new_type<U::operator new>*) {
    return U::operator new(n);
  }

  template <class U> void* _allocate(std::size_t n, ...) {
    return ::operator new(n);
  }

  template <class U> void _deallocate(void* p,
      delete_type<U::operator delete>*) {
    U::operator delete(p);
  }

  template <class U> void _deallocate(void* p, ...) {
    ::operator delete(p);
  }
 public:
  typedef T value_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  pointer address(reference x) const {
    return std::addressof(x);
  }

  const_pointer address(const_reference x) const {
    return std::addressof(x);
  }

  pointer allocate(size_type n, const void* hint = nullptr) {
    return reinterpret_cast<pointer>(_allocate<T>(n*sizeof(T), nullptr));
  }

  void deallocate(pointer p, size_type n) {
    _deallocate<T>(p, nullptr);
  }

  size_type max_size() const {
    return std::numeric_limits<size_type>::max();
  }

  template <class U, class... Args> void construct(U* p, Args&&... args) {
    ::new (reinterpret_cast<void*>(p)) U(std::forward<Args>(args)...);
  }

  template <class U> void destroy(U* p) {
    p->~U();
  }
};

#define USE_ALLOCATOR_AS_DEFAULT(type) \
  namespace std { \
    template<> class allocator<type> : public Allocator<type> { \
    }; \
  }\

#endif
