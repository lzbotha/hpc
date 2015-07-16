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

__device__ int partition(int * list, int left, int right, int pivot_index) {
    int pivot_value = list[pivot_index];

    // Move pivot to the end
    list[pivot_index] = list[right];
    list[right] = pivot_value;

    int store_index = left;

    for (int i = left; i < right; ++i) {
        if (list[i] < pivot_value) {
            int temp = list[store_index];
            list[store_index] = list[i];
            list[i] = temp;

            ++store_index;
        }
    }

    int temp = list[store_index];
    list[store_index] = list[right];
    list[right] = temp;

    return store_index;
}

__device__ int select_kth(int * list, int left, int right, int k) {
    if (left == right)
        return list[left];

    int pivot_index;
    while(true) {
        pivot_index = left + (right - left) / 2;// + (int)(((float)rand() / RAND_MAX) * (right - left));
        pivot_index = partition(list, left, right, pivot_index);

        if (k == pivot_index)
            return list[k];
        else if (k < pivot_index)
            right = pivot_index - 1;
        else
            left = pivot_index + 1;
    }
}

__device__ int clamp(int x, int a, int b) {
    return max(a, min(b, x));
}

__global__ void filter(int * grid, int * result, int rows, int cols, int diameter) {
    int row = blockIdx.x * blockDim.x + threadIdx.x;
    int col = blockIdx.y * blockDim.y + threadIdx.y;

    if(row < rows and col < cols){
        int top = clamp(row - (diameter - 1) / 2, 0, rows - 1);
        int bottom = clamp(row + (diameter - 1) / 2, 0, rows - 1);
        int left = clamp(col - (diameter - 1) / 2, 0, cols - 1);
        int right = clamp(col + (diameter - 1) / 2, 0, cols - 1);

        int num_values = (bottom - top + 1) * (right - left + 1);
        int values[441];
        
        int count = 0;

        for (int r = top; r <= bottom; ++r) {
            for (int c = left; c <= right; ++c) {
                values[count] = grid[c + r * cols];
                ++count;
            }
        }

        result[col + row * cols] = select_kth(values, 0, num_values - 1, (num_values - 1) / 2);
    }
}

void CUDA_SAFE_CALL(cudaError_t error, std::string error_message) {
    using namespace std;
    if(error!=cudaSuccess)
    {
       cout << error_message << endl;
       cout << cudaGetErrorString(error) << endl;
       exit(-1);
    }
}

void Grid::applyMedianFilter(int diameter) {
    using namespace std;

    int * new_grid = new int[this->r * this->c];

    CUDA_SAFE_CALL(cudaSetDevice(0), "Failed to set device");
    CUDA_SAFE_CALL(
        cudaMalloc(&d_grid, this->r * this->c * sizeof(float)),
        "Failed to allocate memory for d_grid"
    );
    CUDA_SAFE_CALL(
        cudaMalloc(&d_result, this->r * this->c * sizeof(float)),
        "Failed to allocate memory for d_result"
    );
    
    CUDA_SAFE_CALL(
        cudaMemcpy(d_grid, this->grid, this->r * this->c * sizeof(float), cudaMemcpyHostToDevice),
        "Failed to copy grid to d_grid"
    );

    dim3 dimBlock(16,16);
    dim3 dimGrid(
        this->r / dimBlock.x + 1,
        this->c / dimBlock.y + 1
    );

    filter<<<dimGrid, dimBlock>>>(d_grid, d_result, this->r, this->c, diameter);

    CUDA_SAFE_CALL(cudaDeviceSynchronize(), "Running kernel failed");

    CUDA_SAFE_CALL(cudaMemcpy(
        new_grid, d_result, this->r * this->c * sizeof(float), cudaMemcpyDeviceToHost),
        "Failed to copy d_result to new_grid"
    );

    CUDA_SAFE_CALL(cudaFree(d_grid), "Failed to free d_grid");
    CUDA_SAFE_CALL(cudaFree(d_result), "Failed to free d_result");

    delete [] grid;
    grid = new_grid;
}

void Grid::printToFile(std::string filename) {
    using namespace std;
    utils::outputToCSV(this->grid, this->r, this->c, filename);
}