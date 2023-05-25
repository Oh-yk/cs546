#include "knn.h"

int K = 3;

class DistanceInfo {
    public:
        int district;
        unsigned long long distance;
};

/* KNN Functions */
// static bool cmp(DistanceInfo &e1, DistanceInfo &e2) {
//     return e1.distance < e2.distance;
// }

unsigned long long KNN::calculate_distance_squared(char* sample_bssid[24], int sample_rss[24], char* test_bssid[24], int test_rss[24]) {
    unsigned long long distance = 0;
#pragma hls_unroll yes
    for (int t = 0; t < 24; t++) {
        bool bssid_matched = false;

        //TODO: uncomment
        // for (int p = 0; p < 24; p++) {
        //     if (strcmp(sample_bssid[p], test_bssid[t]) == 0) {
        //         distance += (sample_rss[p] - test_rss[t]) * (sample_rss[p] - test_rss[t]);
        //         bssid_matched = true;
        //     }
        // }

        if (!bssid_matched) {
            distance += 10000000000;
        }
    }
    return distance;
}

#pragma hls_top
int KNN::run() {
    DistanceInfo distances[35];
#pragma hls_unroll yes
    for (int i = 0; i < 7; i++) {
#pragma hls_unroll yes
        for (int j = 0; j < 5; j++) {
            unsigned long long distance = calculate_distance_squared(radiomap_bssid[i][j], radiomap_rss[i][j], test_bssid, test_rss);
            distances[i * 7 + j] = DistanceInfo { i, distance };
        }
    }

    // sort(distances.begin(), distances.end(), cmp);

    int count[7] = {0, 0, 0, 0, 0, 0, 0};
#pragma hls_unroll yes
    for (int i = 0; i < K; i++) {
        count[distances[i].district] += 1;
    }

    int ans = 0;
    int max = 0;
#pragma hls_unroll yes
    for (int i = 0; i < 7; i++) {
        if (count[i] > max) {
            ans = i + 1;
            max = count[i];
        }
    }
    return ans;
}