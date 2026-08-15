#include <print>

int main() {
	constexpr int image_width { 256 };
	constexpr int image_height { 256 };

	std::println("P3\n{} {} \n255\n", image_width, image_height);

	for (int j{0}; j < image_height; ++j) {
		for (int i{0}; i < image_width; ++i) {
			auto r = static_cast<double>(i) / (image_width - 1);
			auto g = static_cast<double>(j) / (image_height - 1);
			auto b = 0.0;

			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);

			std::println("{} {} {}", ir, ig, ib);
		}
	}
}
