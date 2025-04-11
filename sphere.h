#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
    // full constructor with center, radius, and material
    sphere(const point3& c, double r, shared_ptr<material> m)
        : center(c), radius(std::fmax(0, r)), surface_material(m) {}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        vec3 oc = center - r.origin();
        auto a = r.direction().length_squared();
        auto half_b = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius * radius;

        auto discriminant = half_b * half_b - a * c;
        if (discriminant < 0) return false;

        auto sqrtd = sqrt(discriminant);

        // find closest root in valid interval
        auto root = (half_b - sqrtd) / a;
        if (!ray_t.surrounds(root)) {
            root = (half_b + sqrtd) / a;
            if (!ray_t.surrounds(root))
                return false;
        }

        // fill hit record
        rec.hit_t = root;
        rec.hit_point = r.at(rec.hit_t);
        vec3 outward_normal = (rec.hit_point - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.surface_material = surface_material;

        return true;
    }

private:
    point3 center;
    double radius;
    shared_ptr<material> surface_material;
};

#endif
