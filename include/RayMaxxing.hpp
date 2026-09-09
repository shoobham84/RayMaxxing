#pragma once

#include <cmath>
#include <print>
#include <limits>
#include <memory>
#include <concepts>

constexpr const auto Infinity{ std::numeric_limits<double>::infinity() };
constexpr const auto PI{ 3.1415926535897932385 };

constexpr auto degreeToRad(double degree) {
	return degree * PI / 180.0;
}

#include "Ray.hpp"
#include "Vec3.hpp"
