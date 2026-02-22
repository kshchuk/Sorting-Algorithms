#pragma once

/**
 * @file strategy.hpp
 * @brief SortStrategy and SortContext for the strategy pattern.
 */

namespace sorting {

/**
 * @class SortStrategy
 * @brief Abstract base class for sorting strategies.
 */
template <typename T>
class SortStrategy {
public:
    virtual void sort(T* arr, int size) = 0;
    virtual ~SortStrategy() = default;
};

/**
 * @class SortContext
 * @brief Context class for sorting.
 */
template <typename T>
class SortContext {
private:
    SortStrategy<T>* strategy;
public:
    explicit SortContext(SortStrategy<T>* strategy) : strategy(strategy) {}

    void set_strategy(SortStrategy<T>* strategy) {
        this->strategy = strategy;
    }

    void sort(T* arr, int size) {
        strategy->sort(arr, size);
    }
};

}  // namespace sorting
