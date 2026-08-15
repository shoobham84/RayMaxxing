#pragma once

#include <concepts>
#include <array>
#include <format>
#include <cassert>

template<std::floating_point Tp>
class VecBase3
{
public:
	using value_type = Tp;
	
	constexpr VecBase3() noexcept = default;

	constexpr VecBase3(value_type x, value_type y, value_type z)
	: m_Data{ x, y, z } {}

	[[nodiscard]] value_type x() const {
		return m_Data[0]; 
	}
	[[nodiscard]] value_type y() const {
		return m_Data[1];
	}
	[[nodiscard]] value_type z() const { 
		return m_Data[2];
	}

	[[nodiscard]] constexpr value_type& operator[](size_t _index) const {
		assert(_index < m_DataSize && "Index out of bounds");
		return m_Data[_index];
	}

	[[nodiscard]] value_type& operator[](size_t _index) {
		assert(_index < m_DataSize && "Index out of bounds");
		return m_Data[_index];
	}

private:
	constexpr static size_t m_DataSize{ 3 };
	std::array<value_type, m_DataSize> m_Data{ 
		static_cast<value_type>(0),
		static_cast<value_type>(0),
		static_cast<value_type>(0)
	};
	
};

template<std::floating_point Tp>
struct std::formatter<VecBase3<Tp>> {
	constexpr auto parse(std::format_parse_context& ctx) {
		return ctx.begin();
	}

	auto format(const VecBase3<Tp>& Vec, std::format_context& ctx) const {
		return std::format_to(ctx.out(), "{} {} {}", Vec.x(), Vec.y(), Vec.z());
	}
};
