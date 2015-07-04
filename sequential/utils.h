#ifndef _UTILS
#define _UTILS

namespace utils {
    /**
    * Reads in the filesize in bytes
    */
    int getFileSize(std::string filename);
    float * readFile(std::string filename);
    int clamp(int n, int lower, int upper);

    void outputToCSV(int * arr, int rows, int cols, std::string filename);
}

#endif