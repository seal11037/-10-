#include "Minesweeper.h"

int main() {
    int choice=1;
    while(choice==1){
        cout << "Welcome to Minesweeper!" << endl;

        while (true) {
            cout << endl;
            cout << "1.新遊戲：" << endl;
            cout << "2.退出：" << endl;
            cout << "輸入您的選擇：";
        

            cin >> choice;

            if (choice == 1) {
                Minesweeper game;
             game.playGame();
             } 
            else if (choice == 2) {
                break;
            } 
            else {
                cout << "無效的選擇，再試一次" << endl;
            }
        }
    }
    return 0;
}
