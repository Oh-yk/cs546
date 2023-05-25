#ifndef KNN_H
#define KNN_H

#include <iostream>

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
        // Rss radiomap[7][5][24];
        char* radiomap_bssid[7][5][24];
        int radiomap_rss[7][5][24];

        // Rss *test;
        char* test_bssid[24];
        int test_rss[24];
        unsigned long long calculate_distance_squared(char* sample_bssid[24], int sample_rss[24], char* test_bssid[24], int test_rss[24]);

    public:
        KNN (char* r_bssid[7][5][24], int r_rss[7][5][24], char* t_bssid[24], int t_rss[24]) {
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 5; j++) {
                    for (int k = 0; k < 24; k++) {
                        // radiomap[i][j][k] = r[i][j][k];
                        radiomap_bssid[i][j][k] = r_bssid[i][j][k];
                        radiomap_rss[i][j][k] = r_rss[i][j][k];
                    }
                }
            }
            for (int k = 0; k < 24; k++) {
                test_bssid[k] = t_bssid[k];
                test_rss[k] = t_rss[k];
            }
        };
        int run();
};

void positioning(int testset_num);

#endif /* KNN_H */