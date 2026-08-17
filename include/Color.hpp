#pragma once

#include "VecBase3.hpp"
#include <ostream>

namespace rtrc {

template<std::floating_point Tp>
class Color : public VecBase3<Tp>
{
public:
	using value_type = Tp;
	using VecBase3<value_type>::VecBase3;
};

template<std::floating_point Tp>
void writeColor(std::ostream& out, const Color<Tp>& PixelColor) {
	auto r{ PixelColor.x() };
	auto g{ PixelColor.y() };
	auto b{ PixelColor.z() };

	// translate [0,1] to range [0, 255]
	int rbyte = static_cast<int>(255.999 * r);
	int gbyte = static_cast<int>(255.999 * g);
	int bbyte = static_cast<int>(255.999 * b);

	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

using Color3d = Color<double>;
using Color3f = Color<float>;
using color   = Color3d;

}
