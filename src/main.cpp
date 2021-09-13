#include <iostream>
#include "stb_image_write.h"
#include "vec3.h"
#include "colour.h"
#include "ray.h"

using namespace std;

// Image
const auto aspect_ratio = 16.0 / 9.0;
const int image_width = 400;
const int image_height = static_cast<int>(image_width / aspect_ratio);
const int comps = 3;

colour ray_colour(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*colour(1.0, 1.0, 1.0) + t*colour(0.5, 0.7, 1.0);
}

int main() {
    // Image
    const string image_name = "image.png";
    unsigned char img_rgb[image_width*image_height*comps];

    // Camera
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    point3 origin = point3(0, 0, 0);
    vec3 horizontal = vec3(viewport_width, 0, 0);
    vec3 vertical = vec3(0, viewport_height, 0);
    vec3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);


    // Render
    for (int y = image_height-1; y >= 0; --y) {
        cout << "\rScanlines remaining: " << y << ' ' << std::flush;
        for (int x = 0; x < image_width; ++x) {
            auto u = double(x) / (image_width-1);
            auto v = double(y) / (image_height-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            colour pixel_colour = ray_colour(r);

            unsigned char* pixel_ptr = &img_rgb[(image_height-y-1)*image_width*comps+x*comps];
            write_colour(pixel_ptr, pixel_colour);
        }
    }
    cout << "\nDone scanning.\n";
    auto success = stbi_write_png(image_name.c_str(),
                                  image_width,
                                  image_height,
                                  3,
                                  img_rgb,
                                  static_cast<int>(sizeof(img_rgb)/image_height));
    if(!success) {
        cout << "Something went wrong" << endl;
    } else {
        cout << "Image created at " + image_name << endl;
    }
    return 0;
}


