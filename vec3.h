#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

// just a vector class for 3d space 
// contains normal vector methods and some specific methods just for our ray tracer 
class vec3 {
public:
    double e[3];

    vec3() : e{0, 0, 0} {}
    vec3(double x_, double y_, double z_) : e{x_, y_, z_} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[](int idx) const { return e[idx]; }
    double& operator[](int idx) { return e[idx]; }

    vec3& operator+=(const vec3& other) {
        e[0] += other.e[0];
        e[1] += other.e[1];
        e[2] += other.e[2];
        return *this;
    }

    vec3& operator*=(double scalar) {
        e[0] *= scalar;
        e[1] *= scalar;
        e[2] *= scalar;
        return *this;
    }

    vec3& operator/=(double divisor) {
        return *this *= 1 / divisor;
    }

    double length() const {
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    static vec3 random() {
        return vec3(random_double(), random_double(), random_double());
    }

    // generating a random point in the space 
    static vec3 random(double min_, double max_) {
        return vec3(random_double(min_, max_), random_double(min_, max_), random_double(min_, max_));
    }

    // if floating point is too low then we ignore it 
    bool near_zero() const {
        auto eps = 1e-8;
        return std::fabs(e[0]) < eps && std::fabs(e[1]) < eps && std::fabs(e[2]) < eps;
    }
};

// point3 is just vec3 but we use it just to represent a point 
using point3 = vec3;

// print vector like "x y z"
inline std::ostream& operator<<(std::ostream& out_stream, const vec3& vec) {
    return out_stream << vec.e[0] << ' ' << vec.e[1] << ' ' << vec.e[2];
}

// vector addition
inline vec3 operator+(const vec3& a, const vec3& b) {
    return vec3(a.e[0] + b.e[0], a.e[1] + b.e[1], a.e[2] + b.e[2]);
}

// vector subtraction
inline vec3 operator-(const vec3& a, const vec3& b) {
    return vec3(a.e[0] - b.e[0], a.e[1] - b.e[1], a.e[2] - b.e[2]);
}

// element-wise multiply
inline vec3 operator*(const vec3& a, const vec3& b) {
    return vec3(a.e[0] * b.e[0], a.e[1] * b.e[1], a.e[2] * b.e[2]);
}

// scalar multiply (scalar * vec)
inline vec3 operator*(double scale, const vec3& v) {
    return vec3(scale * v.e[0], scale * v.e[1], scale * v.e[2]);
}

// scalar multiply (vec * scalar)
inline vec3 operator*(const vec3& v, double scale) {
    return scale * v;
}

// divide by scalar
inline vec3 operator/(const vec3& v, double divisor) {
    return (1 / divisor) * v;
}

// dot product
inline double dot(const vec3& a, const vec3& b) {
    return a.e[0]*b.e[0] + a.e[1]*b.e[1] + a.e[2]*b.e[2];
}

// cross product
inline vec3 cross(const vec3& a, const vec3& b) {
    return vec3(
        a.e[1]*b.e[2] - a.e[2]*b.e[1],
        a.e[2]*b.e[0] - a.e[0]*b.e[2],
        a.e[0]*b.e[1] - a.e[1]*b.e[0]
    );
}

// normalize vector
inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

// this is to alter the properties of camera 
// gives random point inside unit disk (for defocus blur etc.)
inline vec3 random_in_unit_disk() {
    while (true) {
        auto pt = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (pt.length_squared() < 1) return pt;
    }
}

// gives random unit length vector (uniformly distributed)
inline vec3 random_unit_vector() {
    while (true) {
        auto rand_vec = vec3::random(-1, 1);
        auto mag_sq = rand_vec.length_squared();
        if (mag_sq > 1e-160 && mag_sq <= 1) return rand_vec / std::sqrt(mag_sq);
    }
}

// returns vector in same hemisphere as normal
inline vec3 random_on_hemisphere(const vec3& normal) {
    vec3 sphere_vec = random_unit_vector();
    return dot(sphere_vec, normal) > 0.0 ? sphere_vec : -sphere_vec;
}

// reflect v along normal
inline vec3 reflect(const vec3& incident, const vec3& normal) {
    return incident - 2 * dot(incident, normal) * normal;
}

// calculate refraction vector based on Snell's Law
inline vec3 refract(const vec3& uv, const vec3& normal, double eta_ratio) {
    auto cos_theta = std::fmin(dot(-uv, normal), 1.0);
    vec3 perp = eta_ratio * (uv + cos_theta * normal);
    vec3 parallel = -std::sqrt(std::fabs(1.0 - perp.length_squared())) * normal;
    return perp + parallel;
}

#endif 
