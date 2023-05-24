#include "knn.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

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

class DistanceInfo {
    public:
        int district;
        unsigned long long distance;
};

int K = 3;

/* DATA LOADER Functions*/
void Point::read_file(string file_path) {
    fstream fs;
    fs.open(file_path, ios::in);
    string header;
    getline(fs, header);
    for (int i = 0; i < 24; i++) {
        string bssid;
        string rss_buf;
        getline(fs, bssid, ',');
        getline(fs, rss_buf, '\n');

        Rss rss = Rss{bssid, stoi(rss_buf)};
        rss_array.push_back(rss);
    }
    fs.close();
}

void Point::read_radiomap_file(int district_num, int index) {
    string file_path = string("../data/preprocessed/radiomap/district") + string(to_string(district_num)) + string("/PP_D")
        + string(to_string(district_num)) + string("_") + string(to_string(index)) + string(".csv");

    read_file(file_path);
}

void Point::read_test_file(int test_point_num) {
    string file_path = string("../data/preprocessed/test/PP_D")
        + string(to_string(test_point_num)) + string("_test.csv");

    read_file(file_path);
}

/* RADIOMAP Functions */
void District::read_file(int district_num) {
    for (int i = 1; i < 6; i++) {
        Point point = Point();
        point.read_radiomap_file(district_num, i);
        points_data.push_back(point);
    }
}

void RadioMap::construct_radiomap() {
    for (int i = 1; i < 8; i++) {
        District district = District();
        district.read_file(i);
        districts_data.push_back(district);
    }
}

/* KNN Functions */
static bool cmp(DistanceInfo &e1, DistanceInfo &e2) {
    return e1.distance < e2.distance;
}

unsigned long long KNN::calculate_distance_squared(Point sample, Point test) {
    unsigned long long distance = 0;
#pragma hls_unroll yes
    for (int t = 0; t < 25; t++) {
        bool bssid_matched = false;

#pragma hls_unroll yes
        for (int p = 0; p < 25; p++) {
            if (sample.rss_array[p].bssid.compare(test.rss_array[t].bssid) == 0) {
                distance += (sample.rss_array[p].rss - test.rss_array[t].rss) * (sample.rss_array[p].rss - test.rss_array[t].rss);
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
    vector<DistanceInfo> distances;
#pragma hls_unroll yes
    for (int i = 0; i < 7; i++) {
        District district = radiomap.districts_data[i];
#pragma hls_unroll yes
	for (int j = 0; j < 5; j++) {
            Point sample = district.points_data[j];
            unsigned long long distance = calculate_distance_squared(sample, test);
            distances.push_back(DistanceInfo { i, distance });
	}
    }

    sort(distances.begin(), distances.end(), cmp);

    vector<int> count = {0, 0, 0, 0, 0, 0, 0};
#pragma hls_unroll yes
    for (int i = 0; i < K; i++) {
        count[distances[i].district] += 1;
    }

    int ans = 0;
    int max = 0;
    // printf("%d %d %d %d %d %d %d\n", count[0], count[1], count[2], count[3], count[4], count[5], count[6]);
#pragma hls_unroll yes
    for (int i = 0; i < 7; i++) {
        if (count[i] > max) {
            ans = i + 1;
            max = count[i];
        }
    }

    return ans;
}

/* Running KNN */
#pragma hls_top
void positioning(int testset_num) {
    cout << "Reading testset..." << endl;
    Point testpoint = Point();
    testpoint.read_test_file(testset_num);

    cout << "Positioning..." << endl;
    KNN knn(testpoint);
    int result = knn.run();

    printf("Result for positioning: District %d\n", result);
}