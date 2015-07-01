#include <iostream>
#include "grid.h"

Grid::Grid(int rows, int cols) : r(rows), c(cols){
    this->grid = new int[r * c];
}

Grid::~Grid() {
    delete this->grid;
}

int Grid::rows() {return this->r;}
int Grid::cols() {return this->c;}

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