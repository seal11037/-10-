#include "Cell.h"

Cell::Cell() {
    //初始化地雷格子
    row = 0;
    col = 0;
    mine = false;//非地雷
    revealed = false;//未被打開
    flagged = false;//未被標記
    numMines = 0;
}

int Cell::getRow() {
    //獲取對象行
    return row;
}

void Cell::setRow(int r) {
    row = r;
}

int Cell::getCol() {
    //獲取對象列
    return col;
}

void Cell::setCol(int c) {
    col = c;
}

bool Cell::isMine() {
    //判斷是否是地雷
    return mine;
}

void Cell::setMine(bool value) {
    //設置是否是地雷
    mine = value;
}

bool Cell::isRevealed() {
    //判斷是否被打開
    return revealed;
}

void Cell::setRevealed(bool value) {
    //設置是否被打開
    revealed = value;
}

bool Cell::isFlagged() {
    //判斷是否被插旗
    return flagged;
}

void Cell::setFlagged(bool value) {
    //設置是否被插旗
    flagged = value;
}

int Cell::getNumMines() {
    //獲取周圍的地雷數量
    return numMines;
}

void Cell::setNumMines(int num) {
    //設置周圍的地雷數量
    numMines = num;
}

char Cell::getSymbol() {
    //根據格子的狀態顯示對應的代號
    if (flagged) {
        //如果標記為旗幟 顯示F
        return 'F';
    } else if (!revealed) {
        //如果未被打開 顯示？
        return '?';
    } else if (mine) {
        //如果被打開為地雷 顯示Ｘ
        return 'X';
    } else {
        //已打開且周圍有地雷的情况下 顯示對應的數字
        return static_cast<char>('0' + numMines);
    }
}

