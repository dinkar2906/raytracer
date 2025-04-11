#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include "hittable.h"
#include "material.h"
#include "color.h"
#include "ray.h"
#include "vec3.h"

class camera {
public:

    // defining our viewport it can be overwritten
    double aspect_ratio = 1.0;
    int image_width = 100;
    // generally we overwrite samples per pixel more it is to calcualate you can say average of a pixel to blend it 
    // that creates a realisitc view insetead of sharp edges
    int samples_per_pixel = 10;
    int max_depth = 10;
    // you can say these are the general property of camera
    double vfov = 90;
    point3 lookfrom = point3(0, 0, 0);
    point3 lookat = point3(0, 0, -1);
    vec3 vup = vec3(0, 1, 0);

    double defocus_angle = 0; // if we want to simulate depth of field effect
    double focus_dist = 10;   // how far camera is focusing

    void render(const hittable& world) {
        initialize(); // sets up camera properties

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        // going row by row and then col by col and averaging color samples to make image smooth
        for (int y = 0; y < image_height; y++) {
            std::clog << "\rScanlines remaining: " << (image_height - y) << ' ' << std::flush;
            for (int x = 0; x < image_width; x++) {
                color pixel_sum(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; s++) {
                    ray r = get_ray(x, y);
                    pixel_sum += ray_color(r, max_depth, world);
                }
                write_color(std::cout, pixel_samples_scale * pixel_sum);
            }
        }
        std::clog << "\rDone.                 \n";
    }

private:
    int image_height;
    double pixel_samples_scale;
    point3 center;
    point3 pixel00_loc;
    vec3 pixel_delta_u, pixel_delta_v;
    vec3 u, v, w; // camera coordinate system basis
    vec3 defocus_disk_u, defocus_disk_v; // vectors for defocus effect

    void initialize() {
        image_height = int(image_width / aspect_ratio);
        if (image_height < 1) image_height = 1;

        pixel_samples_scale = 1.0 / samples_per_pixel;
        center = lookfrom;

        // converting field of view into height of viewport and then width according to aspect
        auto theta = degrees_to_radians(vfov);
        auto half_view_height = std::tan(theta / 2);
        auto viewport_height = 2.0 * half_view_height * focus_dist;
        auto viewport_width = viewport_height * (double(image_width) / image_height);

        // camera frame u, v, w calculation based on lookfrom and lookat
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        vec3 viewport_u = viewport_width * u;
        vec3 viewport_v = viewport_height * -v;

        // how far to move in image space to reach next pixel
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // where top left pixel is
        point3 viewport_upper_left = center - focus_dist * w - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        // if we want to simulate defocus then we need to build disk radius
        auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;
    }

    ray get_ray(int x, int y) const {
        // pick a random point in pixel square to anti-alias
        vec3 random_offset = sample_square();
        point3 pixel_sample = pixel00_loc
                            + ((x + random_offset.x()) * pixel_delta_u)
                            + ((y + random_offset.y()) * pixel_delta_v);

        // if no defocus just send from center else simulate a lens disk
        point3 ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
        vec3 ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
        // pick point inside unit square centered at origin
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    point3 defocus_disk_sample() const {
        // pick point from unit disk for simulating aperture
        vec3 p = random_in_unit_disk();
        return center + p.x() * defocus_disk_u + p.y() * defocus_disk_v;
    }

    color ray_color(const ray& r, int depth, const hittable& world) const {
        if (depth <= 0) {
            return color(0, 0, 0);
        }

        hit_record rec;
        if (world.hit(r, interval(0.001, infinity), rec)) {
            ray scattered;
            color attenuation;
            if (rec.surface_material->scatter(r, rec, attenuation, scattered)) {
              return attenuation * ray_color(scattered, depth - 1, world);
          }
             else {
                return color(0, 0, 0);
            }
        }

        // background sky gradient from white to blue
        vec3 unit_dir = unit_vector(r.direction());
        double t = 0.5 * (unit_dir.y() + 1.0);
        return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
    }
};

#endif