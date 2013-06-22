#ifndef STD_MAX_ALIGN_T_H_
#define STD_MAX_ALIGN_T_H_

#include <config.h>

#ifdef HAVE_MAX_ALIGN_T
# include <cstddef>
namespace std {
  using ::max_align_t;
}
#elif !defined(HAVE_STD_MAX_ALIGN_T)
#include <type_traits>
namespace std {
  typedef std::conditional<(alignof(long long) > alignof(long double)),
          long long, long double>::type max_align_t;
}
#endif

#endif
