#ifndef COMMON_HEADER_H
#define COMMON_HEADER_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <cstdlib>


// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double(){
    // [0,1)
    return std::rand()/(RAND_MAX + 1.0);
}

inline double random_double(int rand_min, int rand_max){
    // [rand_min, rand_max)
    return rand_min + (rand_max - rand_min)*random_double();
}


// Common Headers
#include "color.h"
#include "ray.h"
#include "vec3.h"


#endif