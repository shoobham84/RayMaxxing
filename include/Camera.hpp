#pragma once

#include "Hittable.hpp"
#include <iostream>
#include <print>

class Camera {
public:
	static constexpr const auto aspectRatio { 16.0 / 9.0 };
	static constexpr const int image_width { 400 };


	void Render(const Hittable& world) {
		Initialize();

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

private:
	int image_height;
	rtrc::point3 cameraCenter; 
	rtrc::point3 pixelUL_00_Location;
	rtrc::Vec3<double> pixelDeltaU;
	rtrc::Vec3<double> pixelDeltaV;

	void Initialize() {
		image_height = std::max( 1, static_cast<int>( image_width / aspectRatio ));
		
		// camera
		auto focalLength { 1.0 };
		auto viewportHeight { 2.0 };
		auto viewportWidth { viewportHeight * static_cast<double>( image_width) / image_height };

		cameraCenter = rtrc::point3();

		// horz and vertical vectors
		auto viewportU { rtrc::vec3(viewportWidth, 0.0, 0.0 )};
		auto viewportV { rtrc::vec3(0.0, -viewportHeight, 0.0 )};

		// pixel delta vectors, interpixel distance
		pixelDeltaU = viewportU / image_width ;
		pixelDeltaV = viewportV / image_height ;

		// location of upper left pixel, pixel grid inset by half interpixel distance to the viewport
		auto viewportUpperLeft { cameraCenter - rtrc::vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2 };

		pixelUL_00_Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
	}

	rtrc::color rayColor(const rtrc::ray& ray, const Hittable& world) {
		HitRecord record;
		if (world.Hit(ray, Interval(0, Infinity), record)) {
			return 0.5 * (record.Normal + rtrc::color(1,1,1));
		}

		rtrc::vec3 unitDir = rtrc::unit_vector(ray.direction());
		auto a { 0.5 * (unitDir.y() + 1.0) };
		return (1.0 - a) * rtrc::color(1.0, 1.0, 1.0) + a * rtrc::color(0.0, 0.3, 0.7);
	}

};
