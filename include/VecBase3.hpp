#pragma once

#include <concepts>
#include <array>
#include <format>
#include <cassert>
#include <cmath>
#include <ostream>

namespace rtrc {

template<std::floating_point Tp>
class VecBase3
{
public:
	using value_type = Tp;

	constexpr VecBase3() noexcept = default;

	constexpr VecBase3(value_type x, value_type y, value_type z)
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

	[[nodiscard]] constexpr bool operator==(const VecBase3& other) const noexcept = default;

	[[nodiscard]] constexpr value_type length_squared() const {
		return x() * x() + y() * y() + z() * z();
	}

	[[nodiscard]] constexpr value_type length() const {
		return std::sqrt(length_squared());
	}

protected:
	constexpr static size_t m_DataSize{ 3 };

	std::array<value_type, m_DataSize> m_Data{ 
		static_cast<value_type>(0),
		static_cast<value_type>(0),
		static_cast<value_type>(0)
	};
};


template<typename T>
concept Vec3Like = requires {
	typename T::value_type;
	requires std::floating_point<typename T::value_type>;
	requires std::derived_from<T, VecBase3<typename T::value_type>>;
};


template<Vec3Like V>
constexpr V& operator+=(V& lhs, const V& rhs) noexcept {
	lhs[0] += rhs[0];
	lhs[1] += rhs[1];
	lhs[2] += rhs[2];
	return lhs;
}

template<Vec3Like V>
constexpr V& operator-=(V& lhs, const V& rhs) noexcept {
	lhs[0] -= rhs[0];
	lhs[1] -= rhs[1];
	lhs[2] -= rhs[2];
	return lhs;
}

template<Vec3Like V, std::convertible_to<typename V::value_type> Sclr>
constexpr V& operator*=(V& lhs, Sclr scalar) noexcept {
	const auto s = static_cast<typename V::value_type>(scalar);
	lhs[0] *= s;
	lhs[1] *= s;
	lhs[2] *= s;
	return lhs;
}

template<Vec3Like V, std::convertible_to<typename V::value_type> Sclr>
constexpr V& operator/=(V& lhs, Sclr scalar) {
	return lhs *= static_cast<typename V::value_type>(1) / static_cast<typename V::value_type>(scalar);
}



template<Vec3Like V>
inline std::ostream& operator<<(std::ostream& out, const V& vec) {
	return out << vec.x() << ' ' << vec.y() << ' ' << vec.z();
}

template<Vec3Like V>
[[nodiscard]] constexpr V operator+(const V& u, const V& v) noexcept {
	return V(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

template<Vec3Like V>
[[nodiscard]] constexpr V operator-(const V& u, const V& v) noexcept {
	return V(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

template<Vec3Like V>
[[nodiscard]] constexpr V operator-(const V& v) {
	return V(-(v.x()), -(v.y()), -(v.z()));
}

template<Vec3Like V>
[[nodiscard]] constexpr V operator*(const V& u, const V& v) noexcept {
	return V(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

template<Vec3Like V, std::convertible_to<typename V::value_type> Sclr>
[[nodiscard]] constexpr V operator*(Sclr scalar, const V& vec) noexcept {
	return V(scalar * vec.x(), scalar * vec.y(), scalar * vec.z());
}

template<Vec3Like V, std::convertible_to<typename V::value_type> Sclr>
[[nodiscard]] constexpr V operator*(const V& vec, Sclr val) noexcept {
	return val * vec;
}

template<Vec3Like V, std::convertible_to<typename V::value_type> Sclr>
[[nodiscard]] constexpr V operator/(const V& vec, Sclr val) {
	return (static_cast<typename V::value_type>(1) / val) * vec;
}


template<Vec3Like V>
[[nodiscard]] constexpr typename V::value_type dot(const V& u, const V& v) {
	return u.x() * v.x() +
			u.y() * v.y() +
			u.z() * v.z();
}

template<Vec3Like V>
[[nodiscard]] constexpr V cross(const V& u, const V& v) noexcept {
	return V(u.y() * v.z() - u.z() * v.y(),
			 u.z() * v.x() - u.x() * v.z(),
			 u.x() * v.y() - u.y() * v.x()
	);
}

template<Vec3Like V>
[[nodiscard]] constexpr V unit_vector(const V& v) {
	return v / v.length();
}

} // namespace rtrc


template<rtrc::Vec3Like V>
struct std::formatter<V> {
	constexpr auto parse(std::format_parse_context& ctx) {
		return ctx.begin();
	}

	auto format(const V& vec, std::format_context& ctx) const {
		return std::format_to(ctx.out(), "{} {} {}", vec.x(), vec.y(), vec.z());
	}
};
