#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "camera.h"

int main() {

    // hittable list contains all objects that are going to be in the way of ray and 
    // it is inherited from the class hittable
    // every object is some kind of math equation and solution with a ray and 
    // that object gives us points in 3d space where we have to add color


    hittable_list scene_objects;

    auto matte_ground = make_shared<lambertian>(color(0.05, 0.05, 0.05));
    scene_objects.add(make_shared<sphere>(point3(0, -1000.5, 0), 1000, matte_ground));

    auto refractive_center = make_shared<dielectric>(1.5);
    scene_objects.add(make_shared<sphere>(point3(0, 1, 0), 1.0, refractive_center));

    auto reflective_purple = make_shared<metal>(color(0.6, 0.2, 0.9), 0.0);
    scene_objects.add(make_shared<sphere>(point3(-2.5, 1.2, -1.5), 1.0, reflective_purple));

    auto reflective_blue = make_shared<metal>(color(0.2, 0.8, 1.0), 0.0);
    scene_objects.add(make_shared<sphere>(point3(2.5, 1.0, -1.0), 1.0, reflective_blue));

    auto floating_mirror = make_shared<metal>(color(0.95, 0.95, 0.95), 0.0);
    scene_objects.add(make_shared<sphere>(point3(0, 3.2, 0.5), 0.7, floating_mirror));

    auto small_glass_orb = make_shared<dielectric>(1.5);
    scene_objects.add(make_shared<sphere>(point3(-2.5, 3.0, -1.5), 0.3, small_glass_orb));

    // There are different types of objects or same objects with differnet properties but they all share same space 

    // camera class defines a camera that is basically sending bunch of rays from single point but later on 
    // we make some changes because to simulate real life camera we don't use a point source (but in theory  we do)
    camera main_camera;
    main_camera.aspect_ratio      = 16.0 / 9.0;
    main_camera.image_width       = 600;
    main_camera.samples_per_pixel = 100;
    main_camera.max_depth         = 30;

    //VFOV stands for vertical field of view 
    // lookfrom is from where we are looking generally (0,0,0) but we can override it to change camera direction
    

    main_camera.vfov     = 40;
    main_camera.lookfrom = point3(6, 5, -3);      
    main_camera.lookat   = point3(0, 0, 0);       
    main_camera.vup      = vec3(1, 0, 0); 

    // vfov,lookfrom and lookat changes the places of camera not its properties 
    // but defocus changes the properties of camera 

    main_camera.defocus_angle = 0.3;
    main_camera.focus_dist    = 8.0;

    main_camera.render(scene_objects);
}
