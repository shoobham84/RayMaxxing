#pragma once

#include <concepts>
#include <array>
#include <format>
#include <cassert>

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

	[[nodiscard]] constexpr const value_type& operator[](size_t _index) const {
		assert(_index < m_DataSize && "Index out of bounds");
		return m_Data[_index];
	}

	[[nodiscard]] value_type& operator[](size_t _index) {
		assert(_index < m_DataSize && "Index out of bounds");
		return m_Data[_index];
	}

	[[nodiscard]] bool operator==(const VecBase3<value_type>& other) const noexcept = default;

private:
	constexpr static size_t m_DataSize{ 3 };

	std::array<value_type, m_DataSize> m_Data{ 
		static_cast<value_type>(0),
		static_cast<value_type>(0),
		static_cast<value_type>(0)
	};
	
};

template <std::floating_point Tp>
inline std::ostream& operator<<(std::ostream& out, const VecBase3<Tp>& Vec) {
	return out << Vec.x() << ' ' << Vec.y() << ' ' << Vec.z();
}

using VecBase3d = VecBase3<double>;
using VecBase3f = VecBase3<float>;
using vecbase3  = VecBase3d;

}


template<std::floating_point Tp>
struct std::formatter<rtrc::VecBase3<Tp>> {
	constexpr auto parse(std::format_parse_context& ctx) {
		return ctx.begin();
	}

	auto format(const rtrc::VecBase3<Tp>& Vec, std::format_context& ctx) const {
		return std::format_to(ctx.out(), "{} {} {}", Vec.x(), Vec.y(), Vec.z());
	}
};


