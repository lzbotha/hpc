#include <iostream>
#include <vector>
#include <ctime>

#include "grid.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    using namespace std;

    if (argc != 5) {
        cerr << "Incorrect usage" << endl;
        exit(0);
    }

    string input_file = argv[1];
    string output_file = argv[2];
    int grid_dim = atoi(argv[3]);
    int filter_dim = atoi(argv[4]);

    clock_t start, total;
    start = clock();
    total = clock();

    Grid g(grid_dim, grid_dim);
    cout << "Creating grid object ( "  << grid_dim << "): " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;
    start = std::clock();

    int points = utils::getFileSize(input_file) / sizeof(float) / 2;
    float * values = utils::readFile(input_file);
    cout << "Reading file from disk: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;
    start = std::clock();

    g.populateFromArray(points, values);
    cout << "Populating grid: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;
    start = std::clock();

    g.applyMedianFilter(filter_dim);
    cout << "Applying median filter (" << filter_dim << "): " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;
    start = std::clock();

    g.printToFile(output_file);
    cout << "Printing to file: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;

    cout << "Total: " << (clock() - total) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl << endl;

    delete[] values;
    return 0;
}