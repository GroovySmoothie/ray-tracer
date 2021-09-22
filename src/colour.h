#ifndef COLOUR_H
#define COLOUR_H

#include "vec3.h"
#include "rtweekend.h"

void write_colour(unsigned char* pixel, colour pixel_colour) {
    // Write the translated [0,255] value of each colour component.
    pixel[0] = static_cast<char>(255.999 * pixel_colour.x());
    pixel[1] = static_cast<char>(255.999 * pixel_colour.y());
    pixel[2] = static_cast<char>(255.999 * pixel_colour.z());
}

void write_colour(unsigned char* pixel, colour pixel_colour, int samples_per_pixel) {
    auto r = pixel_colour.x();
    auto g = pixel_colour.y();
    auto b = pixel_colour.z();

    // Divide the color by the number of samples and gamma-correct for gamma=2.0.
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Write the translated [0,255] value of each colour component.
    pixel[0] = static_cast<char>(255.999 * r);
    pixel[1] = static_cast<char>(255.999 * g);
    pixel[2] = static_cast<char>(255.999 * b);
}

#endif