#include <iostream>
#include <algorithm>
#include "RayMaxxing.hpp"
#include "Hittable.hpp"
#include "HittableList.hpp"
#include "Sphere.hpp"


rtrc::color rayColor(const rtrc::ray& ray, const Hittable& world) {
	HitRecord record;
	if (world.Hit(ray, 0, Infinity, record)) {
		return 0.5 * (record.Normal + rtrc::color(1,1,1));
	}

	rtrc::vec3 unitDir = rtrc::unit_vector(ray.direction());
	auto a { 0.5 * (unitDir.y() + 1.0) };
	return (1.0 - a) * rtrc::color(1.0, 1.0, 1.0) + a * rtrc::color(0.0, 0.3, 0.7);
}


int main() {
	constexpr auto aspectRatio { 16.0 / 9.0 };
	constexpr int image_width { 400 };

	constexpr int image_height { std::max( 1, static_cast<int>( image_width / aspectRatio ))};

	// world
	HittableList world;
	world.add(std::make_shared<Sphere>(rtrc::point3(0, 0, -1), 0.5));
	world.add(std::make_shared<Sphere>(rtrc::point3(0, -100.5, -1), 100));

	// camera
	auto focalLength { 1.0 };
	auto viewportHeight { 2.0 };
	auto viewportWidth { viewportHeight * static_cast<double>( image_width) / image_height };

	auto cameraCenter { rtrc::point3() };

	// horz and vertical vectors
	auto viewportU { rtrc::vec3(viewportWidth, 0.0, 0.0 )};
	auto viewportV { rtrc::vec3(0.0, -viewportHeight, 0.0 )};

	// pixel delta vectors, interpixel distance
	auto pixelDeltaU { viewportU / image_width };
	auto pixelDeltaV { viewportV / image_height };

	// location of upper left pixel, pixel grid inset by half interpixel distance to the viewport
	auto viewportUpperLeft { cameraCenter - rtrc::vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2 };
	auto pixelUL_00_Location { viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV) };

	std::println("P3\n{} {} \n255\n", image_width, image_height);

	for (int j{0}; j < image_height; ++j) {
		std::println(std::cerr, "\rScanlines remaining: {} ", (image_height - j));
		for (int i{0}; i < image_width; ++i) {
			auto pixelCenter = pixelUL_00_Location + (i * pixelDeltaU) + (j * pixelDeltaV);

			auto rayDirection = pixelCenter - cameraCenter;
			rtrc::ray testRay(cameraCenter, rayDirection);

			rtrc::color pixel_color{ rayColor(testRay, world) };
			rtrc::writeColor(std::cout, pixel_color);
		}
	}
	std::println(std::cerr, "\rDone.              ");
}
