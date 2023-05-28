#ifndef GameBoard_h
#define GameBoard_h
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp> 
#include "GameStateInit.h"

class GameBoard {
public:
    GameBoard();
    ~GameBoard();
    void play_game();

private:
    GameStateInit gameState;
    sf::RenderWindow window;

    void print_board();
    void process_input();
    void handle_click(int row, int col, bool isLeftClick);
};
#endif