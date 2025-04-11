#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class material;

class hit_record {
public:
    // location where the ray hit the object
    point3 hit_point;

    // surface normal at the point of contact
    vec3 surface_normal;

    // pointer to the material of the object hit
    shared_ptr<material> surface_material;

    // distance from ray origin to intersection
    double hit_t;

    // determines if the hit was from outside the surface
    bool is_front_face;

    void set_face_normal(const ray& incoming_ray, const vec3& outward_normal) {
        // check if ray is hitting from outside or inside
        is_front_face = dot(incoming_ray.direction(), outward_normal) < 0;
        surface_normal = is_front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    virtual ~hittable() = default;

    // every hittable object must implement this to define how it's intersected by a ray
    virtual bool hit(const ray& r, interval ray_bounds, hit_record& rec) const = 0;
};

#endif
