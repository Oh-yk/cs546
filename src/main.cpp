#include <iostream>
#include "knn.hpp"
#include "dataloader.hpp"
#include "radiomap.hpp"
#include "testset.hpp"

using namespace std;

void positioning(int testset_num) {
    cout << "Reading radio map..." << endl;
    RadioMap radiomap = RadioMap();
    radiomap.read_file();

    cout << "Reading testset..." << endl;
    Data testset = Data();
    testset.read_test_file(testset_num);

    cout << "Positioning..." << endl;
    KNN knn(radiomap, testset);
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