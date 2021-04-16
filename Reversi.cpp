/*
 * Reversi.cpp
 * 
 * Description: include all the information of a student
 * Class Invariant:
 * 
 * Author: Huiyu Long
 * Date: March 29, 2019
 */

# include "Reversi.h"
//# include "AiTech.cpp"
# include <assert.h>
using namespace std;

// default constructor
Reversi::Reversi() {
    UserCount = 2;
    AiCount = 2;
    game_board = new char *[8];
    for(int i=0; i<8; i++)
        game_board[i] = new char[8];
}

char** Reversi::init_game_board() {
    /****************** initialize the game board ******************/
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            game_board[i][j] = '.';
    }
    game_board[3][3] = 'o';
    game_board[4][4] = 'o';
    game_board[3][4] = 'x';
    game_board[4][3] = 'x';

    helpPrint();
    /*********** successfully initialized the game board ***********/
    return game_board;
}


// Pre Condition: check if the given move is available
// Post Condition: return true if the given move is available
//                 else return false
//bool Reversi::available_move(char** GameBoard, int* playerMove, char* player)


//end of available move
// (fliping your opponent's pieces by trapping them between two of your own)
// Post Condition: update the GameBoard after one 
//                 player made his move, and return
//                 the updated GameBoard
char** Reversi::update(char** GameBoard, int* playerMove, char player) {

    // create the new GameBoard
    char** newGameBoard = new char*[8];
    for(int i=0; i<8; i++)
        newGameBoard[i] = new char[8];
    // corner case: cannot be replaced
    //cout << "*********playerMove[0]: " << playerMove[0] << "playerMove[1]: **************" << playerMove[0] << endl;
    //assert(playerMove[0] >=0 && playerMove[0]<=7);
    //assert(playerMove[1] >=0 && playerMove[1]<=7);
    if(GameBoard[playerMove[0]][playerMove[1]] != '.') {
        //cout << "It cannot be replaced! Please try again: " << endl;
        return NULL;
    }
    bool updated = false;
    // deep copy of the player's move
    int* index = new int[3];
    int* temp = new int[3];
    char enemy;
    int count = 0;
    // to deep copy GameBoard once
    int create = 0;
    // start from playerMove's lefttop corner
    for(int i=0; i<3; i++) {
        index[i] = playerMove[i]-1;
        temp[i] = playerMove[i]-1;
    }

    //cout << index[0] << index[1] << endl;
    // update the game board
    // if the player is user, check if those nine indices 
    // ,which are around the UserMove are 'o' other than 'x'
    // vice versa
    if(player == 'x'){
        enemy = 'o';
    }
    else {
        enemy = 'x';
    }
    int temp_0 = index[0];
    int temp_1 = index[1];
    // check the nine indices
    for(int i=temp_0; i<temp_0+3; i++) {
        for(int j=temp_1; j<temp_1+3; j++) {
            index[0] = i;
            temp[0] = index[0];
            index[1] = j;
            temp[1] = index[1];
            //cout << "checking temp[0] " << temp[0];
            //cout << " and temp[1]: " << temp[1] << endl;
            // corner case
            if(index[0] < 0 || index[0] > 7 || index[1] < 0 || index[1] > 7) {
                continue;
            }
            // if the checking index is considerable, keep moving
            // to the next one(straight/diagonal line) until
            // it's not enemy's move('x'/'o')
            while(GameBoard[temp[0]][temp[1]] == enemy) {
                //cout << "considerable: " << temp[0] << " " << temp[1] << endl;
                temp[0]+=(index[0]-playerMove[0]);
                temp[1]+=(index[1]-playerMove[1]);
                count++;
                //cout << "considerable: " << temp[0] << " " << temp[1] << endl;
                if(temp[0]<0 || temp[1]<0 || temp[0]>7 || temp[1]>7)
                    break;
            }
            // if player's move traps his enemy's, flip all pieces
            // that are between the player's piece
            if(temp[0]>=0 && temp[1]>=0 && temp[0]<=7 && temp[1]<=7) {
                if(GameBoard[temp[0]][temp[1]] == player && count > 0) {
                    if(create == 0) {
                        for(int i=0; i<8; i++)
                            for(int j=0; j<8; j++)
                                newGameBoard[i][j] = GameBoard[i][j];
                        create++;
                    }

                    for(int i=0; i<count; i++) {
                        temp[0]-=(index[0]-playerMove[0]);
                        temp[1]-=(index[1]-playerMove[1]);
                        //cout << "fliping piece: " << temp[0] << " " << temp[1] << endl;
                        newGameBoard[temp[0]][temp[1]] = player;
                        //GameBoard[temp[0]][temp[1]] = player[0];
                        updated = true;
                    }
                }
            }
            count = 0;
        }
    }
    if(updated == false) {
        //cout << "Invalid Move! Please try again: " << endl;
        return NULL;
    }
    else {
        newGameBoard[playerMove[0]][playerMove[1]] = player;
        //GameBoard[playerMove[0]][playerMove[1]] = player[0];
        //cout << "successfully updated!" << endl;
        return newGameBoard;
    }
                
}

void Reversi::helpPrint(char** GameBoard) {
    cout << ' ';
    for(int i=0; i<8; i++)
        cout << ' ' << i;
    cout << endl;
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            if(j == 0)
                cout << i << ' ';
            cout << GameBoard[i][j] << ' ';
        }
        cout << endl;
    }
}

void Reversi::helpPrint() {
    cout << ' ';
    for(int i=0; i<8; i++)
        cout << ' ' << i;
    cout << endl;
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            if(j == 0)
                cout << i << ' ';
            cout << game_board[i][j] << ' ';
        }
        cout << endl;
    }
}
