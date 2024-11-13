#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera {
    public:
        double aspect_ratio = 1;
        int img_width = 100;
        int samples_per_pixel = 100; //number of samples to do antialising

        void render(const hittable& world){
            initialize();

            std::cout << "P3\n" << img_width << " " << img_height << "\n" << "255\n";

            for (int j = 0; j < img_height; j++){
                std::clog << "\r Scanlines remaining: " << (img_height - j) << " " << std::flush;
                for (int i = 0; i < img_width; i++){
                    color pixel_color(0,0,0);
                    for (int sample=0; sample < samples_per_pixel; sample++){
                        ray r = get_ray(i, j);                    
                        pixel_color += ray_color(r, world);
                    }
                    pixel_color /= samples_per_pixel;
                    write_color(std::cout, pixel_color);
                }
            }
            std::clog << "\nFinished :)\n";
        };

    private:
        int    img_height;   // Rendered image height
        point3 center;         // Camera center
        point3 pixel00_loc;    // Location of pixel 0, 0
        vec3   pixel_delta_u;  // Offset to pixel to the right
        vec3   pixel_delta_v;  // Offset to pixel below

        void initialize(){
            img_height = int(img_width / aspect_ratio);
            img_height = (img_height < 1) ? 1 : img_height;

            center = point3(0, 0, 0);

            // viewport dimensions
            auto focal_length = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height*(double(img_width)/img_height);

            // vectors from the viewport
            auto viewport_u = vec3(viewport_width, 0, 0); // left to right
            auto viewport_v = vec3(0, -viewport_height, 0); //up to down           
            // delta vectors
            pixel_delta_u = viewport_u / img_width;
            pixel_delta_v = viewport_v / img_height;           

            // Calculate the location of the upper left pixel.
            auto upper_left_corner = center - viewport_u/2 - viewport_v/2 - vec3(0,0,focal_length);
            pixel00_loc = upper_left_corner + 0.5*(pixel_delta_u+pixel_delta_v);
        }

        color ray_color(const ray& r, const hittable& world){
            hit_record rec;
            
            if (world.hit(r, 0, 100, rec)){
                return 0.5*(rec.normal + color(1,1,1)); // mapping -1 to 1 -> 0 to 1
            }

            vec3 unit_direction = unit_vector(r.direction());
            auto alpha = 0.5*(unit_direction.y()+1); //unit_direction is in the range -1 to 1, alpha has to be in the range 0 to 1
            return (1-alpha)*color(1, 1, 1) + alpha*color(0, 0, 1);
        }

        // make a ray from origin to a random sample centered in a pixel 
        ray get_ray(int i, int j){
            auto offset = sample_square();
            auto pixel_sample = pixel00_loc + (offset.x() + i)*pixel_delta_u + (offset.y()+ j)*pixel_delta_v;
            auto ray_direction = pixel_sample - center;

            return ray(center, ray_direction);
        }

        vec3 sample_square(){
            return vec3(random_double() - 0.5, random_double() - 0.5, 0);
        }


};

#endif