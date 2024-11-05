#include "color.h"
#include "vec3.h"
#include <iostream> 


int main(){
    // Image size
    int width_img = 256;
    int height_img = 256;

    // Render
    std::cout << "P3\n" << width_img << " " << height_img << "\n" << "255\n";

    for (int j = 0; j < height_img; j++){
        std::clog << "\r Scanlines remaining: " << (height_img - j) << " " << std::flush;
        for (int i = 0; i < width_img; i++){
            auto r = 1 - double(i) / (width_img - 1);
            auto g = double(j) / (height_img - 1);
            auto b = 0;
            auto pixel_color = color(r, g, b);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\nFinished :)\n" << std::flush;
}
