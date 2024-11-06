#include "common_header.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"


color ray_color(const ray& r, const hittable& world){
    hit_record rec;

    if (world.hit(r, 0, 100, rec)){
        return 0.5*(rec.normal + color(1,1,1)); // mapping -1 to 1 -> 0 to 1
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

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5)); // add a sphere with center at (0,0,-1) and radius 0.5 to the world
    world.add(make_shared<sphere>(point3(0,-100.5, -1), 100));// add a big sphere under the small one to act as the ground


    // Render
    std::cout << "P3\n" << width_img << " " << height_img << "\n" << "255\n";

    for (int j = 0; j < height_img; j++){
        std::clog << "\r Scanlines remaining: " << (height_img - j) << " " << std::flush;
        for (int i = 0; i < width_img; i++){
            auto pixel_center = pixel00_loc + i*pixel_delta_u + j*pixel_delta_v;
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\nFinished :)\n" << std::flush;
}
