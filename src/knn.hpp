#ifndef KNN_H
#define KNN_H

#include "radiomap.hpp"
#include <iostream>

using namespace std;

class KNN {
    private:
        RadioMap radiomap;
        Point test;
        unsigned long long calculate_distance_squared(Point sample, Point test);

    public:
        KNN (Point t) {
            test = t;
            cout << "Reading radio map..." << endl;
            RadioMap r = RadioMap();
            r.construct_radiomap();
            radiomap = r;
        };
        int run();
};

#endif /* KNN_H */