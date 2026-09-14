#pragma once

#include "Vec3.hpp"
#include "Point.hpp"

namespace rtrc {

template<std::floating_point Tp>
[[nodiscard]] constexpr Point<Tp> operator+(const Point<Tp>& p, const Vec3<Tp>& v) noexcept {
	return Point<Tp>(p.x() + v.x(), p.y() + v.y(), p.z() + v.z());
}

template<std::floating_point Tp>
[[nodiscard]] constexpr Point<Tp> operator+(const Vec3<Tp>& v, const Point<Tp>& p) noexcept {
	return p + v;
}

template<std::floating_point Tp>
[[nodiscard]] constexpr Point<Tp> operator-(const Point<Tp>& p, const Vec3<Tp>& v) noexcept {
	return Point<Tp>(p.x() - v.x(), p.y() - v.y(), p.z() - v.z());
}

template<std::floating_point Tp>
[[nodiscard]] constexpr Vec3<Tp> operator-(const Point<Tp>& a, const Point<Tp>& b) noexcept {
	return Vec3<Tp>(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
}

template<std::floating_point Tp>
constexpr Point<Tp>& operator+=(Point<Tp>& p, const Vec3<Tp>& v) noexcept {
	p[0] += v[0];
	p[1] += v[1];
	p[2] += v[2];
	return p;
}

template<std::floating_point Tp>
constexpr Point<Tp>& operator-=(Point<Tp>& p, const Vec3<Tp>& v) noexcept {
	p[0] -= v[0];
	p[1] -= v[1];
	p[2] -= v[2];
	return p;
}

} // namespace rtrc
