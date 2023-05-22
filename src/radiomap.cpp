#include "radiomap.hpp"
#include <vector>
#include <string>

using namespace std;

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