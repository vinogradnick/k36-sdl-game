#pragma once
#include <cassert>
#include <cstddef>
#include <cstdint>

class ZoneAllocator {
public:
  size_t m_size = 0;
  explicit ZoneAllocator(size_t maxSize) : m_size(maxSize) {
    m_base = new uint8_t[maxSize];
    m_head = m_base;
  }

  ~ZoneAllocator() { delete[] m_base; }

  void *allocate(size_t size, size_t alignment = alignof(std::max_align_t)) {
    uintptr_t current = reinterpret_cast<uintptr_t>(m_head);
    uintptr_t aligned = (current + alignment - 1) & ~(alignment - 1);
    uintptr_t end = aligned + size;

    assert(end <= reinterpret_cast<uintptr_t>(m_base + m_size) &&
           "ZoneAllocator: Out of memory!");

    m_head = reinterpret_cast<uint8_t *>(end);
    return reinterpret_cast<void *>(aligned);
  }

  void reset() { m_head = m_base; }

  size_t used() const { return static_cast<size_t>(m_head - m_base); }

private:
  uint8_t *m_base = nullptr;
  uint8_t *m_head = nullptr;
};

template <typename T> class ZoneBox {
public:
  explicit ZoneBox(ZoneAllocator &allocator)
      : ptr_(new(allocator.allocate(sizeof(T), alignof(T))) T()) {}

  ~ZoneBox() {
    ptr_->~T(); // Явно вызываем деструктор
  }

  T *get() { return ptr_; }
  T &operator*() { return *ptr_; }
  T *operator->() { return ptr_; }

private:
  T *ptr_;
};

template <typename T> struct ZoneSTLAllocator {

  ZoneAllocator *zone;

  explicit ZoneSTLAllocator(ZoneAllocator *z) : zone(z) {}

  template <typename U>
  explicit ZoneSTLAllocator(const ZoneSTLAllocator<U> &other)
      : zone(other.zone) {}

  T *allocate(std::size_t n) {
    return static_cast<T *>(zone->allocate(n * sizeof(T), alignof(T)));
  }

  void deallocate(T *, std::size_t) {}
};

ZoneAllocator &GetSceneAllocator();