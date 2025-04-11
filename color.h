#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "interval.h"
#include <iostream>

using color = vec3;

// converts linear RGB component to gamma corrected (sRGB-like)
inline double linear_to_gamma(double value_linear) {
    if (value_linear > 0)
        return std::sqrt(value_linear); // gamma 2.0 correction
    return 0; // black otherwise
}

// write final pixel color to output stream in PPM format
void write_color(std::ostream& out, const color& raw_color) {
    // apply gamma correction
    double r_corrected = linear_to_gamma(raw_color.x());
    double g_corrected = linear_to_gamma(raw_color.y());
    double b_corrected = linear_to_gamma(raw_color.z());

    // clamp values before conversion
    static const interval intensity(0.000, 0.999);
    int r_byte = int(256 * intensity.clamp(r_corrected));
    int g_byte = int(256 * intensity.clamp(g_corrected));
    int b_byte = int(256 * intensity.clamp(b_corrected));

    // write pixel as ASCII text
    out << r_byte << ' ' << g_byte << ' ' << b_byte << '\n';
}

#endif
