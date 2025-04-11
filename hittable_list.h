#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>
// generally we use this class as a base class to derive others and we overwrite most of its functions

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable {
public:
    std::vector<shared_ptr<hittable>> objects; // all the objects in the scene

    hittable_list() {}
    hittable_list(shared_ptr<hittable> obj) { add(obj); }

    void clear() { objects.clear(); } // remove everything from the scene

    void add(shared_ptr<hittable> obj) {
        objects.push_back(obj); // add a new object to the scene
    }

    // checks if any object in the list is hit by the ray
    bool hit(const ray& r, interval ray_t, hit_record& closest_hit) const override {
        hit_record temp_hit; // stores hit info for current object
        bool any_hit = false;
        auto closest_so_far = ray_t.max; // we keep track of closest t

        for (const auto& obj : objects) {
            if (obj->hit(r, interval(ray_t.min, closest_so_far), temp_hit)) {
                any_hit = true;
                closest_so_far = temp_hit.hit_t;
                closest_hit = temp_hit;
            }
        }

        return any_hit; // if we hit at least one object
    }
};

#endif
