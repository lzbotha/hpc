#include <iostream>
#include <fstream>
#include <string>

#include "utils.h"

int utils::getFileSize(std::string filename) {
    using namespace std;

    ifstream file(filename, std::ifstream::ate | std::ios::binary);
    return file.tellg();
}

float * utils::readFile(std::string filename) {
    using namespace std;
    // TODO: add a check that floats are 32 bits on this architecture

    // Opens the file and set position at end of file
    ifstream file(filename, std::ifstream::ate | std::ios::binary);
    int bytes = file.tellg();

    // Move back to the start of the file
    file.seekg(ios_base::beg);

    float * arr = new float [bytes/4];
    float fileRead[1024];
    int counter = 0;

    for (int i = 0; i < bytes; i += 1024 * sizeof(float)){
        file.read(reinterpret_cast<char*>(&fileRead), 1024 * sizeof(float));

        for (int j = 0; j < 1024; j+=2){
            arr[counter] = fileRead[j];
            arr[counter + 1] = fileRead[j + 1];
            counter += 2;
        }
    }
    // ./tool  11.50s user 5.90s system 19% cpu 1:28.45 total

    file.close();

    return arr;
}

bool utils::outputToCSV(float * arr, int rows, int cols, std::string filename) {
    using namespace std;

    ofstream file(filename);

    // first cell in first line is blank
    file << "";

    // add bin numbers
    for (int col = 0; col < cols; ++col)
        file << "," << col;
    file << endl;

    for (int row = 0; row < rows; ++row) {
        // add the row number
        file << row;
        // add the value at (row, col)
        for (int col = 0; col < cols; ++ col) {
            file << "," << arr[row * rows + col];
        }
        file << endl;
    }

    file.close();

    return true;
}