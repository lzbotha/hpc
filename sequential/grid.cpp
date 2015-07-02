#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

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

void Grid::getRows(
    int centre, 
    int radius, 
    int & start, 
    int & end) 
{
    start = (centre - radius)<0 ? 0:(centre - radius);
    end = (centre + radius)>this->r ? this->r - 1: (centre + radius);

    if (centre > this->r || centre < 0) {
        start = -1;
        end = -1;
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
        // int bucket_row = ((int)round(this->r * x) % this->r);
        // int bucket_col = ((int)round(this->c * y) % this->c);

        int bucket_row = (int)(x / bucket_row_width);
        if (x == 1)
            bucket_row = this->r - 1;

        int bucket_col = (int)(y / bucket_col_width);
        if (y == 1)
            bucket_col = this->c - 1;

        // cout << x << "\t" << y << endl;
        // cout << bucket_row << "\t" << bucket_col << endl;
        // cout << bucket_row << "\t" << bucket_col << "\t" << bucket_col + bucket_row * this->r << endl;
        ++this->grid[bucket_col + bucket_row * this->r];
    }

    delete values;
}

int Grid::medianFilter(int row, int col, int diameter) {
    using namespace std;
    vector<int> values;



    int top = utils::clamp((row - 1)/2, 0, this->r - 1);
    int bottom = utils::clamp(row + (diameter - 1) / 2, 0, this->r - 1);
    int left = utils::clamp((col -1)/2, 0, this->c - 1);
    int right = utils::clamp(col + (diameter - 1) / 2, 0, this->c - 1);

    // cout << "top: " << top << endl;
    // cout << "bottom: " << bottom << endl;
    // cout << "left: " << left << endl;
    // cout << "right: " << right << endl;

    for (int r = top; r <= bottom; ++r) {
        for (int c = left; c <= right; ++c) {
            values.emplace_back((*this)(top + r, left + c));
        }
    }

    int middle = (values.size() - 1) / 2;
    // cout << middle << endl;

    nth_element(values.begin(), values.begin()+middle, values.end());

    return values[middle];
}