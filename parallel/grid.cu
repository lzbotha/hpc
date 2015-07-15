#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>
#include <omp.h>
#include <cuda_runtime.h>

#include "grid.h"
#include "utils.h"

Grid::Grid(int rows, int cols) : r(rows), c(cols){
    this->grid = new int[r * c];
    this->clear();
}

Grid::~Grid() {
    delete this->grid;
}

int Grid::rows() {return this->r;}
int Grid::cols() {return this->c;}

void Grid::clear() {
    for (int i = 0; i < this->r * this->c; ++i)
        grid[i] = 0;
}

void Grid::print() {
    using namespace std;
    for (int row = 0; row < this->r; ++row){
        for (int col = 0; col < this->c; ++col) {
            cout << (*this)(row, col) << "\t";
        }
        cout << endl;
    }
}

void Grid::populateFromFile(std::string filename) {
    using namespace std;

    int points = utils::getFileSize(filename) / sizeof(float) / 2;
    float * values = utils::readFile(filename);

    float bucket_row_width = 1.0f / this->r;
    float bucket_col_width = 1.0f / this->c;

    for (int p = 0; p < points; ++p){
        float x = values[2 * p];
        float y = values[2 * p + 1];

        int bucket_row = (int)(x / bucket_row_width);
        if (bucket_row >= this->r)
            bucket_row = this->r - 1;

        int bucket_col = (int)(y / bucket_col_width);
        if (y >= this->c)
            bucket_col = this->c - 1;

        ++this->grid[bucket_col + bucket_row * this->r];
    }

    delete values;
}

void Grid::populateFromArray(int points, float * values) {
    using namespace std;

    float bucket_row_width = 1.0f / this->r;
    float bucket_col_width = 1.0f / this->c;

    for (int p = 0; p < points; ++p){
        float x = values[2 * p];
        float y = values[2 * p + 1];

        int bucket_row = (int)(x / bucket_row_width);
        if (bucket_row >= this->r)
            bucket_row = this->r - 1;

        int bucket_col = (int)(y / bucket_col_width);
        if (y >= this->c)
            bucket_col = this->c - 1;

        ++this->grid[bucket_col + bucket_row * this->r];
    }
}


// int Grid::medianFilter(int row, int col, int diameter) {
//     using namespace std;
//     vector<int> values;

//     int top = utils::clamp(row - (diameter - 1) / 2, 0, this->r - 1);
//     int bottom = utils::clamp(row + (diameter - 1) / 2, 0, this->r - 1);
//     int left = utils::clamp(col - (diameter - 1) / 2, 0, this->c - 1);
//     int right = utils::clamp(col + (diameter - 1) / 2, 0, this->c - 1);

//     // cout << "top: " << top << endl;
//     // cout << "bottom: " << bottom << endl;
//     // cout << "left: " << left << endl;
//     // cout << "right: " << right << endl;

//     for (int r = top; r <= bottom; ++r) {
//         for (int c = left; c <= right; ++c) {
//             values.emplace_back((*this)(r, c));
//         }
//     }
//     // cout << values.size() << endl;
//     // myvector.insert (it+2,anothervector.begin(),anothervector.end());

//     int middle = (values.size() - 1) / 2;
//     // cout << middle << endl;

//     nth_element(values.begin(), values.begin()+middle, values.end());

//     return values[middle];
// }

int Grid::medianFilter(int row, int col, int diameter) {
    using namespace std;

    int top = utils::clamp(row - (diameter - 1) / 2, 0, this->r - 1);
    int bottom = utils::clamp(row + (diameter - 1) / 2, 0, this->r - 1);
    int left = utils::clamp(col - (diameter - 1) / 2, 0, this->c - 1);
    int right = utils::clamp(col + (diameter - 1) / 2, 0, this->c - 1);

    int num_values = (bottom - top + 1) * (right - left + 1);
    int values[num_values];
    int count = 0;

    // for (int r = top; r <= bottom; ++r) {
    //     for (int c = left; c <= right; ++c) {
    //         values[count] = (*this)(r, c);
    //         ++count;
    //     }
    // }

    for (int r = top; r <= bottom; ++r) {
        copy(
            grid + left + r * this->r,
            grid + right + r * this->r + 1,
            values + count
        );
        count += right - left + 1;
    }

    int middle = (num_values - 1) / 2;
    // cout << middle << endl;

    nth_element(values, values + middle, values + num_values);
    return values[middle];
}

void Grid::applyMedianFilter(int diameter) {
    using namespace std;

    int * new_grid = new int[this->r * this->c];

    for (int row = 0; row < this->r; ++row)
        for (int col = 0; col < this->c; ++col)
            new_grid[row * this->r + col] = this->medianFilter(row, col, diameter);

    delete [] grid;
    grid = new_grid;    
}

void Grid::printToFile(std::string filename) {
    using namespace std;
    utils::outputToCSV(this->grid, this->r, this->c, filename);
}