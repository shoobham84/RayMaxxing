#include <print>

int main() {
	constexpr int image_width { 256 };
	constexpr int image_height { 256 };

	std::println("P3\n{} {} \n255\n", image_width, image_height);
}
