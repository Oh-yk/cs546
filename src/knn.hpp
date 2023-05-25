#ifndef KNN_H
#define KNN_H

#include <iostream>
#include <vector>

using namespace std;

/* DATA LOADER */
class Rss {
    public:
        char *bssid;
        int rss;
};


/* KNN */
class KNN {
    private:
        vector<vector<vector<Rss>>> radiomap;
        vector<Rss> test;
        unsigned long long calculate_distance_squared(vector<Rss> sample, vector<Rss> test);

    public:
        KNN (vector<vector<vector<Rss>>> r, vector<Rss> t) {
            radiomap = r;
            test = t;
        };
        int run();
};

void positioning(int testset_num);

#endif /* KNN_H */