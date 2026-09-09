#pragma once

#include "Hittable.hpp"
#include <vector>
#include <memory>

class HittableList : public Hittable {
public:
	std::vector<std::shared_ptr<Hittable>> objects;
	
	HittableList() = default;
	HittableList(std::shared_ptr<Hittable> object) {
		add(object);
	}

	void clear() {
		objects.clear();
	}

	void add(std::shared_ptr<Hittable> obj) {
		objects.emplace_back(obj);
	}

	bool Hit(const rtrc::ray& ray, double ray_tmin, double ray_tmax, HitRecord& record) const override {
		HitRecord tempRecord;
		bool hitAnything{ false };

		auto closestSoFar = ray_tmax;

		for (const auto& obj : objects) {
			if (obj->Hit(ray, ray_tmin, closestSoFar, tempRecord)) {
				hitAnything = true;
				closestSoFar = tempRecord.Time;
				record = tempRecord;
			}
		}

		return hitAnything;
	}
};

