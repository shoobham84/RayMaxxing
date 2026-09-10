#pragma once

#include <cmath>
#include <print>
#include <memory>
#include <concepts>
#include "Interval.hpp"

constexpr const auto PI{ 3.1415926535897932385 };

constexpr auto degreeToRad(double degree) {
	return degree * PI / 180.0;
}

#include "Ray.hpp"
#include "Vec3.hpp"
