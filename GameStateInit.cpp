#include "GameStateInit.h"

GameStateInit::GameStateInit() {
    // 遊戲的初值、圖形設定
    rows = 10;
    cols = 10;
    num_mines = 10;
    game_over = false;
    game_won = false;
    cells = new Cell*[rows];
    for (int i = 0; i < rows; i++) {
        cells[i] = new Cell[cols];
        for (int j = 0; j < cols; j++) {
            cells[i][j].setRow(i);
            cells[i][j].setCol(j);
            cells[i][j].setMine(false);
            cells[i][j].setRevealed(false);
            cells[i][j].setFlagged(false);
            cells[i][j].setNumMines(0);
        }
    }
    // 設定每次重玩所需的變數
    init_vars();
}

GameStateInit::~GameStateInit() {
    //解構
    for (int i = 0; i < rows; i++) {
        delete[] cells[i];
    }
    delete[] cells;
}

void GameStateInit::init_vars() {
    // 初始化
    num_mines_placed = 0;
    num_flags_placed = 0;
    num_cells_revealed = 0;
}

void GameStateInit::place_mines(int row_clicked, int col_clicked) {
    // 亂放置地雷
    while (num_mines_placed < num_mines) {
        int row = rand() % rows;
        int col = rand() % cols;
        if (!cells[row][col].isMine() && (row != row_clicked || col != col_clicked)) {
            //!cells[row][col].isMine() 檢查該座標是否已經有地雷，如果有地雷，則不能在該座標放置地雷。
            //(row != row_clicked || col != col_clicked) 檢查該座標是否與玩家第一次點擊的格子座標相同，如果相同則不能在該座標放置地雷。
            cells[row][col].setMine(true);
            num_mines_placed++;
            update_num_mines(row, col);
        }
    }
}

void GameStateInit::update_num_mines(int row, int col) {
    // 相鄰格子的地雷數量
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (i >= 0 && i < rows && j >= 0 && j < cols && !(i == row && j == col)) {
                //i >= 0: 檢查相鄰格子的列座標是否在遊戲地圖的範圍內（列座標!<0）
                //i < rows: 檢查相鄰格子的列座標是否在遊戲地圖的範圍內（列座標!>=遊戲地圖的列數）
                //j >= 0: 檢查相鄰格子的行座標是否在遊戲地圖的範圍內（行座標!<0）。
                //j < cols: 檢查相鄰格子的行座標是否在遊戲地圖的範圍內（行座標!>=遊戲地圖的行數）。
                //!(i == row && j == col): 檢查相鄰格子是否為目前點擊的格子（相鄰格子的列座標和行座標!=目前點擊的格子的列座標和行座標）
                cells[i][j].setNumMines(cells[i][j].getNumMines() + 1);
            }
        }
    }
}

void GameStateInit::reveal_cell(int row, int col) {
    //處理滑鼠左鍵按下的動作
    if (cells[row][col].isFlagged() || cells[row][col].isRevealed() || game_over || game_won) {
        // 如果方格已被標記或已被打開，或遊戲已结束或已勝利，則什麼都不做
        return;
    }
    if (cells[row][col].isMine()) {
        // 如果玩家點的方格是地雷，遊戲结束
        cells[row][col].setRevealed(true);
        game_over = true;
        cout << "Game Over!"<<endl;
    } else {
        // 如果玩家點的方格不是地雷，則打開方格
        cells[row][col].setRevealed(true);
        num_cells_revealed++;
        if (num_cells_revealed == rows * cols - num_mines) {
            // 如果所有非地雷方格都被打開，遊戲勝利
            game_won = true;
            cout << "\nCongratulations! You won the game!\n";
        } else if (cells[row][col].getNumMines() == 0) {
            // 如果點的方格周圍没有地雷，則遞歸打開周圍的方格
            for (int i = row - 1; i <= row + 1; i++) {
                for (int j = col - 1; j <= col + 1; j++) {
                    if (i >= 0 && i < rows && j >= 0 && j < cols && !(i == row && j == col)) {
                        reveal_cell(i, j);
                    }
                }
            }
        }
    }
}

void GameStateInit::flag_cell(int row, int col) {
    // 處理滑鼠右鍵按下放開的動作
    if (cells[row][col].isRevealed() || game_over || game_won) {
        // 如果遊戲结束，或已揭開、已標記過旗子，直接返回
        return;
    }
    if (cells[row][col].isFlagged()) {
        cells[row][col].setFlagged(false);
        //旗幟數量-1
        num_flags_placed--;
    } else {
        if (num_flags_placed < num_mines) {
            cells[row][col].setFlagged(true);
            //旗幟數量＋1
            num_flags_placed++;
        }
    }
}

void GameStateInit::check_win() {
    //檢查遊戲勝利、失敗
    if (num_cells_revealed == rows * cols - num_mines) {
        // 所有的空格都已排除，玩家勝利
        game_over = true;
        game_won = true;
        //設為true，因為遊戲结束後不再能够繼續，讓遊戲勝利和失敗兩種情况互斥
    }
}

void GameStateInit::reset_game() {
    // 重置遊戲變數
    num_mines_placed = 0;
    num_flags_placed = 0;
    num_cells_revealed = 0;
    game_over = false;
    game_won = false;

    // 重新設置地圖
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cells[i][j].setMine(false);
            cells[i][j].setRevealed(false);
            cells[i][j].setFlagged(false);
            cells[i][j].setNumMines(0);
        }
    }
    int row_clicked = -1;
    int col_clicked = -1;
    while (num_mines_placed < num_mines) {
        int row = rand() % rows;
        int col = rand() % cols;
        if (!cells[row][col].isMine() && (row != row_clicked || col != col_clicked)) {
            //!cells[row][col].isMine()：判斷當前位置沒有地雷。
            //(row != row_clicked || col != col_clicked)：判斷當前位置不是玩家點擊的位置。
            cells[row][col].setMine(true);
            num_mines_placed++;
            update_num_mines(row, col);
        }
    }
}
