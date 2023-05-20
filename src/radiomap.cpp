#include <radiomap.hpp>
#include <filesystem>

namespace fs = std::filesystem;

void District::read_file(int district_num) {
    char *folder_path;
    if (district_num == 1) {
        folder_path = "../data/preprocessed/radiomap/district1";
    } else if (district_num == 2) {
        folder_path = "../data/preprocessed/radiomap/district2";
    } else if (district_num == 3) {
        folder_path = "../data/preprocessed/radiomap/district3";
    } else if (district_num == 4) {
        folder_path = "../data/preprocessed/radiomap/district4";
    } else if (district_num == 5) {
        folder_path = "../data/preprocessed/radiomap/district5";
    } else if (district_num == 6) {
        folder_path = "../data/preprocessed/radiomap/district6";
    } else if (district_num == 7) {
        folder_path = "../data/preprocessed/radiomap/district7";
    }

    for (int i = 1; i < 6; i++) {
        // char *file_path = folder_path + "/PP_D" + itoa(district_num) + "_" + itoa(i) + ".csv";
        // char *file_path = "../data/preprocessed/radiomap/district1/PP_D1_1.csv";
        // TODO: read data

    }
    
}

void RadioMap::read_file() {
    districts = (District **) calloc(sizeof(District *), 7);
    for (int i = 1; i < 8; i++) {
        District *district = (District *) malloc(sizeof(District));
        district->read_file(i);

        districts[i - 1] = district;
    }
}