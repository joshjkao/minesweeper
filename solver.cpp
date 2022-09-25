#include "solver.h"
#include <iostream>

Solver::Solver(Board in):
rows_(in.getRows()), cols_(in.getCols()), input_(in.getOutput())
{
    
}

Solver::~Solver() {

}

void Solver::q_instr(int action, int row, int col) {
    
    std::vector<int> vec;
    vec.push_back(action);
    vec.push_back(row);
    vec.push_back(col);
    instructions_.insert(vec);
}

std::set<std::vector<int> > Solver::getInstructions() {
    return instructions_;
}

BasicSolver::BasicSolver(Board in):
    Solver(in)
{

}

BasicSolver::~BasicSolver() {

}



void BasicSolver::iterate() {
    instructions_.clear();
    bool stop = false;
    for (int i = 0; i < rows_; ++i) {
        if (stop) break;
        for (int j = 0; j < cols_; ++j) {
            if (stop) break;
            if (input_[i][j] == 10 || input_[i][j] == 0) { }
            else if (neighbor_count(i, j, rows_, cols_, input_, isOpen()) == 0) { }
            else if (input_[i][j] == neighbor_count(i, j, rows_, cols_, input_, isMine())) {
                q_instr(0, i-1, j-1);
                q_instr(0, i-1, j  );
                q_instr(0, i-1, j+1);
                q_instr(0, i  , j-1);
                q_instr(0, i  , j+1);
                q_instr(0, i+1, j-1);
                q_instr(0, i+1, j  );
                q_instr(0, i+1, j+1);
                stop = true;
            }
            else if (input_[i][j] - neighbor_count(i, j, rows_, cols_, input_, isMine()) == neighbor_count(i, j, rows_, cols_, input_, isOpen())) {
                q_instr(1, i-1, j-1);
                q_instr(1, i-1, j  );
                q_instr(1, i-1, j+1);
                q_instr(1, i  , j-1);
                q_instr(1, i  , j+1);
                q_instr(1, i+1, j-1);
                q_instr(1, i+1, j  );
                q_instr(1, i+1, j+1);
                stop = true;
            }
        }
    }
}

