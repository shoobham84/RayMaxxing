#pragma once

#include <limits>

constexpr const auto Infinity{ std::numeric_limits<double>::infinity() };

class Interval {
public:
	double Min, Max;

	Interval() 
	: Min(-Infinity), Max(Infinity) {}

	Interval(double min, double max) 
	: Min(min), Max(max) {}

	double size() {
		return Max - Min;
	}

	bool contains(double x) {
		return Min <= x && Max >= x;
	}

	bool surrounds(double x) {
		return Min < x && Max > x;
	}

	static const Interval Empty, Universe;
};

inline const Interval Interval::Empty = Interval(Infinity, -Infinity);
inline const Interval Interval::Universe = Interval(-Infinity, +Infinity);

