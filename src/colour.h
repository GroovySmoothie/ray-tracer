#ifndef COLOUR_H
#define COLOUR_H

#include "vec3.h"

void write_colour(unsigned char* pixel, colour pixel_colour) {
    // Write the translated [0,255] value of each colour component.
    pixel[0] = static_cast<char>(255.999 * pixel_colour.x());
    pixel[1] = static_cast<char>(255.999 * pixel_colour.y());
    pixel[2] = static_cast<char>(255.999 * pixel_colour.z());
}

#endif