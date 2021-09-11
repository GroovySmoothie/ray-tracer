#include <iostream>
#include "stb_image_write.h"
#include "vec3.h"
#include "colour.h"

using namespace std;

const int image_width = 256;
const int image_height = 256;
const int comps = 3; //3 for RGB, 4 for RGBA

int pixel_index(int x, int y) {
    return (image_height-y-1)*image_width*comps+x*comps;
}

int main() {
    // Image
    const string image_name = "image.png";
    unsigned char img_rgb[image_width*image_height*comps];

    // Render
    for (int j = image_height-1; j >= 0; --j) {
        cout << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            colour pixel_colour(double(i)/(image_width-1), double(j)/(image_height-1), 0.25);

            unsigned char* pixel_ptr = &img_rgb[pixel_index(i, j)];
            write_colour(pixel_ptr, pixel_colour);
        }
    }
    cout << "\nDone scanning.\n";
    auto success = stbi_write_png(image_name.c_str(),
                                  image_width,
                                  image_height,
                                  3,
                                  img_rgb,
                                  sizeof(img_rgb)/image_height);
    if(!success) {
        cout << "Something went wrong" << endl;
    } else {
        cout << "Image created at " + image_name << endl;
    }
    return 0;
}


