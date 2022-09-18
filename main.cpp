#include <iostream>
#include <string>
#include "minesweeper.h"
using namespace std;

int main() {
    Board test(10,10, 2);
    int x_in;
    int y_in;
    string s_in;
    test.printBoard();
    cin >> s_in >> x_in >> y_in;
    test.generateMines(x_in,y_in);
    while (test.gameContinue() == 0) {
        test.printBoard();
        cin >> s_in >> x_in >> y_in;
        if (s_in == "dig") {
            test.dig(x_in, y_in);
        }
        else if (s_in == "flag") {
            test.flag(x_in, y_in);
        }
    }

    if (test.gameContinue() == -1) {
        cout << "you lose" << endl;
    }
    else {
        cout << "you win" << endl;
    }
}