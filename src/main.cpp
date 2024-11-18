#include "common_header.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"


int main(){
    // World
    hittable_list world;

    //materials
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<metal>(color(0.8, 0.8, 0.8));
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2));

    std::clog << "Materials created successfully" << std::endl;
    // objects
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5, material_center)); // add a sphere with center at (0,0,-1) and radius 0.5 to the world
    world.add(make_shared<sphere>(point3(0,-100.5, -1), 100, material_ground));// add a big sphere under the small one to act as the ground
    world.add(make_shared<sphere>(point3(-1,0,-1), 0.5, material_left));
    world.add(make_shared<sphere>(point3(1,0,-1), 0.5, material_right));

    std::clog << "Objects added to the world" << std::endl;
    

    // Initialize camera and Render
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.img_width = 400;
    std::clog << "Camera initialized." << std::endl;

    cam.render(world);

    std::clog << "Rendering completed" << std::endl;
    
}
