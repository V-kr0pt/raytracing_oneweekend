#include "common_header.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"


int main(){
    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5)); // add a sphere with center at (0,0,-1) and radius 0.5 to the world
    world.add(make_shared<sphere>(point3(0,-100.5, -1), 100));// add a big sphere under the small one to act as the ground

    // Initialize camera and Render
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.img_width = 400;

    cam.render(world);
    
}
