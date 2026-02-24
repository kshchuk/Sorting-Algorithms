#pragma once

#include <cstddef>
#include <utility>

namespace sorting {

/** Thread-local stats for comparisons and assignments (used by Counted<T>). */
struct InstrumentationStats {
    size_t comparisons = 0;
    size_t assignments = 0;

    static InstrumentationStats& get() {
        static thread_local InstrumentationStats stats;
        return stats;
    }

    void reset() {
        comparisons = 0;
        assignments = 0;
    }

    size_t total() const { return comparisons + assignments; }
};

/**
 * Wrapper type that counts every comparison (via operators) and every
 * copy/move (ctor and assignment). Use for measuring K = comparisons + assignments.
 */
template <typename T>
class Counted {
public:
    using value_type = T;

    Counted() : value_{} {}
    explicit Counted(T v) : value_(std::move(v)) {}

    Counted(const Counted& other) : value_(other.value_) {
        InstrumentationStats::get().assignments++;
    }
    Counted(Counted&& other) noexcept : value_(std::move(other.value_)) {
        InstrumentationStats::get().assignments++;
    }
    Counted& operator=(const Counted& other) {
        value_ = other.value_;
        InstrumentationStats::get().assignments++;
        return *this;
    }
    Counted& operator=(Counted&& other) noexcept {
        value_ = std::move(other.value_);
        InstrumentationStats::get().assignments++;
        return *this;
    }

    Counted& operator=(const T& v) {
        value_ = v;
        InstrumentationStats::get().assignments++;
        return *this;
    }

    const T& value() const { return value_; }
    T& value() { return value_; }

    bool operator<(const Counted& other) const {
        InstrumentationStats::get().comparisons++;
        return value_ < other.value_;
    }
    bool operator<=(const Counted& other) const {
        InstrumentationStats::get().comparisons++;
        return value_ <= other.value_;
    }
    bool operator>(const Counted& other) const {
        InstrumentationStats::get().comparisons++;
        return value_ > other.value_;
    }
    bool operator>=(const Counted& other) const {
        InstrumentationStats::get().comparisons++;
        return value_ >= other.value_;
    }
    bool operator==(const Counted& other) const {
        InstrumentationStats::get().comparisons++;
        return value_ == other.value_;
    }
    bool operator!=(const Counted& other) const {
        InstrumentationStats::get().comparisons++;
        return value_ != other.value_;
    }

    operator T() const { return value_; }

private:
    T value_;
};

using CountedInt = Counted<int>;
using CountedDouble = Counted<double>;

inline void resetInstrumentation() {
    InstrumentationStats::get().reset();
}

inline size_t getComparisons() {
    return InstrumentationStats::get().comparisons;
}

inline size_t getAssignments() {
    return InstrumentationStats::get().assignments;
}

inline size_t getTotalOperations() {
    return InstrumentationStats::get().total();
}

}  // namespace sorting
