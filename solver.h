#include "minesweeper.h"
#include <set>
#include <vector>

struct isMine {
    bool operator()(int row, int col, int rows, int cols, int** array) {
        if (row < 0 || row >= rows) return false;
        if (col < 0 || col >= cols) return false;
        if (array[row][col] == 10) return true;
        return false;
    }
};

struct isOpen {
    bool operator()(int row, int col, int rows, int cols, int** array) {
        if (row < 0 || row >= rows) return false;
        if (col < 0 || col >= cols) return false;
        if (array[row][col] == -1) return true;
        return false;
    }
};

class Solver {
    public:
    Solver(Board& in);
    ~Solver();
    virtual void iterate() = 0;
    std::set<std::vector<int> > getInstructions();

    protected:
    int rows_;
    int cols_;
    int** input_;
    std::set<std::vector<int> > instructions_;
    void q_instr(int action, int row, int col);

};

class BasicSolver: public Solver {
    public:
    BasicSolver(Board& in);
    ~BasicSolver();
    void iterate();
};


template <typename Comp> int neighbor_count(int row, int col, int rows, int cols, int** array, Comp c) {
    int count = 0;
    if ( c(row-1, col-1, rows, cols, array)) count++;
    if ( c(row-1, col  , rows, cols, array)) count++;
    if ( c(row-1, col+1, rows, cols, array)) count++;
    if ( c(row  , col-1, rows, cols, array)) count++;
    if ( c(row  , col+1, rows, cols, array)) count++;
    if ( c(row+1, col-1, rows, cols, array)) count++;
    if ( c(row+1, col  , rows, cols, array)) count++;
    if ( c(row+1, col+1, rows, cols, array)) count++;
    return count;
}

template <typename Comp> void neighbor_do(int row, int col, int rows, int cols, int** array, Comp c) {
    c(row-1, col-1, rows, cols, array);
    c(row-1, col  , rows, cols, array);
    c(row-1, col+1, rows, cols, array);
    c(row  , col-1, rows, cols, array);
    c(row  , col+1, rows, cols, array);
    c(row+1, col-1, rows, cols, array);
    c(row+1, col  , rows, cols, array);
    c(row+1, col+1, rows, cols, array);
    return;
}