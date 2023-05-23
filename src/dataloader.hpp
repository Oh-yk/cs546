#ifndef DATALOADER_H
#define DATALOADER_H

#include <string>
#include <vector>

using namespace std;

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

#endif /* DATALOADER_H */