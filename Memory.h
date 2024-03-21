#pragma once

#include <memory>
#include <unordered_set>

// rename "std::shared_ptr<T>" to shared<T>
template <typename T>
using shared = std::shared_ptr<T>;

// rename "std::unique_ptr<T>" to unique<T>
template <typename T>
using unique = std::unique_ptr<T>;

// rename "std::weak_ptr<T>" to weak<T>
template <typename T>
using weak = std::weak_ptr<T>;

// rename "std::make_shared<T>" to make_shared<T>
template <typename T, typename... Args>
requires std::constructible_from<T, Args...>
shared<T> make_shared(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

// rename "std::make_unique<T>" to make_unique<T>
template <typename T, typename... Args>
requires std::constructible_from<T, Args...>
unique<T> make_unique(Args&&... args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

// rename "std::unordered_set<T>" to uset<T>
template <typename T>
using uset = std::unordered_set<T>;