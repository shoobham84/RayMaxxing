#pragma once

#include "VecBase3.hpp"
#include <ostream>

namespace rtrc {

template<std::floating_point Tp>
class Color : public VecBase3<Tp>
{
public:
	using value_type = Tp;

	constexpr Color() noexcept = default;

	constexpr Color(value_type r, value_type g, value_type b)
	: VecBase3<Tp>(r, g, b) {}

	[[nodiscard]] constexpr value_type r() const noexcept { return this->x(); }
	[[nodiscard]] constexpr value_type g() const noexcept { return this->y(); }
	[[nodiscard]] constexpr value_type b() const noexcept { return this->z(); }
};



constexpr auto linearToGamma(double linearComp) {
	if (linearComp > 0) return std::sqrt(linearComp);

	return 0.0;
}

template<std::floating_point Tp>
void writeColor(std::ostream& out, const Color<Tp>& PixelColor) {
	auto r{ PixelColor.r() };
	auto g{ PixelColor.g() };
	auto b{ PixelColor.b() };

	r = linearToGamma(r);
	g = linearToGamma(g);
	b = linearToGamma(b);

	static constexpr Interval intensity(0.000, 0.999);
	int rbyte = static_cast<int>(256 * intensity.clamp(r));
	int gbyte = static_cast<int>(256 * intensity.clamp(g));
	int bbyte = static_cast<int>(256 * intensity.clamp(b));

	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

using Color3d = Color<double>;
using Color3f = Color<float>;
using color   = Color3d;

}
