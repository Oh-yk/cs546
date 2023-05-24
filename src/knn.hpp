#ifndef KNN_H
#define KNN_H

#include <iostream>
#include <vector>

using namespace std;

/* DATA LOADER */
class Rss {
    public:
        string bssid;
        int rss;
};

class Point {
    private:
        void read_file(string file_path);
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

/* KNN */
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

void positioning(int testset_num);

#endif /* KNN_H */