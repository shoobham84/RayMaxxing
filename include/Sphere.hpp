#pragma once

#include "Hittable.hpp"
#include "Ray.hpp"

class Sphere : public Hittable
{
public:
	Sphere(const rtrc::point3& center, double radius) 
	: m_Center(center), m_Radius(std::fmax(0.0, radius)) {}

	bool Hit(const rtrc::ray& r, double tmin, double tmax, HitRecord& rec) const override {
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

		rec.Time = root;
		rec.Points = r.at(rec.Time);
		rtrc::vec3 outwardNormal { (rec.Points - m_Center )/ m_Radius};
		rec.setFaceNormal(r, outwardNormal);

		return true;
	}

private:
	rtrc::point3 m_Center;
	double m_Radius;
};

using sphere = Sphere;
