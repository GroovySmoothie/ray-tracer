#include <iostream>
#include <chrono>

#include "stb_image_write.h"
#include "rtweekend.h"

#include "camera.h"
#include "colour.h"
#include "hittable_list.h"
#include "sphere.h"

using namespace std;

colour ray_colour(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return colour(0,0,0);

    if (world.hit(r, 0.001, infinity, rec)) {
        point3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5 * ray_colour(ray(rec.p, target - rec.p), world, depth-1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5*(unit_direction.y() + 1);
    return (1.0-t)*colour(1.0, 1.0, 1.0) + t*colour(0.5, 0.7, 1.0);
}

int main() {
    // Timing
    auto start = chrono::system_clock::now();

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int comps = 3;
    const int samples_per_pixel = 100;
    const int max_depth = 50;
    const string image_name = "image.png";
    unsigned char img_rgb[image_width*image_height*comps];

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,0), 100));

    // Camera
    camera cam;

    // Render
    for (int y = image_height-1; y >= 0; --y) {
        cout << "\rScanlines remaining: " << y << ' ' << std::flush;
        for (int x = 0; x < image_width; ++x) {
            colour pixel_colour(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; s++) {
                auto u = (x + random_double()) / (image_width-1);
                auto v = (y + random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_colour += ray_colour(r, world, max_depth);
            }
            unsigned char* pixel_ptr = &img_rgb[(image_height-y-1)*image_width*comps+x*comps];
            write_colour(pixel_ptr, pixel_colour, samples_per_pixel);
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

    auto end = chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    cout << "Seconds elapsed " << elapsed_seconds.count() << endl;
    return 0;
}


