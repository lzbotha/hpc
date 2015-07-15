#ifndef _GRID
#define _GRID

class Grid {
    private:
        int * grid;
        int r;
        int c;



    public:
        Grid(int rows, int cols);
        ~Grid();
        int rows();
        int cols();
        inline int& operator[] (int x) {return grid[x];}
        inline int& operator() (int y, int x) {return grid[x + r * y];}

        void clear();
        void print();

        void populateFromFile(std::string filename);
        void populateFromArray(int points, float * values);

        int medianFilter(int row, int col, int diameter);
        void applyMedianFilter(int diameter);
        void printToFile(std::string filename);

        int select_kth(int * list, int left, int right, int k);
        inline int partition(int * list, int left, int right, int pivot_index);
};

#endif