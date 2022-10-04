#include "minesweeper.h"

/*Output states: 
-1 = undiscovered
0-6 = number of mines surrounding
10 = flagged
*/

Tile::Tile():
isMine_(false), state_(0) 
{

}

Board::Board(Board const& other) { //debug: should never be called
    std::cout << "copy constructor called";
}

Board::Board(int rows, int cols, int mines): 
dead_(false), rows_(rows), cols_(cols), mines_(mines), digs_(0)
{
    field_ = new Tile*[rows];
    for (int i = 0; i < cols; ++i) {
        field_[i] = new Tile[cols];
    }
    output_ = new int*[rows];
    for (int i = 0; i < cols; ++i) {
        output_[i] = new int[cols];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            output_[i][j] = -1;
        }
    }
}

Board::~Board() {
    for (int i = 0; i < rows_; i++) {
        delete [] field_[i];
        delete [] output_[i];
    }
    delete [] field_;
    delete [] output_;
}

void Board::generateMines(int row, int col) {
    int i = 0;
    while (i < mines_) {
        int x = rand() % rows_;
        int y = rand() % cols_;
        if (((x >= row - 1 && x <= row + 1) && (y >= col - 1 && y <= col + 1)) || (field_[x][y].isMine_ == true)) continue;
        if (checkValidMine(x-1, y-1) && checkValidMine(x-1, y  ) && checkValidMine(x-1, y+1) && checkValidMine(x  , y-1) && checkValidMine(x  , y+1) && checkValidMine(x+1, y-1) && checkValidMine(x+1, y  ) && checkValidMine(x+1, y+1)) {
            field_[x][y].isMine_ = true;
            if (checkValid(x-1, y-1)) ++field_[x-1][y-1].state_;
            if (checkValid(x-1, y  )) ++field_[x-1][y  ].state_;
            if (checkValid(x-1, y+1)) ++field_[x-1][y+1].state_;
            if (checkValid(x  , y-1)) ++field_[x  ][y-1].state_;
            if (checkValid(x  , y+1)) ++field_[x  ][y+1].state_;
            if (checkValid(x+1, y-1)) ++field_[x+1][y-1].state_;
            if (checkValid(x+1, y  )) ++field_[x+1][y  ].state_;
            if (checkValid(x+1, y+1)) ++field_[x+1][y+1].state_;
            i++;
        }
    }
    dig(row, col);
    return;
}

void Board::dig(int row, int col) {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_ || (output_[row][col] != -1)) {}
    else if (field_[row][col].isMine_) {
        dead_ = true;
    }
    else {
        output_[row][col] = field_[row][col].state_;
        ++digs_;
        if (field_[row][col].state_ == 0) {
            dig(row-1, col-1);
            dig(row-1, col  );
            dig(row-1, col+1);
            dig(row  , col-1);
            dig(row  , col+1);
            dig(row+1, col-1);
            dig(row+1, col  );
            dig(row+1, col+1);
        }
    }
    return;
}

void Board::flag(int row, int col) {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_ || (output_[row][col] > -1 && output_[row][col] != 10)) return;
    // else if (output_[row][col] == 10) {
    //     output_[row][col] = -1;
    // }
    else {
        output_[row][col] = 10;
    }
    return;
}

void Board::action(int action, int row, int col) {
    if (!action) dig(row, col);
    else flag(row, col);
}

void Board::printBoard() {
    for (int k = 0; k < 10; ++k) {
        std::cout << std::endl;
    }

    for (int i = 0; i < rows_ + 1; ++i) {
        std::cout << "--";
    }
    std::cout << std::endl;
    for (int i = 0; i < rows_; ++i) {
        std::cout << "|";
        for (int j = 0; j < cols_; ++j) {
            if (output_[i][j] == 10) {
                std::cout << "x ";
            }
            else if (output_[i][j] == 0) {
                std::cout << "  ";
            }
            else if (output_[i][j] > -1) {
                std::cout << output_[i][j] << " ";
            }
            else {
                std::cout << ". ";
            }
        }
        std::cout << "|" << std::endl;
    }
    
    for (int i = 0; i < rows_ + 1; ++i) {
        std::cout << "--";
    }
}

int** Board::getOutput() {
    return output_;
}

int Board::getRows() {
    return rows_;
}

int Board::getCols() {
    return cols_;
}

bool Board::isMine(int row, int col) {
    if (row < 0 || row >= rows_) return 0;
    if (col < 0 || col >= cols_) return 0;
    return field_[row][col].isMine_;
}

bool Board::checkValid(int row, int col) {
    if (row < 0 || row >= rows_) return false;
    if (col < 0 || col >= cols_) return false;
    return true;
}

bool Board::checkValidMine(int row, int col) {
    if (row < 0 || row >= rows_) return 0;
    if (col < 0 || col >= cols_) return 0;
    if (field_[row][col].state_ == 6) return 0;
    return 1;
}

int Board::gameContinue() {
    if (dead_) return -1;
    if (digs_ == rows_ * cols_ - mines_) return 1;
    return 0;
}