#pragma once

#include "Ray.hpp"
#include <concepts>
#include "RayMaxxing.hpp"

class HitRecord {
public:
	rtrc::point3 Points;
	rtrc::vec3 Normal;
	double Time;
	bool frontFace;
	
	constexpr void setFaceNormal(const rtrc::ray& r, const rtrc::vec3& outward_normal) {
		frontFace = rtrc::dot(r.direction(), outward_normal) < 0;
		Normal = frontFace ? outward_normal : -outward_normal; 
	}
};

class Hittable {
public:
	virtual ~Hittable() = default;

	virtual bool Hit(const rtrc::ray& ray, Interval ray_t, HitRecord& record) const = 0;
};

using hittable = Hittable;
