#include "arena_string_test.hpp"

#include <stdio.h>
#include <string.h>
#include <cassert>

#include <arena_string.hpp>

void Test_ArenaStringFromCString() {
  arena::Arena arena;
  const bool res = arena.Create(1024);
  assert(res);

  const char* test_str = "hello, arena string";
  arena::ArenaString astring = arena::ArenaString::From(&arena, test_str, strlen(test_str));

  assert(astring.str_ != nullptr);
  assert(astring.len_ == strlen(test_str));
  assert(strncmp(astring.str_, test_str, astring.len_) == 0);

  arena.Free();

  printf("TestArenaStringFromCString ===================== PASSED\n");
}

void Test_ArenaStringFromStdString() {
  arena::Arena arena;
  assert(arena.Create(1024));

  std::string str = "arena string from std::string";
  arena::ArenaString astring = arena::ArenaString::From(&arena, str);

  assert(astring.str_ != nullptr);
  assert(astring.len_ == str.size());
  assert(strncmp(astring.str_, str.c_str(), astring.len_) == 0);

  arena.Free();

  printf("TestArenaStringFromStdString ===================== PASSED\n");
}

void Test_ArenaStringClear() {
  arena::Arena arena;
  assert(arena.Create(256));

  const char* text = "clear me";
  arena::ArenaString astring = arena::ArenaString::From(&arena, text, strlen(text));
  assert(astring.str_ != nullptr);

  astring.Clear();
  // After clearing, underlying buffer region should be zeroed
  for (size_t i = astring.region_.begin; i < astring.region_.begin + astring.len_; ++i) {
    unsigned char* buffer_bytes = static_cast<unsigned char*>(arena.GetBuffer());
    assert(buffer_bytes[i] == 0);
  }
  assert(astring.str_ == nullptr);

  arena.Free();

  printf("TestArenaStringClear ===================== PASSED\n");
}

void RunArenaStringTests() {
  printf("=== Running Arena Tests ===\n");
  Test_ArenaStringFromCString();
  Test_ArenaStringFromStdString();
  Test_ArenaStringClear();
  printf("=== Finished Arena Tests ===\n\n");
}
