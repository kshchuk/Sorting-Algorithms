#pragma once

/**
 * Include this header ONLY when running the experiment to measure V (memory).
 * Overloads global operator new[]/delete[] and tracks bytes allocated during sort().
 */

#include <cstddef>
#include <cstdlib>
#include <new>

namespace experiment {

struct MemoryTracker {
    static MemoryTracker& get() {
        static thread_local MemoryTracker tracker;
        return tracker;
    }

    std::size_t current_bytes = 0;
    std::size_t peak_bytes = 0;

    void reset() {
        current_bytes = 0;
        peak_bytes = 0;
    }

    void add(std::size_t size) {
        current_bytes += size;
        if (current_bytes > peak_bytes)
            peak_bytes = current_bytes;
    }

    void subtract(std::size_t size) {
        current_bytes -= size;
    }

    std::size_t getPeakBytes() const { return peak_bytes; }
};

}  // namespace experiment

// Global overloads - include this header only in experiment build.
inline void* operator new(std::size_t size) {
    void* p = std::malloc(size);
    if (!p)
        throw std::bad_alloc{};
    experiment::MemoryTracker::get().add(size);
    return p;
}

inline void operator delete(void* p) noexcept {
    std::free(p);
}

inline void* operator new[](std::size_t size) {
    void* p = std::malloc(size);
    if (!p)
        throw std::bad_alloc{};
    experiment::MemoryTracker::get().add(size);
    return p;
}

inline void operator delete[](void* p) noexcept {
    std::free(p);
}

#if __cplusplus >= 201402L
inline void operator delete(void* p, std::size_t size) noexcept {
    experiment::MemoryTracker::get().subtract(size);
    std::free(p);
}
inline void operator delete[](void* p, std::size_t size) noexcept {
    experiment::MemoryTracker::get().subtract(size);
    std::free(p);
}
#endif
