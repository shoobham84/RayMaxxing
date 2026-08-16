#pragma once

#include "Vec3.hpp"
#include "Position.hpp"

template <std::floating_point Tp>
class Ray {
public:
	using value_type = Tp;

	constexpr Ray() noexcept = default;

	Ray(const Point<value_type>& origin, const Vec3<value_type>& direction) 
	: m_Origin(origin), m_Dir(direction) {}

	constexpr Point<value_type> at(value_type lambda) {
		return m_Origin + lambda * m_Dir;
	}

private:
	Point<value_type> m_Origin;
	Vec3<value_type> m_Dir;
};
