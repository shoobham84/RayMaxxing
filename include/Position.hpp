#pragma once

#include "VecBase3.hpp"
#include "Vec3.hpp"

namespace rtrc {

template<std::floating_point Tp>
class Point : public VecBase3<Tp>
{
public:
	using value_type = Tp;
	using VecBase3<value_type>::VecBase3;

	[[nodiscard]] constexpr Point operator-() const {
		return Point(-this->x(), -this->y(), -this->z());
	}

	constexpr Point& operator*=(value_type scalar) {
		(*this)[0] *= scalar;
		(*this)[1] *= scalar;
		(*this)[2] *= scalar;
		return *this;
	}

	constexpr Point& operator/=(value_type scalar) {
		return *this *= static_cast<value_type>(1)/scalar;
	}

	constexpr Point& operator+=(const Vec3<value_type>& vec3) {
		(*this)[0] += vec3[0];
		(*this)[1] += vec3[1];
		(*this)[2] += vec3[2];
		return *this;
	}

	constexpr Point& operator-=(const Vec3<value_type>& vec3) {
		(*this)[0] -= vec3[0];
		(*this)[1] -= vec3[1];
		(*this)[2] -= vec3[2];
		return *this;
	}

	[[nodiscard]] friend constexpr Point<value_type> operator+(const Point& p, const Vec3<value_type>& v) noexcept {
		return Point(p.x() + v.x(), p.y() + v.y(), p.z() + v.z());
	}

	[[nodiscard]] friend constexpr Point<value_type> operator-(const Point& p, const Vec3<value_type>& v) noexcept {
		return Point(p.x() - v.x(), p.y() - v.y(), p.z() - v.z());
	}

	[[nodiscard]] friend constexpr Vec3<value_type> operator-(const Point& p1, const Point& p2) noexcept {
		return Vec3<value_type>(p1.x() - p2.x(), p1.y() - p2.y(), p2.z() - p2.z());
	}
};

using Point3d = Point<double>;
using Point3f = Point<float>;
using point3  = Point3d;


}
