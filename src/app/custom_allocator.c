#include <cstddef>
#include <cstdio>

void *__real_malloc(size_t size);

void *__wrap_malloc(size_t size) {
  void *ptr = __real_malloc(size);
  // printf("malloc(%ld) = %p\n", size, ptr);
  return ptr;
}
