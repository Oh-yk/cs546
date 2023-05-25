#ifndef INFO_H
#define INFO_H

#include <vector>
#include "knn.hpp"

using namespace std;

class Point {
    private:
        void read_file(char *file_path);
    public:
        vector<Rss> rss_array;
        void read_radiomap_file(int district_num, int index);
        void read_test_file(int test_point_num);
};

/* RADIOMAP */
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

#endif /* INFO_H */