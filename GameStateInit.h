#ifndef Game_StateInit_h
#define Game_StateInit_h
#include <iostream>
using namespace std;
#include "Cell.h"

class GameStateInit {
public:
    GameStateInit();
    ~GameStateInit();
    void init_vars();
    void place_mines(int row_clicked, int col_clicked);
    void update_num_mines(int row, int col);
    void reveal_cell(int row, int col);
    void flag_cell(int row, int col);
    void check_win();
    void reset_game();

private:
    int rows;
    int cols;
    int num_mines;
    int num_mines_placed;
    int num_flags_placed;
    int num_cells_revealed;
    bool game_over;
    bool game_won;
    Cell** cells;
};
#endif