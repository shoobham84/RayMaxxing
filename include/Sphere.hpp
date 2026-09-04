#pragma once

#include "Hittable.hpp"
#include "Ray.hpp"

template<std::floating_point Tp>
class Sphere : public Hittable<Tp>
{
public:
	using value_type = Tp;
	Sphere(const rtrc::point3& center, Tp radius) 
	: m_Center(center), m_Radius(std::fmax(0, radius)) {}

	bool Hit(const rtrc::ray& r, value_type tmin, value_type tmax, HitRecord& rec) const override {
		rtrc::vec3 OC {m_Center - r.origin()};

		// λ^2 * |d|^2 - λ * 2 * b * OC + |OC|^2 - r ^ 2 = 0
		auto a { r.direction().length_squared() };
		auto h { dot(r.direction(), OC)};
		auto c { OC.length_squared() - m_Radius * m_Radius };

		auto discriminant { h*h - a*c }; 
		if (discriminant < 0) return false;

		auto sqrt_discr { std::sqrt(discriminant) };

		auto root { (h - sqrt_discr) / a};
		if (root <= tmin || root >= tmax) {
			root = (h + sqrt_discr) / a;
			if (root <= tmin || root >= tmax) return false;
		}

		rec.time = root;
		rec.points = r.at(rec.time);
		rec.normal = (rec.points - m_Center) / m_Radius;

		return true;
	}

private:
	rtrc::point3 m_Center;
	value_type m_Radius;
};
