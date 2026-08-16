#include <iostream>
#include <print>
#include "Color.hpp"

int main() {
	constexpr int image_width { 256 };
	constexpr int image_height { 256 };

	std::println("P3\n{} {} \n255\n", image_width, image_height);

	for (int j{0}; j < image_height; ++j) {
		std::println(std::cerr, "\rScanlines remaining: {} ", (image_height - j));
		for (int i{0}; i < image_width; ++i) {
			auto pixel_color = Color<double>(
				static_cast<double>(i)/(image_width-1), 
				static_cast<double>(j)/(image_height-1),
				0.0);

			writeColor(std::cout, pixel_color);
		}
	}
	std::println(std::cerr, "\rDone.              ");
}
