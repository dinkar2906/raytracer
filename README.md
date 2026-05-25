# Ray Tracer

A CPU-based ray tracer written from scratch in C++ implementing the core algorithms
from *Ray Tracing in One Weekend* (Peter Shirley). Produces physically-based renders
with realistic lighting, shadows, and materials.

![Render 1](image.png)<img width="600" height="337" alt="anotherview" src="https://github.com/user-attachments/assets/93f1ce79-ddd8-48eb-9a72-923f875d1b98" />
[Uploading anotherview.ppm…]()
![Uploading another.png…]()


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
