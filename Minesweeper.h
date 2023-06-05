#ifndef Minesweeper_h
#define Minesweeper_h

#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

struct Player {
    string name;
    int timeInSeconds;

    Player(const string& n, int t) : name(n), timeInSeconds(t) {}
    void displayTime() const;
};

class Minesweeper {
public:
    Minesweeper();
    void playGame();

private:
    const int BOARD_SIZE = 10;
    const int NUM_BOMBS = 10;
    vector<vector<char>> board;
    vector<vector<bool>> visited;
    vector<vector<bool>> flagged;

    void printBoard(bool reveal) const;
    void placeBombs();
    int countNeighboringBombs(int row, int col) const;
    void revealEmptyCells(int row, int col);
    bool hasWon() const;
};

#endif
