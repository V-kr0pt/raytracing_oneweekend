#ifndef INTERVAL_H
#define INTERVAL_H

class interval{
    double min;
    double max;
    public:
        interval(double min, double max) : min(min), max(max){}; // constructor
        
        double clamp(double x) const{
            if (x < min) return min;
            if (x > max) return max;
            return x;
        }
        
};

#endif