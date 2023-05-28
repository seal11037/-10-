#include "GameBoard.h"

GameBoard::GameBoard() {
    // 建窗口
    window.create(sf::VideoMode(800, 600), "Minesweeper");
}

GameBoard::~GameBoard() {}

void GameBoard::play_game() {
    print_board();

    while (!gameState.game_over && !gameState.game_won) {
        process_input();
        print_board();
    }
}

void GameBoard::print_board() {
    // 繪製地圖
    window.clear();

    int rows = gameState.rows;
    int cols = gameState.cols;
    int cellSize = 50;

    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
    cell.setOutlineThickness(1.0f);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cell.setPosition(j * cellSize, i * cellSize);
            cell.setFillColor(sf::Color::White);
            cell.setOutlineColor(sf::Color::Black);

            if (gameState.cells[i][j].isRevealed()) {
                cell.setFillColor(sf::Color::Black);
            }

            if (gameState.cells[i][j].isFlagged()) {
                cell.setFillColor(sf::Color::Red);
            }

            window.draw(cell);
        }
    }

    window.display();
}

void GameBoard::process_input() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return;
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            int row = event.mouseButton.y / 50;  // 假设每个单元格大小为50x50
            int col = event.mouseButton.x / 50;
            bool isLeftClick = (event.mouseButton.button == sf::Mouse::Left);

            handle_click(row, col, isLeftClick);
        }
    }
}

void GameBoard::handle_click(int row, int col, bool isLeftClick) {
    if (isLeftClick) {
        gameState.reveal_cell(row, col);
    } else {
        gameState.flag_cell(row, col);
    }

    gameState.check_win();
}