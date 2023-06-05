#include "Minesweeper.h"

void Player::displayTime() const {
    int seconds = timeInSeconds % 60;
    int minutes = (timeInSeconds / 60) % 60;
    int hours = (timeInSeconds / 3600) % 24;
    int days = timeInSeconds / 86400;

    if (days > 0) {
        cout << days << " 天 ";
    }

    if (hours > 0) {
        cout << hours << " 時 ";
    }

    if (minutes > 0) {
        cout << minutes << " 分 ";
    }

    cout << seconds << " 秒";
}

Minesweeper::Minesweeper() {
    board = vector<vector<char>>(BOARD_SIZE, vector<char>(BOARD_SIZE, '-'));
    visited = vector<vector<bool>>(BOARD_SIZE, vector<bool>(BOARD_SIZE, false));
    flagged = vector<vector<bool>>(BOARD_SIZE, vector<bool>(BOARD_SIZE, false));

    srand(time(NULL));
}

void Minesweeper::printBoard(bool reveal) const {
    cout << "   ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << "  ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            char cell = board[i][j];
            if (cell == 'X' && !reveal) {
                cell = '-';
            }
            cout << cell << " ";
        }
        cout << endl;
    }
}

void Minesweeper::placeBombs() {
    int count = 0;
    while (count < NUM_BOMBS) {
        int row = rand() % BOARD_SIZE;
        int col = rand() % BOARD_SIZE;
        if (board[row][col] != 'X') {
            board[row][col] = 'X';
            count++;
        }
    }
}

int Minesweeper::countNeighboringBombs(int row, int col) const {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) {
                if (board[newRow][newCol] == 'X') {
                    count++;
                }
            }
        }
    }
    return count;
}

void Minesweeper::revealEmptyCells(int row, int col) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return;
    }

    if (visited[row][col]) {
        return;
    }

    visited[row][col] = true;

    if (board[row][col] == '-') {
        int numBombs = countNeighboringBombs(row, col);
        board[row][col] = '0' + numBombs;

        if (numBombs == 0) {
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    revealEmptyCells(row + i, col + j);
                }
            }
        }
    }
}

bool Minesweeper::hasWon() const {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == '-' && !visited[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void Minesweeper::playGame() {
    placeBombs();

    int startTime = time(NULL);

    while (true) {
        printBoard(false);

        int row, col;
        cout << "輸入列和行(x,y)（以空格分隔）：";
        cin >> col >> row;

        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
            cout << "無效的舉動，再試一次" << endl;
            continue;
        }

        int action;
        cout << "輸入動作（1: 點開, 2: 插旗, 3: 取消插旗）： ";
        cin >> action;

        if (visited[row][col]) {
            cout << "該格已經被顯露，再試一次" << endl;
            continue;
        }

        if (action == 1) {
            if (flagged[row][col]) {
                cout << "該格已經被插旗，無法點開。再試一次" << endl;
                continue;
            }

            if (board[row][col] == 'X') {
                cout << "遊戲結束！你踩到了炸彈" << endl;
                break;
            }

            revealEmptyCells(row, col);
        } else if (action == 2) {
            if (visited[row][col]) {
                cout << "該格已經被插旗，再試一次" << endl;
                continue;
            }

            flagged[row][col] = true;
            board[row][col] = 'F';
        } else if (action == 3) {
            if (!flagged[row][col]) {
                cout << "該格並未插旗，再試一次" << endl;
                continue;
            }

            flagged[row][col] = false;
            board[row][col] = '-';
        } else {
            cout << "無效的動作，再試一次" << endl;
            continue;
        }

        if (hasWon()) {
            int endTime = time(NULL);
            int elapsedTime = endTime - startTime;

            string playerName;
            cout << "恭喜！你贏了！輸入你的名字：";
            cin >> playerName;

            Player player(playerName, elapsedTime);
            vector<Player> leaderboard;

            leaderboard.push_back(player);

            sort(leaderboard.begin(), leaderboard.end(), [](const Player& a, const Player& b) {
                return a.timeInSeconds < b.timeInSeconds;
            });

            cout << "排行榜：" << endl;
            for (int i = 0; i < leaderboard.size(); i++) {
                cout << i + 1 << ". " << leaderboard[i].name << " - ";
                leaderboard[i].displayTime();
                cout << endl;
            }

            break;
        }
    }
}

