#pragma once

#include <concepts>
#include <array>
#include <format>
#include <cassert>
#include <cmath>
#include <ostream>
#include "RayMaxxing.hpp"

namespace rtrc {

template<std::floating_point Tp>
class Vec3
{
public:
	using value_type = Tp;

	constexpr Vec3() noexcept = default;

	constexpr Vec3(value_type x, value_type y, value_type z)
	: m_Data{ x, y, z } {}

	[[nodiscard]] constexpr value_type x() const noexcept {
		return m_Data[0]; 
	}
	[[nodiscard]] constexpr value_type y() const noexcept {
		return m_Data[1];
	}
	[[nodiscard]] constexpr value_type z() const noexcept { 
		return m_Data[2];
	}

	[[nodiscard]] constexpr const value_type& operator[](size_t index) const {
		assert(index < m_DataSize && "Index out of bounds");
		return m_Data[index];
	}

	[[nodiscard]] constexpr value_type& operator[](size_t index) {
		assert(index < m_DataSize && "Index out of bounds");
		return m_Data[index];
	}

	[[nodiscard]] constexpr Vec3 operator-() const {
		return Vec3(-(this->x()), -(this->y()), -(this->z()));
	}

	[[nodiscard]] constexpr bool operator==(const Vec3<value_type>& other) const noexcept = default;

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

	template <std::convertible_to<value_type> Sclr>
	constexpr Vec3& operator*=(Sclr scalar) noexcept {
		const auto s = static_cast<value_type>(scalar);
		(*this)[0] *= s;
		(*this)[1] *= s;
		(*this)[2] *= s;
		return *this;
	}

	template <std::convertible_to<value_type> Sclr>
	constexpr Vec3& operator/=(Sclr scalar) {
		return *this *= static_cast<value_type>(1) / static_cast<value_type>(scalar);
	}

	constexpr static Vec3 random() {
		return Vec3(randomDouble(), randomDouble(), randomDouble());
	}

	constexpr static Vec3 random(double min, double max) {
		return Vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
	}

private:
	constexpr static size_t m_DataSize{ 3 };

	std::array<value_type, m_DataSize> m_Data{ 
		static_cast<value_type>(0),
		static_cast<value_type>(0),
		static_cast<value_type>(0)
	};
	
};

// ── free operators ───────────────────────────────────────────────────

template <std::floating_point Tp>
inline std::ostream& operator<<(std::ostream& out, const Vec3<Tp>& Vec) {
	return out << Vec.x() << ' ' << Vec.y() << ' ' << Vec.z();
}

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

template <std::floating_point Tp, std::convertible_to<Tp> Sclr>
[[nodiscard]] constexpr Vec3<Tp> operator/(const Vec3<Tp>& vec3, Sclr val) {
	return (static_cast<Tp>(1)/val) * vec3;
}

template <std::floating_point Tp, std::convertible_to<Tp> Sclr>
[[nodiscard]] constexpr Vec3<Tp> operator*(Sclr scalar, const Vec3<Tp>& vec3) noexcept {
	return Vec3<Tp>(scalar * vec3.x(), scalar * vec3.y(), scalar*vec3.z());
}

template <std::floating_point Tp, std::convertible_to<Tp> Sclr>
[[nodiscard]] constexpr Vec3<Tp> operator*(const Vec3<Tp>& vec3, Sclr val) noexcept {
	return val * vec3;
}

// ── geometric helpers ────────────────────────────────────────────────

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


// ── color helper ─────────────────────────────────────────────────────

constexpr auto linearToGamma(double linearComp) {
	if (linearComp > 0) return std::sqrt(linearComp);

	return 0.0;
}

template<std::floating_point Tp>
void writeColor(std::ostream& out, const Vec3<Tp>& PixelColor) {
	auto r{ PixelColor.x() };
	auto g{ PixelColor.y() };
	auto b{ PixelColor.z() };

	r = linearToGamma(r);
	g = linearToGamma(g);
	b = linearToGamma(b);

	// translate [0,1] to range [0, 255]
	static constexpr Interval intensity(0.000, 0.999);
	int rbyte = static_cast<int>(256 * intensity.clamp(r));
	int gbyte = static_cast<int>(256 * intensity.clamp(g));
	int bbyte = static_cast<int>(256 * intensity.clamp(b));

	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}




// ── type aliases ─────────────────────────────────────────────────────

using Vec3d = Vec3<double>;
using Vec3f = Vec3<float>;
using vec3  = Vec3d;

template<std::floating_point Tp>
using Color = Vec3<Tp>;

using Color3d = Color<double>;
using Color3f = Color<float>;
using color   = Color3d;

template<std::floating_point Tp>
using Point = Vec3<Tp>;

using Point3d = Point<double>;
using Point3f = Point<float>;
using point3  = Point3d;

}


template<std::floating_point Tp>
struct std::formatter<rtrc::Vec3<Tp>> {
	constexpr auto parse(std::format_parse_context& ctx) {
		return ctx.begin();
	}

	auto format(const rtrc::Vec3<Tp>& Vec, std::format_context& ctx) const {
		return std::format_to(ctx.out(), "{} {} {}", Vec.x(), Vec.y(), Vec.z());
	}
};
