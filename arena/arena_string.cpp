#include "arena_string.hpp"

namespace arena {

ArenaString CreateString(Arena* arena, const char* str, size_t len) {
  ArenaString string(arena);
  string.str_ = static_cast<char*>(arena->Allocate(&string.region_, len + 1));
  memmove(string.str_, str, len + 1);
  string.str_[len] = '\0';

  string.len_ = len;

  return string;
}

ArenaString ArenaString::From(Arena* arena, const char* str, size_t len) {
  return CreateString(arena, str, len);
}

ArenaString ArenaString::From(Arena* arena, const std::string& str) {
  return CreateString(arena, str.data(), str.size());
}

void ArenaString::Clear() {
  memset(
    static_cast<char*>(arena_->GetBuffer()) + region_.begin,
    0,
    len_);
  str_ = nullptr;
}

} // namespace arena
