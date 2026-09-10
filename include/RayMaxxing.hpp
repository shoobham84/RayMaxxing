#pragma once

#include <cmath>
#include <print>
#include <memory>
#include <concepts>
#include "Interval.hpp"
#include <random>

constexpr const auto PI{ 3.1415926535897932385 };

constexpr auto degreeToRad(double degree) {
	return degree * PI / 180.0;
}

constexpr double randomDouble() {
	static std::uniform_real_distribution<double> distribution(0, 1.0);
	static std::mt19937 mt;
	return distribution(mt);
}

constexpr double randomDouble(double min, double max) {
	static std::uniform_real_distribution<double> distribution(min, max);
	static std::mt19937 mt;
	return distribution(mt);
}

#include "Ray.hpp"
#include "Vec3.hpp"
