#include <iostream>
#include "knn.hpp"
#include "dataloader.hpp"
#include "radiomap.hpp"

using namespace std;

void positioning(int testset_num) {
    cout << "Reading radio map..." << endl;
    RadioMap radiomap = RadioMap();
    radiomap.construct_radiomap();

    cout << "Reading testset..." << endl;
    Point testpoint = Point();
    testpoint.read_test_file(testset_num);

    cout << "Positioning..." << endl;
    KNN knn(radiomap, testpoint);
    int result = knn.run();

    printf("Result for positioning: District %d\n", result);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage:\n"
        "./positioning <testset #(1~7)>\n");
        return -1;
    }

    int testset_num = atoi(argv[1]);

    positioning(testset_num);
    return 0;
}