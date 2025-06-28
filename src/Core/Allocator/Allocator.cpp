#include "Allocator.hpp"

ZoneAllocator &GetZoneAllocator() {
  static ZoneAllocator allocator(700 * 1024 * 1024);
  return allocator;
}