#include "knn.hpp"
#include <string>
#include <fstream>
#include <vector>

int K = 3;

/* DATA LOADER Functions*/
void Point::read_file(char *file_path) {
    fstream fs;
    fs.open(file_path, ios::in);
    char header[40];
    fs.getline(header, sizeof(header));
    for (int i = 0; i < 24; i++) {
        char bssid[30];
        char rss_buf[30];
        fs.getline(bssid, sizeof(bssid), ',');
        fs.getline(rss_buf, sizeof(rss_buf), '\n');

        Rss rss = Rss();
        rss.bssid = (char *) calloc(30, sizeof(char));
        strcpy(rss.bssid, bssid);
        rss.rss = atoi(rss_buf);
        rss_array.push_back(rss);
    }
    fs.close();
}

void Point::read_radiomap_file(int district_num, int index) {
    // string file_path = string("../data/preprocessed/radiomap/district") + string(to_string(district_num)) + string("/PP_D")
    //     + string(to_string(district_num)) + string("_") + string(to_string(index)) + string(".csv");
    char *a = (char *) "../data/preprocessed/radiomap/district";
    char b[2];
    sprintf(b, "%d", district_num);
    char *c = (char *) "/PP_D";
    char d[2];
    sprintf(d, "%d", district_num);
    char *e = (char *) "_";
    char f[2];
    sprintf(f, "%d", index);
    char *g = (char *) ".csv";

    char *file_path;
    file_path = (char *) malloc(strlen(a) + strlen(b) + strlen(c) + strlen(d) + strlen(e) + strlen(f) + strlen(g));
    strcpy(file_path, a);
    strcat(file_path, b);
    strcat(file_path, c);
    strcat(file_path, d);
    strcat(file_path, e);
    strcat(file_path, f);
    strcat(file_path, g);

    read_file(file_path);
}

void Point::read_test_file(int test_point_num) {
    // string file_path = string("../data/preprocessed/test/PP_D")
    //     + string(to_string(test_point_num)) + string("_test.csv");
    char *a = (char *) "../data/preprocessed/test/PP_D";
    char b[2];
    sprintf(b, "%d", test_point_num);
    char *c = (char *) "_test.csv";

    char *file_path;
    file_path = (char *) malloc(strlen(a) + strlen(b) + strlen(c));
    strcpy(file_path, a);
    strcat(file_path, b);
    strcat(file_path, c);

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

class DistanceInfo {
    public:
        int district;
        unsigned long long distance;
};

/* KNN Functions */
static bool cmp(DistanceInfo &e1, DistanceInfo &e2) {
    return e1.distance < e2.distance;
}

unsigned long long KNN::calculate_distance_squared(Point sample, Point test) {
    unsigned long long distance = 0;
    for (int t = 0; t < 24; t++) {
        bool bssid_matched = false;
        
        for (int p = 0; p < 24; p++) {
            if (strcmp(sample.rss_array[p].bssid, test.rss_array[t].bssid) == 0) {
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
    for (int i = 0; i < 7; i++) {
        District district = radiomap.districts_data[i];
        for (int j = 0; j < 5; j++) {
            Point sample = district.points_data[j];
            unsigned long long distance = calculate_distance_squared(sample, test);
            distances.push_back(DistanceInfo { i, distance });
        }
    }
    sort(distances.begin(), distances.end(), cmp);

    vector<int> count = {0, 0, 0, 0, 0, 0, 0};
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

/* Running KNN */
void positioning(int testset_num) {
    cout << "Reading testset..." << endl;
    Point testpoint = Point();
    testpoint.read_test_file(testset_num);

    cout << "Positioning..." << endl;
    KNN knn(testpoint);
    int result = knn.run();

    printf("Result for positioning: District %d\n", result);
}