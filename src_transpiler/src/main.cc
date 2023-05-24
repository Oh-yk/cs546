#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "knn.h"

#include "transpiler/data/tfhe_data.h"
#include "xls/common/logging/logging.h"

//using namespace std;
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage:\n"
        "./positioning <testset #(1~7)>\n");
        return -1;
    }

    int testset_num = atoi(argv[1]);

    // generate a keyset
    TFHEParameters params(120);

    // generate a random key
    // Note: In real applications, a cryptographically secure seed needs to be
    // used.
    std::array<uint32_t, 3> seed = {314, 1592, 657};
    TFHESecretKeySet key(params, seed);

    // Encrypt
    auto encrypted_num = Tfhe<int>::Encrypt(n, key);
    cout << "Encryption done" << endl;
    cout << "Initial state check by decryption: " << endl;
    cout << "Decrypted input: " << encrypted_num.Decrypt(key) << endl;

    // Perform computation
    cout << "\t\t\t\t\tServer side computation:" << endl;
    Tfhe<int> encryptedResult(params);

    absl::Time start_time = absl::Now();
    double cpu_start_time = clock();

    XLS_CHECK_OK(positioning(encryptedResult, encrypted_num, key.cloud()));

    double cpu_end_time = clock();
    absl::Time end_time = absl::Now();
    cout << "\t\t\t\t\tComputation done" << endl;
    cout << "\t\t\t\t\tTotal time: "
         << absl::ToDoubleSeconds(end_time - start_time) << " secs" << endl;
    cout << "\t\t\t\t\t  CPU time: "
         << (cpu_end_time - cpu_start_time) / 1'000'000 << " secs" << endl;

    cout << "Decrypted result: District #";
    // Decrypt results.
    cout << encryptedResult.Decrypt(key) << endl;
    cout << "Decryption done" << endl << endl;

    //positioning(testset_num);
    return 0;
}