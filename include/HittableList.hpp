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

	constexpr void add(std::shared_ptr<Hittable> obj) {
		objects.emplace_back(obj);
	}

	bool Hit(const rtrc::ray& ray, Interval ray_t, HitRecord& record) const override {
		HitRecord tempRecord;
		bool hitAnything{ false };

		auto closestSoFar = ray_t.Max;

		for (const auto& obj : objects) {
			if (obj->Hit(ray, Interval(ray_t.Min, closestSoFar), tempRecord)) {
				hitAnything = true;
				closestSoFar = tempRecord.Time;
				record = tempRecord;
			}
		}

		return hitAnything;
	}
};

