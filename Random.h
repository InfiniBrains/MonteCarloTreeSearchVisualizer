#pragma once

#include <random>

std::random_device rd;
std::mt19937 gen(rd());

template <typename T>
requires std::is_integral_v<T>
T random(T min, T max) {
  std::uniform_int_distribution<T> dis(min, max);
  return dis(gen);
}

template <typename T>
requires std::is_floating_point_v<T>
T random(T min, T max) {
  std::uniform_real_distribution<T> dis(min, max);
  return dis(gen);
}