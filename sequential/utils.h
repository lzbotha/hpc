#ifndef _UTILS
#define _UTILS

namespace utils {
    int getFileSize(std::string filename);
    float ** readFile(std::string filename);

    bool outputToCSV(float ** arr, int size, std::string filename);
}

#endif