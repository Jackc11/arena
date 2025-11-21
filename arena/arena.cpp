#include "arena.hpp"

namespace arena {

static constexpr size_t DEFAULT_ALIGNMENT = 2 * sizeof(void*);

uintptr_t Arena::AlignForward(uintptr_t ptr, uintptr_t alignment) {
  uintptr_t modulo;
  // Is power of two
  if (!((alignment != 0) && ((alignment & (alignment - 1)) == 0))) return 0;

  modulo = ptr & (alignment - 1);

  if (modulo) {
    ptr += alignment - modulo;
  }

  return ptr;
}

bool Arena::Create(size_t capacity) {
  buffer_ = malloc(capacity);
  if (buffer_ == nullptr) {
    printf("Failed to allocate arena memory: %s\n", strerror(errno));
    return false;
  }
  memset(buffer_, 0, capacity);
  size_ = capacity;
  capacity_ = capacity;

  return true;
}

bool Arena::Expand(size_t capacity) {
  buffer_ = realloc(buffer_, capacity);
  if (buffer_ == nullptr) {
    printf("Failed to reallocate memory\n");
    return false;
  }

  size_ = capacity;
  capacity_ = capacity;

  return true;
}

void* Arena::AllocateAligned(ArenaRegion* region, size_t size, size_t alignment) {
  uintptr_t curr_ptr = (uintptr_t)buffer_ + (uintptr_t)offset_;
  uintptr_t aligned_offset = AlignForward(curr_ptr, alignment);
  aligned_offset -= (uintptr_t)buffer_;

  if (aligned_offset + size > size_) return nullptr;

  committed_ += size;
  void* ptr = static_cast<unsigned char*>(buffer_) + aligned_offset;
  region->begin = offset_;
  offset_ = aligned_offset + size;
  region->end = offset_;

  return ptr;
}

void* Arena::Allocate(ArenaRegion* region, size_t size) {
  if (size == 0) return nullptr;
  return AllocateAligned(region, size, DEFAULT_ALIGNMENT);
}

void Arena::Clear() {
  offset_ = 0;
  committed_ = 0;
  memset(buffer_, 0, size_);
}

void Arena::Free() {
  Clear();
  free(buffer_);
  buffer_ = nullptr;
}

} // namespace arena
