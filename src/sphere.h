#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
    public:
        sphere(const point3& center, double radius, shared_ptr<material> mat) 
        : center(center), radius(std::fmax(0,radius)), mat(mat){};
        
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override{
            vec3 oc = center - r.origin();
            auto a = r.direction().length_squared(); // dot(r,r)
            auto h = dot(r.direction(), oc); // h = b/-2
            auto c = oc.length_squared() - radius*radius; // dot(oc, oc) - R^2
            auto discriminant = h*h - a*c;


            if (discriminant < 0) // no intersection
                return false;
            
            auto sqrt_discriminant = std::sqrt(discriminant);
            auto root = (h - sqrt_discriminant) / a; // return the closest intersection

            // Check if the 2 roots are out of the range of t_min and t_max
            if (root < t_min || t_max < root){
                root = (h + sqrt_discriminant) / a;
                if (root < t_min || t_max < root)
                    return false;
            }

            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat =  mat;

            return true;

        };

    private:
        point3 center;
        double radius;
        shared_ptr<material> mat;
};

#endif