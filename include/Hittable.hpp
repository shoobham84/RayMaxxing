#pragma once

#include "Ray.hpp"
#include <concepts>

class HitRecord {
public:
	rtrc::point3 Points;
	rtrc::vec3 Normal;
	double Time;
	bool frontFace;
	
	void setFaceNormal(const rtrc::ray& r, const rtrc::vec3& outward_normal) {
		frontFace = rtrc::dot(r.direction(), outward_normal) < 0;
		Normal = frontFace ? outward_normal : -outward_normal; 
	}
};

template<std::floating_point Tp>
class Hittable {
public:
	virtual ~Hittable() = default;

	virtual bool Hit(const rtrc::Ray<Tp>&, double time_min, double time_max, HitRecord& record) const = 0;
};
