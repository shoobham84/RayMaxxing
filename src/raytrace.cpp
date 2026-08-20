#include <iostream>
#include <print>
#include "Color.hpp"
#include "Ray.hpp"
#include "Position.hpp"
#include <algorithm>

// assuming a sphere C with center C = (Cx, Cy, Cz). a ray emanating from a point3 (x, y, z)
// (Cx - x)^2 + (Cy - y)^2 + (Cz - z)^2 = r^2  standard form of a sphere
// below func used to find if point satisfies the sphere's equation, vector form: |P - C| = r;  (P - C) dot (P - C) = r^2 
double sphereHit(const rtrc::point3& center, double radius, const rtrc::ray& ray) {
	rtrc::vec3 OC { center - ray.origin()};
	auto a { rtrc::dot(ray.direction(), ray.direction()) };
	auto b { (-2.0) * rtrc::dot(ray.direction(), OC) };
	auto c { rtrc::dot(OC, OC) - (radius * radius) };

	auto discriminant{ b*b - 4*a*c };
	if (discriminant < 0) return -1;
	return (-b - std::sqrt(discriminant)) / (2.0 * a);
}


// blendedval = (1-a) * startVal + a * endval
rtrc::color rayColor(const rtrc::ray& ray) {
	auto lambda { sphereHit(rtrc::point3(0, 0, -1), 0.5, ray) };     // here lambda is: a + lambda*b in eqn of 3d ray
	if (lambda > 0.0) {
		rtrc::vec3 NormalVec = rtrc::unit_vector(ray.at(lambda) - rtrc::point3(0, 0, -1));
		return 0.5 * rtrc::color(NormalVec.x()+1, NormalVec.y()+1, NormalVec.z()+1);
	} 

	rtrc::vec3 unitDir = rtrc::unit_vector(ray.direction());
	auto a { 0.5 * (unitDir.y() + 1.0) };
	return (1.0 - a) * rtrc::color(1.0, 1.0, 1.0) + a * rtrc::color(0.0, 0.0, 0.0);
}

int main() {
	constexpr auto aspectRatio { 16.0 / 9.0 };
	constexpr int image_width { 400 };

	constexpr int image_height { std::max( 1, static_cast<int>( image_width / aspectRatio ))};

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

			rtrc::color pixel_color{ rayColor(testRay) };
			rtrc::writeColor(std::cout, pixel_color);
		}
	}
	std::println(std::cerr, "\rDone.              ");
}
