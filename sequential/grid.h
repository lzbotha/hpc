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
        inline int& operator() (int x, int y) {return grid[x + r * y];}

        void getRows(int centre, int radius, int & start, int & end);
};

#endif