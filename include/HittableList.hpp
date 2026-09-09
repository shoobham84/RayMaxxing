#pragma once

#include "Hittable.hpp"
#include <vector>
#include <memory>

template <std::floating_point Tp>
class HittableList : public Hittable<Tp> {
public:
	std::vector<std::shared_ptr<Hittable<Tp>>> objects;
	
	HittableList() = default;
	HittableList(std::shared_ptr<Hittable<Tp>> object) {
		add(object);
	}

	void add(std::shared_ptr<Hittable<Tp>> obj) {
		objects.emplace_back(obj);
	}

	bool hit(const rtrc::ray& ray, Tp ray_tmin, Tp ray_tmax, HitRecord& record) const override {
		HitRecord tempRecord;
		bool hitAnything{ false };

		auto closestSoFar = ray_tmax;

		for (const auto& obj : objects) {
			if (obj->hit(ray, ray_tmin, closestSoFar, tempRecord)) {
				hitAnything = true;
				closestSoFar = tempRecord.Time;
				record = tempRecord;
			}
		}

		return hitAnything;
	}
};
