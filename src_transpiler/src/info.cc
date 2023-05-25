#include "info.h"
#include "knn.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

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

/* Running KNN */
int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage:\n"
        "./positioning <testset #(1~7)>\n");
        return -1;
    }

    int testset_num = atoi(argv[1]);

    cout << "Reading radio map..." << endl;
    RadioMap radiomap = RadioMap();
    radiomap.construct_radiomap();
    char* radiomap_bssid[7][5][24];
    int radiomap_rss[7][5][24];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 24; k++) {
                radiomap_bssid[i][j][k] = radiomap.districts_data[i].points_data[j].rss_array[k].bssid;
                radiomap_rss[i][j][k] = radiomap.districts_data[i].points_data[j].rss_array[k].rss;
            }
        }
    }

    cout << "Reading testset..." << endl;
    Point testpoint = Point();
    testpoint.read_test_file(testset_num);
    char* testpoint_bssid[24];
    int testpoint_rss[24];
    for (int i = 0; i < 24; i++) {
        testpoint_bssid[i] = testpoint.rss_array[i].bssid;
        testpoint_rss[i] = testpoint.rss_array[i].rss;
    }

    cout << "Positioning..." << endl;
    KNN knn(radiomap_bssid, radiomap_rss, testpoint_bssid, testpoint_rss);
    int result = knn.run();

    printf("Result for positioning: District %d\n", result);
    return 0;
}