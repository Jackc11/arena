#ifndef _arena_hpp_
#define _arena_hpp_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace arena {

struct ArenaRegion {
  size_t begin;
  size_t end;  
};

class Arena {
public:
  Arena() = default;

  bool Create(size_t capacity);
  bool Expand(size_t new_cap);
  void* AllocateAligned(ArenaRegion* region, size_t size, size_t alignment);
  void* Allocate(ArenaRegion* region, size_t size);
  void Clear();
  void Free();

  inline void* GetBuffer() { return buffer_; }
  inline size_t GetSize() { return size_; }
  inline size_t GetCapacity() { return capacity_; }

private:
  static uintptr_t AlignForward(uintptr_t ptr, uintptr_t alignment);

  void* buffer_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;
  size_t offset_ = 0;
  size_t committed_ = 0;
};

} // namespace arena

#endif // _arena_hpp_
