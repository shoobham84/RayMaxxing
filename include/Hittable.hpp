#pragma once

#include "Ray.hpp"
#include <concepts>

class HitRecord {
public:
	rtrc::point3 points;
	rtrc::vec3 normal;
	double time;
};

template<std::floating_point Tp>
class Hittable {
public:
	virtual ~Hittable() = default;

	virtual bool Hit(const rtrc::Ray<Tp>&, double time_min, double time_max, HitRecord& record) const = 0;
};
