#include <iostream>

#include "utils.h"

int main(int argc, char *argv[]) {
    // std::cout << argc << std::endl;
    // if (argc > 1)
    //     for (int i = 0; i < argc; ++i)
    //         std::cout << argv[i] << std::endl;

    utils::readFile("../data/Points_[1.0e+01]_Noise_[030]_Normal.bin");



    return 0;
}