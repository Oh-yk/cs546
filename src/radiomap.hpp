#ifndef RADIOMAP_H
#define RADIOMAP_H

#include "dataloader.hpp"
#include <vector>

class District {   
    public:
        vector<Point> points_data;
        void read_file(int district_num);
};

class RadioMap {   
    public:
        vector<District> districts_data;
        void construct_radiomap();
};

#endif /* RADIOMAP_H */