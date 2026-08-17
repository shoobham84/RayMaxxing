#pragma once

#include "VecBase3.hpp"
#include <cmath>

namespace rtrc {

template<std::floating_point Tp>
class Vec3 : public VecBase3<Tp>
{
public:
	using value_type = Tp;
	using VecBase3<value_type>::VecBase3;

	[[nodiscard]] constexpr value_type length_squared() const {
		return this->x() * this->x() + this->y() * this->y() + this->z() * this->z();
	}

	[[nodiscard]] constexpr value_type length() const {
		return std::sqrt(length_squared());
	}

	constexpr Vec3& operator+=(const Vec3& v) noexcept {
		(*this)[0] += v[0];
		(*this)[1] += v[1];
		(*this)[2] += v[2];
		return *this;
	}

	constexpr Vec3& operator-=(const Vec3& v) noexcept {
		(*this)[0] -= v[0];
		(*this)[1] -= v[1];
		(*this)[2] -= v[2];
		return *this;
	}

	constexpr Vec3& operator*=(const value_type scalar) noexcept {
		(*this)[0] *= scalar;
		(*this)[1] *= scalar;
		(*this)[2] *= scalar;
		return *this;
	}

	constexpr Vec3& operator/=(const value_type scalar) {
		return *this *= static_cast<value_type>(1) / scalar;
	}

};

template <std::floating_point Tp>
[[nodiscard]] constexpr Vec3<Tp> operator+(const Vec3<Tp>& u, const Vec3<Tp>& v) noexcept {
	return Vec3<Tp>(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

template <std::floating_point Tp>
[[nodiscard]] constexpr Vec3<Tp> operator-(const Vec3<Tp>& u, const Vec3<Tp>& v) noexcept{
	return Vec3<Tp>(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

template <std::floating_point Tp>
[[nodiscard]] constexpr Vec3<Tp> operator*(const Vec3<Tp>& u, const Vec3<Tp>& v) noexcept {
	return Vec3<Tp>(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

template <std::floating_point Tp>
[[nodiscard]] constexpr Vec3<Tp> operator/(const Vec3<Tp>& vec3, Tp val) {
	return (static_cast<Tp>(1)/val) * vec3;
}

template<std::floating_point Tp>
[[nodiscard]] constexpr Vec3<Tp> operator*(Tp scalar, const Vec3<Tp>& vec3) noexcept {
	return Vec3<Tp>(scalar * vec3.x(), scalar * vec3.y(), scalar*vec3.z());
}

template <std::floating_point Tp>
[[nodiscard]] constexpr Vec3<Tp> operator*(const Vec3<Tp>& vec3, Tp val) noexcept {
	return val * vec3;
}

template<std::floating_point Tp>
[[nodiscard]] constexpr Tp dot(const Vec3<Tp>& u, const Vec3<Tp>& v) {
	return u.x() * v.x() +
			u.y() * v.y() +
			u.z() * v.z();
}

template<std::floating_point Tp>
[[nodiscard]] constexpr Vec3<Tp> cross(const Vec3<Tp>& u, const Vec3<Tp>& v) noexcept{
	return Vec3<Tp>(u.y() * v.z() - u.z() * v.y(),
			 	u.z() * v.x() - u.x() * v.z(),
			 	u.x() * v.y() - u.y() * v.x()
	);
}

template<std::floating_point Tp>
[[nodiscard]] constexpr Vec3<Tp> unit_vector(const Vec3<Tp>& v) {
	return v / v.length();
}

using Vec3d = Vec3<double>;
using Vec3f = Vec3<float>;
using vec3  = Vec3d;

}
