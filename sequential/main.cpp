#include <iostream>
#include <vector>
#include <ctime>

#include "grid.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    using namespace std;

    clock_t start;
    start = std::clock();

    Grid g(4096, 4096);
    cout << "Creating grid object: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << endl;
    start = std::clock();

    g.populateFromFile("../data/Points_[2.0e+08]_Noise_[030]_Normal.bin");
    cout << "Reading file into grid: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << endl;
    start = std::clock();

    g.applyMedianFilter(3);
    cout << "Applying median filter: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << endl;
    start = std::clock();
    
    g.printToFile("Bins_[2.0e+08].csv");
    cout << "Printing to file: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << endl;
    // g.print();
    return 0;
}