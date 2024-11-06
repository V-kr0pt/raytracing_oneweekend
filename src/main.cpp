#include "color.h"
#include "vec3.h"
#include "ray.h"
#include <iostream> 

bool hit_sphere(const point3& center, double radius, const ray& r){
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0*dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}

color ray_color(const ray& r){
    point3 sphere_center(0, 0, -1);
    if (hit_sphere(sphere_center, 0.5, r)){
        return color(1, 0, 0);
    }


    vec3 unit_direction = unit_vector(r.direction());
    auto alpha = 0.5*(unit_direction.y()+1); //unit_direction is in the range -1 to 1, alpha has to be in the range 0 to 1
    return (1-alpha)*color(1, 1, 1) + alpha*color(0, 0, 1);
}

int main(){
    // Image size
    auto aspect_ratio = 16.0 / 9.0;
    int width_img = 400;
    int height_img = int(width_img / aspect_ratio);
    height_img = (height_img < 1) ? 1 : height_img;

    // Camera
    auto focal_length = 1;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height*(double(width_img)/height_img); // it can be different from aspect_ratio
    auto camera_center = point3(0, 0, 0);

    // vectors from the viewport
    auto viewport_u = vec3(viewport_width, 0, 0); // left to right
    auto viewport_v = vec3(0, -viewport_height, 0); //up to down

    // Delta vectors 
    auto pixel_delta_v = viewport_v / height_img;
    auto pixel_delta_u = viewport_u / width_img;

    // Calculate the location of the upper left pixel.
    auto upper_left_corner = camera_center - viewport_u/2 - viewport_v/2 - vec3(0,0,focal_length);
    auto pixel00_loc = upper_left_corner + 0.5*(pixel_delta_u+pixel_delta_v);


    // Render
    std::cout << "P3\n" << width_img << " " << height_img << "\n" << "255\n";

    for (int j = 0; j < height_img; j++){
        std::clog << "\r Scanlines remaining: " << (height_img - j) << " " << std::flush;
        for (int i = 0; i < width_img; i++){
            auto pixel_center = pixel00_loc + i*pixel_delta_u + j*pixel_delta_v;
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\nFinished :)\n" << std::flush;
}
