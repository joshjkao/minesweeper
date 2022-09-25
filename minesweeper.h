#include <iostream>

struct Tile {
    bool isMine_;
    int state_;
    Tile();
};

class Board {
    public:
    Board(int rows, int cols, int mines);
    ~Board();
    void generateMines(int row, int col);
    void dig(int row, int col);
    void flag(int row, int col);
    void action(int action, int row, int col);
    void printBoard();
    int** getOutput();
    int getRows();
    int getCols();
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