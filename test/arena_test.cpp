#include "arena_test.hpp"

#include <stdio.h>
#include <cassert>

#include <arena.hpp>

void Test_CreateAndFree() {
  arena::Arena a;
  bool created = a.Create(1024);
  assert(created);
  assert(a.GetBuffer() != nullptr);
  assert(a.GetCapacity() == 1024);
  a.Free();
  assert(a.GetBuffer() == nullptr);
  printf("TestCreateAndFree ===================== PASSED\n");
}

void Test_AllocationAndClear() {
  arena::Arena a;
  a.Create(128);
  arena::ArenaRegion region = {};
  void* ptr1 = a.Allocate(&region, 32);
  assert(ptr1 != nullptr);
  assert(region.begin == 0);
  assert(region.end == region.begin + 32);

  void* ptr2 = a.Allocate(&region, 64);
  assert(ptr2 != nullptr);
  assert(region.begin >= 32);
  assert(region.end == region.begin + 64);

  // Allocation that exceeds capacity returns nullptr
  void* ptr3 = a.Allocate(&region, 128);
  assert(ptr3 == nullptr);

  a.Clear();
  assert(a.GetBuffer() != nullptr);
  void* ptr4 = a.Allocate(&region, 16);
  assert(ptr4 != nullptr);
  
  a.Free();

  printf("TestAllocationAndClear ===================== PASSED\n");
}

void Test_AllocateAligned() {
  arena::Arena a;
  a.Create(256);
  arena::ArenaRegion region = {};

  void* ptr = a.AllocateAligned(&region, 16, 16);
  assert(ptr != nullptr);
  assert(reinterpret_cast<uintptr_t>(ptr) % 16 == 0);

  void* ptr2 = a.AllocateAligned(&region, 32, 32);
  assert(ptr2 != nullptr);
  assert(reinterpret_cast<uintptr_t>(ptr2) % 32 == 0);

  void* ptr3 = a.AllocateAligned(&region, 200, 64);
  assert(ptr3 == nullptr); // Not enough space

  a.Free();
  printf("TestAllocateAligned ===================== PASSED\n");
}

void Test_Expand() {
  arena::Arena a;
  a.Create(64);
  arena::ArenaRegion region = {};
  void* ptr1 = a.Allocate(&region, 32);
  assert(ptr1 != nullptr);

  bool expanded = a.Expand(128);
  assert(expanded);
  assert(a.GetCapacity() == 128);

  void* ptr2 = a.Allocate(&region, 64);
  assert(ptr2 != nullptr);

  a.Free();

  printf("TestExpand ===================== PASSED\n");
}

void Test_AlignForward() {
  // Using reflection because AlignForward is private. 
  // This is replicate of its logic here for a test:
  auto align_forward = [](uintptr_t ptr, uintptr_t alignment) -> uintptr_t {
    if (!((alignment != 0) && ((alignment & (alignment - 1)) == 0))) return 0;
    uintptr_t modulo = ptr & (alignment - 1);
    if (modulo) ptr += alignment - modulo;
    return ptr;
  };

  assert(align_forward(1000, 16) % 16 == 0);
  assert(align_forward(1024, 64) == 1024);
  assert(align_forward(1025, 64) % 64 == 0);
  assert(align_forward(1000, 7) == 0); // Not power of two returns 0
  printf("TestAlignForward ===================== PASSED\n");
}

void RunArenaTests() {
  printf("=== Running Arena Tests ===\n");
  Test_CreateAndFree();
  Test_AllocationAndClear();
  Test_AllocateAligned();
  Test_Expand();
  Test_AlignForward();
  printf("=== Finished Arena Tests ===\n\n");
}
