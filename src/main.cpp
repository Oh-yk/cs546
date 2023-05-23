#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "knn.hpp"

using namespace std;

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