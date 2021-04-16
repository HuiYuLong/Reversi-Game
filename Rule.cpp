# include <iostream>

using namespace std;

//bool isFull(int ai_count, int user_count);
//bool isWin(char player, int ally, int enemy);

int get_user_count(char** GameBoard) {
    int user_count = 0;
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            if(GameBoard[i][j] == 'x')
                user_count++;
        }
    }
    //cout << "user: " << user_count << endl;
    return user_count;
}

int get_ai_count(char** GameBoard) {
    int ai_count = 0;
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            if(GameBoard[i][j] == 'o')
                ai_count++;
        }
    }
    //cout << "ai: " << ai_count << endl;
    return ai_count;
}

// check if the game board is full
bool isFull(int ai_count, int user_count) {
    if (ai_count + user_count == 64)
        return true;
    return false;
}


// rule
bool isWin(char player, int ai_count, int user_count) {
    int ally = -1;
    int enemy = -1;
    //cout << "user count: " << user_count << "   ai count: " << ai_count << endl;
    if(player == 'x') {
        ally = user_count;
        enemy = ai_count;
    }
    else if(player == 'o') {
        ally = ai_count;
        enemy = user_count;
    }
    if(isFull(ai_count, user_count)) {
        if(ally > enemy) {
            //cout << "1Wins!" << endl;
            return true;
        }
        else if(ally == enemy) {
            //cout << "Draw!" << endl;
            return true;
        }
    }
    else if(enemy == 0) {
        //cout << "2Wins!" << endl;
        return true;
    }
    return false;
}
