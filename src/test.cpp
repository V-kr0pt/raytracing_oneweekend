#include <iostream>

int main() {

    // Image

    int image_width = 256;
    int image_height = 256;

    // Render

    /* P3 is the header saying it's a PPM format.
     In the next line we define the image width and height.
        The last number is the maximum color value. (8-bit color depth in this case)
    */ 
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n"; 

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height-j) << ' ' << std::flush; // Print the remaining scanlines
        for (int i = 0; i < image_width; i++) {
            // rgb color of each pixel with range 0.0 to 1.0
            auto r = double(i) / (image_width-1); // change the color based on the width position of the pixel
            auto g = double(j) / (image_height-1); // change the color based on the height position of the pixel
            auto b = 0.0; // set the blue color to 0

            // Convert the color to 0-255 range
            int ir = int(255.999 * r); // 255.999 is used to round the number to the nearest bigger integer 
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);
            // Print the color in the format of PPM
            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::clog << '\n' << std::flush;
}