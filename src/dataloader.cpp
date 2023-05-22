#include "dataloader.hpp"
#include <string>
#include <fstream>

using namespace std;

void Point::read_file(string file_path) {
    fstream fs;
    fs.open(file_path, ios::in);
    for (int i = 0; i < 25; i++) {
        string bssid;
        string rss_buf;
        getline(fs, bssid, ',');
        getline(fs, rss_buf, ',');

        Rss rss = Rss{bssid, stof(rss_buf)};
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