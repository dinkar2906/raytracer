#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "hittable.h"

// base material class - every material should define its scatter behavior
class material {
public:
    virtual ~material() = default;

    // returns whether the ray is scattered or absorbed
    virtual bool scatter(
        const ray& incoming_ray, const hit_record& rec, color& attenuation, ray& scattered_ray
    ) const {
        return false;
    }
};

// matte surface - light scatters randomly
class lambertian : public material {
public:
    lambertian(const color& texture_color) : albedo(texture_color) {}

    bool scatter(const ray& incoming_ray, const hit_record& rec, color& attenuation, ray& scattered_ray)
    const override {
        // new direction after scattering
        vec3 scatter_dir = rec.surface_normal + random_unit_vector();

        // handle edge case when direction is near zero
        if (scatter_dir.near_zero())
            scatter_dir = rec.surface_normal;

        scattered_ray = ray(rec.hit_point, scatter_dir);
        attenuation = albedo; // color of the surface
        return true;
    }

private:
    color albedo; // surface color
};

// metallic surface - reflects light with optional fuzziness
class metal : public material {
public:
    metal(const color& texture_color, double fuzz_factor)
        : albedo(texture_color), fuzz(fuzz_factor < 1 ? fuzz_factor : 1) {}

    bool scatter(const ray& incoming_ray, const hit_record& rec, color& attenuation, ray& scattered_ray)
    const override {
        // get reflected direction with fuzz
        vec3 reflected_dir = reflect(unit_vector(incoming_ray.direction()), rec.surface_normal);
        reflected_dir += fuzz * random_unit_vector();

        scattered_ray = ray(rec.hit_point, reflected_dir);
        attenuation = albedo;

        // return true only if reflection goes outward
        return dot(scattered_ray.direction(), rec.surface_normal) > 0;
    }

private:
    color albedo;
    double fuzz; // how blurry the reflection is
};

// transparent like glass - reflects or refracts light based on angle
class dielectric : public material {
public:
    dielectric(double ref_index) : refractive_index(ref_index) {}

    bool scatter(const ray& incoming_ray, const hit_record& rec, color& attenuation, ray& scattered_ray)
    const override {
        attenuation = color(1.0, 1.0, 1.0); // no color loss

        // choose refraction ratio based on hit direction
        double eta = rec.is_front_face ? (1.0 / refractive_index) : refractive_index;

        vec3 unit_dir = unit_vector(incoming_ray.direction());

        // calculate angle info
        double cos_theta = fmin(dot(-unit_dir, rec.surface_normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        bool will_refract = eta * sin_theta <= 1.0;
        vec3 scatter_dir;

        // reflect or refract depending on conditions
        if (!will_refract || reflectance(cos_theta, eta) > random_double()) {
            scatter_dir = reflect(unit_dir, rec.surface_normal);
        } else {
            scatter_dir = refract(unit_dir, rec.surface_normal, eta);
        }

        scattered_ray = ray(rec.hit_point, scatter_dir);
        return true;
    }

private:
    double refractive_index; // how bendy the material is

    // Schlick's approximation for reflectivity
    static double reflectance(double cosine, double eta) {
        auto r0 = (1 - eta) / (1 + eta);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};

#endif
