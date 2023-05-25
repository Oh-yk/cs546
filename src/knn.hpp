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
        Rss radiomap[7][5][24];
        Rss *test;
        unsigned long long calculate_distance_squared(Rss sample[24], Rss test[24]);

    public:
        KNN (Rss r[7][5][24], Rss t[24]) {
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 5; j++) {
                    for (int k = 0; k < 24; k++) {
                        radiomap[i][j][k] = r[i][j][k];
                    }
                }
            }
            test = t;
        };
        int run();
};

void positioning(int testset_num);

#endif /* KNN_H */