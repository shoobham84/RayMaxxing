#pragma once

#include "VecBase3.hpp"
#include "RayMaxxing.hpp"

namespace rtrc {

template<std::floating_point Tp>
class Vec3 : public VecBase3<Tp>
{
public:
	using value_type = Tp;

	constexpr Vec3() noexcept = default;

	constexpr Vec3(value_type x, value_type y, value_type z)
	: VecBase3<Tp>(x, y, z) {}

	constexpr static Vec3 random() {
		return Vec3(randomDouble(), randomDouble(), randomDouble());
	}

	constexpr static Vec3 random(double min, double max) {
		return Vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
	}
};


template<std::floating_point Tp>
constexpr Vec3<Tp> random_unit_vector() {
	while(1) {
		auto P { Vec3<Tp>::random(-1, 1)};
		auto len_sq { P.length_squared() };
		if ( 1e-160 < len_sq && len_sq<= 1) {
			return P / sqrt(len_sq);
		}
	}
}

template<std::floating_point Tp>
constexpr Vec3<Tp> random_on_hemisphere(const Vec3<Tp>& normal) {
	Vec3<Tp> onUnitSphere { random_unit_vector<Tp>() };
	if (dot(onUnitSphere, normal) > 0) 
		return onUnitSphere;
	else
		return -onUnitSphere;
}

using Vec3d = Vec3<double>;
using Vec3f = Vec3<float>;
using vec3  = Vec3d;

}
