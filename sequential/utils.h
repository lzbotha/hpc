#ifndef _UTILS
#define _UTILS

#include <vector>

namespace utils {
    int getFileSize(std::string filename);
    std::vector<std::vector<float>> readFile(std::string filename);

    bool outputToCSV(std::vector<std::vector<float>> & arr, std::string filename);
}

#endif