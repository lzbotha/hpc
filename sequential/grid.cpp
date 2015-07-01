#include <iostream>
#include "grid.h"

Grid::Grid(int rows, int cols) : r(rows), c(cols){
    this->grid = new int[r * c];
}

Grid::~Grid() {
    using namespace std;
    delete this->grid;
}

int Grid::rows() {return this->r;}
int Grid::cols() {return this->c;}