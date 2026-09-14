#pragma once

#include "VecBase3.hpp"

namespace rtrc {


template<std::floating_point Tp>
class Point : public VecBase3<Tp>
{
public:
	using value_type = Tp;

	constexpr Point() noexcept = default;

	constexpr Point(value_type x, value_type y, value_type z)
	: VecBase3<Tp>(x, y, z) {}
};


using Point3d = Point<double>;
using Point3f = Point<float>;
using point3  = Point3d;

}
