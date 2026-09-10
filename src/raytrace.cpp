#include "RayMaxxing.hpp"
#include "HittableList.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"


int main() {
	// world
	HittableList world;
	world.add(std::make_shared<Sphere>(rtrc::point3(0, -100.5, -1), 100)); // the ground is a sphere yo
	world.add(std::make_shared<Sphere>(rtrc::point3(0, 0, -1), 0.5));

	Camera camera;
	camera.samples_per_pixel = 100;
	camera.Render(world);
}
