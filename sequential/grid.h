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
        int& operator[] (int x) {return grid[x];}
};

#endif