#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <vector>

class hittable_list : public hittable {
  public:
    std::vector<shared_ptr<hittable>> objects; // vector of shared pointers to hittable objects (plural attention)

    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); } // (singular attention)

    void clear() { objects.clear(); } // clear the vector

    void add(shared_ptr<hittable> object) {
        objects.push_back(object); // add in the end of the vector
    }

    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_tmax;

        // loop through all objects in the list and check if the ray hits any of them
        for (const auto& object : objects) {
            if (object->hit(r, ray_tmin, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};

#endif 