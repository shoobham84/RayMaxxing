#pragma once

#include "VecBase3.hpp"

template<std::floating_point Tp>
class Vec3 : public VecBase3<Tp>
{
	using value_type = Tp;
};
