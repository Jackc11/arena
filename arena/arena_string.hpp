#ifndef _arena_string_hpp_
#define _arena_string_hpp_

#include "arena.hpp"

#include <string>

namespace arena {

class ArenaString {
public:
  ArenaString()
    : arena_(nullptr)
    , len_(0)
  {}

  ArenaString(Arena* arena)
    : arena_(arena)
    , len_(0)
  {}

  // To create a use "From". Its inspired by rust String::from("")
  static ArenaString From(Arena* arena, const char* str, size_t len);
  static ArenaString From(Arena* arena, const std::string& str);

  // Clear's the region(set's region in arena with zeros) in the arena
  void Clear();
  
  char* str_;
  size_t len_;
  ArenaRegion region_;

private:
  Arena* arena_;
};

} // namespace arena

#endif // _arena_string_hpp_
