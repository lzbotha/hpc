#include <iostream>
#include <vector>

#include "grid.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    using namespace std;
    // std::cout << argc << std::endl;
    // if (argc > 1)
    //     for (int i = 0; i < argc; ++i)
    //         std::cout << argv[i] << std::endl;
    // int bytes = utils::getFileSize("../data/Points_[2.0e+08]_Noise_[030]_Normal.bin");
    // float * arr = utils::readFile("../data/Points_[2.0e+08]_Noise_[030]_Normal.bin");

    // for (int i = 0; i < 10; ++i)
    //     cout << arr[i][0] << "\t" << arr[i][1] << endl;

    Grid g(20, 20);
    g.populateFromFile("../data/Points_[2.0e+08]_Noise_[030]_Normal.bin");
    g.print();
    return 0;
}