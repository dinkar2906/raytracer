# Ray Tracer

A CPU-based ray tracer written from scratch in C++ implementing the core algorithms
from *Ray Tracing in One Weekend* (Peter Shirley). Produces physically-based renders
with realistic lighting, shadows, and materials.

<img width="600" height="337" alt="anotherview" src="https://github.com/user-attachments/assets/93f1ce79-ddd8-48eb-9a72-923f875d1b98" />
<img width="600" height="337" alt="anotherview" src="https://github.com/user-attachments/assets/68be5cc2-33df-46c6-a7f5-724a9d560d52" />



---

## Features

| Feature | Details |
|---|---|
| Materials | Lambertian (diffuse), Metal (reflective), Dielectric (glass) |
| Lighting | Physically-based diffuse scattering, reflectance, refraction |
| Camera | Configurable FOV, position, depth of field, aperture |
| Anti-aliasing | Multi-sample per pixel with random sampling |
| Rendering | Recursive ray tracing with configurable max depth |

---

## Build & Run

**Requirements:** C++17 compiler (g++ or clang++)

```bash
# Compile
g++ -std=c++17 -O2 -o raytracer main.cpp

# Render (outputs PPM format)
./raytracer > output.ppm
```

Convert PPM to PNG for easy viewing:
```bash
# Linux/Mac
convert output.ppm output.png

# Or open output.ppm directly in GIMP, Photoshop, or any image viewer
```


---

## Project Structure

```
raytracer/
├── main.cpp          # Scene setup and render loop
├── camera.h          # Camera model — FOV, aperture, depth of field
├── ray.h             # Ray class (origin + direction)
├── vec3.h            # 3D vector math
├── color.h           # Colour utilities and gamma correction
├── hittable.h        # Abstract hittable interface
├── hittable_list.h   # Scene as a list of hittable objects
├── sphere.h          # Sphere geometry
├── material.h        # Lambertian, Metal, Dielectric materials
├── interval.h        # Interval utility for ray clipping
└── rtweekend.h       # Constants, utility functions
```

---

## Implementation Notes

- No external libraries — built entirely on the C++ standard library
- Materials use physically-motivated BRDFs: Lambertian scattering, Schlick approximation for glass
- Anti-aliasing done via stratified random sampling per pixel
- Depth of field simulated via a thin-lens camera model

---

## Reference

Peter Shirley — *[Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)* (2020)

---

## Author

Dinkar Upadhyay · [GitHub](https://github.com/dinkar2906) · [LinkedIn](https://linkedin.com/in/dinkar-up)
