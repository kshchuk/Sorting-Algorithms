#pragma once

#include <vector>
#include <random>
#include <cmath>

namespace bench_data {

inline std::mt19937& getGenerator() {
    static std::mt19937 gen(42);
    return gen;
}

// --- Асимптотичні (крайні випадки) ---

template <typename T>
std::vector<T> generateAsymptoticSorted(int n) {
    std::vector<T> arr(n);
    for (int i = 0; i < n; ++i)
        arr[i] = static_cast<T>(i);
    return arr;
}

template <typename T>
std::vector<T> generateAsymptoticReverseSorted(int n) {
    std::vector<T> arr(n);
    for (int i = 0; i < n; ++i)
        arr[i] = static_cast<T>(n - 1 - i);
    return arr;
}

template <typename T>
std::vector<T> generateAsymptoticConstant(int n, T value = T{0}) {
    return std::vector<T>(n, value);
}

// --- Рівномірний розподіл ---

inline std::vector<int> generateUniform(int n, int a, int b) {
    std::vector<int> arr(n);
    std::uniform_int_distribution<int> dist(a, b);
    auto& gen = getGenerator();
    for (int i = 0; i < n; ++i)
        arr[i] = dist(gen);
    return arr;
}

inline std::vector<double> generateUniform(int n, double a, double b) {
    std::vector<double> arr(n);
    std::uniform_real_distribution<double> dist(a, b);
    auto& gen = getGenerator();
    for (int i = 0; i < n; ++i)
        arr[i] = dist(gen);
    return arr;
}

inline std::vector<int> generateUniformInt(int n) {
    return generateUniform(n, 0, 2 * n);
}

inline std::vector<double> generateUniformDouble(int n) {
    return generateUniform(n, 0.0, 1.0);
}

// --- Нормальний розподіл ---

inline std::vector<int> generateNormal(int n, double mean, double stddev) {
    std::vector<int> arr(n);
    std::normal_distribution<double> dist(mean, stddev);
    auto& gen = getGenerator();
    for (int i = 0; i < n; ++i)
        arr[i] = static_cast<int>(std::round(dist(gen)));
    return arr;
}

inline std::vector<double> generateNormalDouble(int n, double mean = 0.5, double stddev = 0.2) {
    std::vector<double> arr(n);
    std::normal_distribution<double> dist(mean, stddev);
    auto& gen = getGenerator();
    for (int i = 0; i < n; ++i)
        arr[i] = dist(gen);
    return arr;
}

inline std::vector<int> generateNormalInt(int n) {
    return generateNormal(n, n / 2.0, n / 6.0);
}

/** Обгортки для бенчмарків (виклик з одним аргументом) */
inline std::vector<int> generateAsymptoticReverseSortedInt(int n) {
    return generateAsymptoticReverseSorted<int>(n);
}

}  // namespace bench_data
