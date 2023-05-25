#include "knn.hpp"
#include <vector>

int K = 3;

class DistanceInfo {
    public:
        int district;
        unsigned long long distance;
};

// /* KNN Functions */
// static bool cmp(DistanceInfo &e1, DistanceInfo &e2) {
//     return e1.distance < e2.distance;
// }

unsigned long long KNN::calculate_distance_squared(Rss sample[24], Rss test[24]) {
    unsigned long long distance = 0;
    for (int t = 0; t < 24; t++) {
        bool bssid_matched = false;
        
        for (int p = 0; p < 24; p++) {
            if (strcmp(sample[p].bssid, test[t].bssid) == 0) {
                distance += (sample[p].rss - test[t].rss) * (sample[p].rss - test[t].rss);
                bssid_matched = true;
            }
        }

        if (!bssid_matched) {
            distance += 10000000000;
        }
    }
    return distance;
}

int KNN::run() {
    DistanceInfo *distances;
    distances = (DistanceInfo *) malloc(sizeof(DistanceInfo) * 35);
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 5; j++) {
            unsigned long long distance = calculate_distance_squared(radiomap[i][j], test);
            distances[i * 7 + j] = DistanceInfo { i, distance };
        }
    }
    
    // sort(distances.begin(), distances.end(), cmp);
    
    int count[7] = {0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < K; i++) {
        count[distances[i].district] += 1;
    }

    int ans = 0;
    int max = 0;
    for (int i = 0; i < 7; i++) {
        if (count[i] > max) {
            ans = i + 1;
            max = count[i];
        }
    }
    return ans;
}