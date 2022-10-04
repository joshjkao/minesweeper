#include <iostream>
#include <string>
// #include "minesweeper.h"
#include "solver.h"
using namespace std;

void playergame(Board& playerboard) {
    playerboard.printBoard();
    int x_in;
    int y_in;
    string s_in;
    cout << "\nStarting new player game with " << playerboard.getRows() << " rows, " << playerboard.getCols() << " cols.";
    cout << "\nChoose a starting square: <row> <col>\n";
    cin >> x_in >> y_in;
    playerboard.generateMines(x_in,y_in);
    while (playerboard.gameContinue() == 0) {
        playerboard.printBoard();
        cout << "\nChoose a square: <dig or flag> <row> <col>\n";
        cin >> s_in >> x_in >> y_in;
        if (s_in == "dig") {
            playerboard.dig(x_in, y_in);
        }
        else if (s_in == "flag") {
            playerboard.flag(x_in, y_in);
        }
    }

    if (playerboard.gameContinue() == -1) {
        cout << "\nYou lose\n" << endl;
    }
    else {
        cout << "\nYou win\n" << endl;
    }
    return;
}

void solvergame(Board& test) {
    test.printBoard();
    int x_in;
    int y_in;
    cout << "\nStarting basic solver on " << test.getRows() << " rows, " << test.getCols() << " cols.";
    cout << "\nChoose a starting square: <row> <col>\n";
    cin >> x_in >> y_in;
    test.generateMines(x_in,y_in);
    test.printBoard();
    BasicSolver solve(test);
    cout << endl;
    while (test.gameContinue() == 0) {
        solve.iterate();
        std::set<std::vector<int> > instructions = solve.getInstructions();
        for (std::set<std::vector<int> >::iterator it = instructions.begin(); it != instructions.end(); ++it) {
            test.action((*it)[0], (*it)[1], (*it)[2]);
        }
        test.printBoard();
        if (instructions.size() == 0) break;
    }
    if (test.gameContinue() == -1) {
        cout << "\nFailed: mine triggered\n";
    }
    if (test.gameContinue() == 1) {
        cout << "\nGame Completed\n";
    }
    if (test.gameContinue() == 0) {
        cout << "\nFailed: inconclusive\n";
    }
}


int main(int argc, char** argv) {
    srand(atoi(argv[0]));
    int rows, cols, mines, gametype;
    cout << "Gametypes: \n1. player game \n2. basic solver\n";
    cout << "\nEnter game information in the following format: <rows> <columns> <mines> <gametype>\n";
    cin >> rows >> cols >> mines >> gametype;
    Board game(rows,cols,mines);
    
    if (gametype == 1) {     
        playergame(game);
    }
    if (gametype == 2) {
        solvergame(game);
    }    
}