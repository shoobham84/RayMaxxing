#pragma once

#include <limits>

constexpr const auto Infinity{ std::numeric_limits<double>::infinity() };

class Interval {
public:
	double Min, Max;

	constexpr Interval() 
	: Min(-Infinity), Max(Infinity) {}

	constexpr Interval(double min, double max) 
	: Min(min), Max(max) {}

	[[nodiscard]] constexpr double size() {
		return Max - Min;
	}

	[[nodiscard]] constexpr bool contains(double x) {
		return Min <= x && Max >= x;
	}

	[[nodiscard]] constexpr bool surrounds(double x) {
		return Min < x && Max > x;
	}

	[[nodiscard]] constexpr double clamp(double x) const {
		if (x < Min) return Min;
		else if (x > Max) return Max;
		return x;
	}

	static const Interval Empty, Universe;
};

inline const Interval Interval::Empty = Interval(Infinity, -Infinity);
inline const Interval Interval::Universe = Interval(-Infinity, +Infinity);

