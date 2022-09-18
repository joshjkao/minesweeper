#include <iostream>

struct Tile {
    bool isMine_;
    int state_;
    Tile();
};

class Board {
    public:
    Board(int rows, int cols, int mines);
    void generateMines(int row, int col);
    void dig(int row, int col);
    void flag(int row, int col);
    void printBoard();
    int** getOutput();
    int gameContinue();
    
    private:
    bool dead_;
    int rows_;
    int cols_;
    int mines_;
    Tile** field_;
    int** output_;
    int digs_;

    bool isMine(int row, int col);
    bool checkValid(int row, int col);
    bool checkValidMine(int row, int col);
};