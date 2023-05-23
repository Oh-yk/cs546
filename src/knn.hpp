#ifndef KNN_H
#define KNN_H

#include "radiomap.hpp"

class KNN {
    private:
        RadioMap radiomap;
        Point test;
        unsigned long long calculate_distance_squared(Point sample, Point test);

    public:
        KNN (RadioMap r, Point t) { radiomap = r; test = t; }
        int run();
};

#endif /* KNN_H */