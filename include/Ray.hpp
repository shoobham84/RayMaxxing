#pragma once

#include "Vec3.hpp"
#include "Position.hpp"

namespace rtrc {

template <std::floating_point Tp>
class Ray {
public:
	using value_type = Tp;

	constexpr Ray() noexcept = default;

	Ray(const Point<value_type>& origin, const Vec3<value_type>& direction) 
	: m_Origin(origin), m_Dir(direction) {}

	constexpr Point<value_type> at(value_type lambda) const noexcept {
		return m_Origin + lambda * m_Dir;
	}

	[[nodiscard]] constexpr const Vec3<value_type>& direction() const noexcept { return m_Dir; }
	[[nodiscard]] constexpr const Point<value_type>& origin() const noexcept { return m_Origin; }

private:
	Point<value_type> m_Origin;
	Vec3<value_type> m_Dir;
};

using Ray3d = Ray<double>;
using Ray3f = Ray<float>;
using ray   = Ray3d;

}
