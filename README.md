# Ray Tracer

This project is a simple **ray tracer** built by following the book *Ray Tracing in One Weekend* by Peter Shirley. It’s designed to help beginners understand the core concepts of ray tracing by building everything from scratch in C++.

The code is thoroughly commented to help you follow along and understand each part of the implementation.

## 🛠 Features
- Basic ray-object intersection
- Lambertian, Metal, and Dielectric materials
- Diffuse and reflective scattering
- Support for multiple objects
- Anti-aliasing
- Recursive ray color calculation
- Depth of field simulation

## ⚠️ Note on Performance

This is an **intentionally unoptimized** CPU-based ray tracer designed for educational purposes. It doesn't use any GPU acceleration (CUDA, Vulkan, etc.), so rendering complex scenes with many objects or high-resolution images will be slow.

If you’re looking to experiment with rendering more complex scenes without waiting too long, consider running the code in a **cloud environment** that provides GPU support.

## ☁️ How I Ran It

Since I don’t currently work with GPU programming, I used **Google Colab** to render scenes. Colab offers free access to GPU-backed runtime environments, making it a convenient option for testing and rendering this ray tracer.
