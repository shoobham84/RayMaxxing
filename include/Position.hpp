#pragma once

#include "VecBase3.hpp"
#include <cmath>
#include "Vec3.hpp"

template<std::floating_point Tp>
class Point : public VecBase3<Tp>
{
public:
	using value_type = Tp;

	Point operator-() const {
		return Point(-(*this).x(), -(*this).y(), -(*this).z());
	}

	value_type length_squared() const {
		return (*this).x() * (*this).x() + (*this).y() * (*this).y() + (*this).z() * (*this).z();
	}

	value_type length() const {
		return std::sqrt(length_squared());
	}

	Point& operator*=(value_type scalar) {
		(*this)[0] *= scalar;
		(*this)[1] *= scalar;
		(*this)[2] *= scalar;
		return *this;
	}

	Point& operator/=(value_type scalar) {
		return *this *= static_cat<value_type>(1)/scalar;
	}

	Point& operator+=(const Vec3<value_type>& vec3) {
		(*this)[0] += vec3[0];
		(*this)[1] += vec3[1];
		(*this)[2] += vec3[2];
		return *this;
	}
};
