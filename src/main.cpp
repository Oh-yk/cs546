#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "knn.hpp"

using namespace std;

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