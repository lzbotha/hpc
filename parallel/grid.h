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

        void getRows(int centre, int radius, int & start, int & end);

        void populateFromFile(std::string filename);
        void populateFromArray(int points, float * values);

        int medianFilter(int row, int col, int diameter);
        void applyMedianFilter(int diameter);
        void printToFile(std::string filename);
};

#endif