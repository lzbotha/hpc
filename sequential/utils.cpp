#include <iostream>
#include <fstream>
#include <string>

#include "utils.h"

int utils::getFileSize(std::string filename) {
    using namespace std;

    ifstream file(filename, std::ifstream::ate | std::ios::binary);
    return file.tellg();
}

float ** utils::readFile(std::string filename) {
    using namespace std;
    // TODO: add a check that floats are 32 bits on this architecture

    // Opens the file and set position at end of file
    ifstream file(filename, std::ifstream::ate | std::ios::binary);
    int bytes = file.tellg();
    cout << bytes << endl;

    float** arr = new float*[bytes/8];

    // Move back to the start of the file
    file.seekg(ios_base::beg);

    for (int i = 0; i < bytes; i+= 8) {
        // Read in 2 floats from file
        arr[i/8] = new float[2];
        file.read(reinterpret_cast<char*>(&arr[i/8][0]), sizeof(float));
        file.read(reinterpret_cast<char*>(&arr[i/8][1]), sizeof(float));
    }

    file.close();

    return arr;
}

bool outputToCSV(float ** arr, int size, std::string filename) {
    using namespace std;

    ofstream file(filename);

    // first cell in first line is blank
    file << "";

    // add bin numbers
    for (int col = 0; col < size; ++col)
        file << "," << col;

    for (int row = 0; row < size; ++row) {
        // add the row number
        file << row;
        // add the value at (row, col)
        for (int col = 1; col < size; ++ col) {
            file << "," << arr[row][col];
        }
    }

    file.close();

    return true;
}