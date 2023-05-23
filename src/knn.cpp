#include "knn.hpp"
#include "dataloader.hpp"
#include "radiomap.hpp"
#include <math.h>
#include <tuple>

int K = 3;

static bool cmp(tuple<int, float> &e1, tuple<int, float> &e2) {
    return get<1>(e1) < get<1>(e2);
}

float KNN::calculate_distance_squared(Point sample, Point test) {
    float distance = 0;
    for (int t = 0; t < 25; t++) {
        bool bssid_matched = false;
        
        for (int p = 0; p < 25; p++) {
            if (sample.rss_array[p].bssid.compare(test.rss_array[t].bssid) == 0) {
                distance += pow(sample.rss_array[p].rss - test.rss_array[t].rss, 2.0f);
                bssid_matched = true;
            }
        }

        if (!bssid_matched) {
            distance += 10000; //TODO: find reasonable value for this.
        }
    }
    return distance;
}

int KNN::run() {
    vector<tuple<int, float>> distances;
    for (int i = 0; i < 7; i++) {
        District district = radiomap.districts_data[i];
        for (int j = 0; j < 5; j++) {
            Point sample = district.points_data[j];
            float distance = calculate_distance_squared(sample, test);
            distances.push_back(make_tuple(i, distance));
        }
    }

    sort(distances.begin(), distances.end(), cmp);
    
    vector<int> count = {0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < K; i++) {
        count[get<0>(distances[i])] += 1;
    }

    int ans = 0;
    int max = 0;
    // printf("%d %d %d %d %d %d %d\n", count[0], count[1], count[2], count[3], count[4], count[5], count[6]);
    for (int i = 0; i < 7; i++) {
        if (count[i] > max) {
            ans = i + 1;
            max = count[i];
        }
    }

    return ans;
}