#ifndef Cell_h
#define Cell_h

class Cell {
public:
    Cell();
    int getRow();
    void setRow(int r);
    int getCol();
    void setCol(int c);
    bool isMine();
    void setMine(bool value);
    bool isRevealed();
    void setRevealed(bool value);
    bool isFlagged();
    void setFlagged(bool value);
    int getNumMines();
    void setNumMines(int num);
    char getSymbol();

private:
    int row;
    int col;
    bool mine;
    bool revealed;
    bool flagged;
    int numMines;

};
#endif  
