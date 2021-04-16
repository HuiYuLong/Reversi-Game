# include "AiTech.h"
# include "Rule.cpp"
# include "Reversi.cpp"
# include "Heuristic.cpp"
#include<tuple> // for tuple 
#include <vector>   // std::cout
#include <algorithm>  
// default constructor
AiTech::AiTech() {}

// Post Condition: it returns a random number from 0 up to MAX_NUM
/*int AiTech::random(int** ) {
    int n = (rand()%MAX_NUM);
    return n;
}*/


// Post Condition: 
vector<tuple<int,int> > rand_n() {
    vector<tuple<int,int> > AvailableMoves;
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            AvailableMoves.push_back(make_tuple(i,j));
        }
    }
    random_shuffle(AvailableMoves.begin(), AvailableMoves.end());
    /*for(int i=0; i<64; i++) {
            cout << get<0>(AvailableMoves[i]) << " " << get<1>(AvailableMoves[i]) << endl;
    } */

    return AvailableMoves;
}

int* AiTech::Best(int** BestMoves) {
    int b = -1;
    int* bArr = new int[2];
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            if(BestMoves[i][j] > b) {
                b = BestMoves[i][j];
                bArr[0] = i;
                bArr[1] = j;
            }
        }
    }
    //cout << " b: " << bArr[0] << bArr[1] << endl;
    return bArr;
}

bool AiTech::simulate(char** GameBoard, int* AiMove) {
    // initilize a random available moves
    vector<tuple<int,int> > AvailableMoves = rand_n();
    int size;
    // create a temp GameBoard since we need simulate the
    // GameBoard, and it needs to be deleted in the end
    char** temp_GB = new char*[8];
    for(int i=0; i<8; i++)
        temp_GB[i] = new char[8];
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            temp_GB[i][j] = GameBoard[i][j];
    // make a valid move
    int playerMove[2];
    Reversi b;
    temp_GB = b.update(temp_GB, AiMove, 'o');
    /*cout << "..." << endl;
    b.helpPrint(temp_GB);
    cout << "..." << endl;*/
    char player = 'x';
    int ai_count = get_ai_count(temp_GB);
    int user_count = get_user_count(temp_GB);
    // simulate with the rest valid moves until use or ai wins
    while(true) {
    //for(int k=0; k<10; k++) {
        //cout << "player: " << player[0] << endl;
        if(isWin('o', ai_count, user_count) == true) {
            /*cout << "+++" << endl;
            b.helpPrint(temp_GB);
            cout << "+++" << endl; */
            //cout << "Win" << endl;
            for(int i=0; i<8; i++)
                delete[] temp_GB[i];
            delete[] temp_GB;
            return true;
        }
        if(isWin('x', ai_count, user_count) == true) {
            /* << "---" << endl;
            b.helpPrint(temp_GB);
            cout << "---" << endl; */
            //cout << "Lose" << endl;
            for(int i=0; i<8; i++)
                delete[] temp_GB[i];
            delete[] temp_GB;
            return false;
        }
        // get the last moves of the available moves
        size = AvailableMoves.size();
        if(size <= 0) {
            //cout << "no available move" << endl;
            AvailableMoves = rand_n();
            //cout << get<0>(AvailableMoves[0]) << " " << get<1>(AvailableMoves[0]) << endl;
            break;
        }
        playerMove[0] = get<0>(AvailableMoves[size-=1]);
        playerMove[1] = get<1>(AvailableMoves[size-=1]);
        //cout << "ayy" << endl;
        //cout << playerMove[0] << " " << playerMove[1] << endl;

        // if the move is valid, make the move
        //cout << "playerMove[0]: " << playerMove[0] << "playerMove[1]: " << playerMove[0] << endl;
        char** GB = b.update(temp_GB, playerMove, player);
        if(GB != NULL) {
            temp_GB = GB;
            /*for(int i=0; i<8; i++)
                delete[] GB[i];
            delete[] GB;*/
            //cout << "player1: " << player << endl;
            /*cout << "***" << endl;
            b.helpPrint(temp_GB);
            cout << "***" << endl;*/
            // simulate user and ai's moves
            if(player == 'o')
                player = {'x'};
            else
                player = {'o'};
            ai_count = get_ai_count(temp_GB);
            user_count = get_user_count(temp_GB);
            // if make the move, refresh the available moves list
            AvailableMoves = rand_n();
        }
        // if not, try another move
        else { 
            AvailableMoves.pop_back();
        }
    }
    /*if(isFull(ai_count, user_count)) {

    }
    for(int i=0; i<8; i++)
        delete[] temp_GB[i];
    delete[] temp_GB;
    return false;*/

}

// Post Condition: it returns the move that ai should make 
//                 for next step with the greatest number of
//                 probability of winning.
int* AiTech::BestMove(char** GameBoard, int num_random_plays, int* AiMove) {
    int check;
    // initilize best moves
    int** BestMoves = new int*[8];
    for(int i=0; i<8; i++)
        BestMoves[i] = new int[8];
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            BestMoves[i][j] = 0;
    Reversi b;
    // To get the best move from the BestMoves(valid) list
    for(int i=0; i<7; i++) {
        for(int j=0; j<7; j++) {
            AiMove[0] = i;
            AiMove[1] = j;
            char** GB = b.update(GameBoard, AiMove, 'o');
            // if it equals to NULL, try another move (back to BestMove)
            if(GB == NULL) {
                /*for(int i=0; i<8; i++)
                    delete[] GB[i];
                delete[] GB;*/
                continue;
            }
            // simulate num_random_plays times
            for(int k=0; k<num_random_plays; k++) {
                    //cout << "???" << endl;
                //cout << "AiMove[0]: " << AiMove[0] << "AiMove[1]: " << AiMove[0] << endl;
                check = simulate(GameBoard, AiMove);
                // simulate does not change any pointer's content
                // it only returns if ai wins or nor
                if(check == true) {
                    //cout << "true+1" << endl;
                    BestMoves[AiMove[0]][AiMove[1]]++;
                }
                else if(check == false) {
                    //cout << "false+1" << endl;
                    // which means high risk of losing, so that
                    // we better make this move
                    BestMoves[AiMove[0]][AiMove[1]]+=6;
                }
                // heuristic+random
                else if(isCorner) {
                    BestMoves[AiMove[0]][AiMove[1]]+=12;
                }
            }
        } 
    }
    // helpPrint
    /*cout << ' ';
    for(int i=0; i<8; i++)
        cout << ' ' << i;
    cout << endl;
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            if(j == 0)
                cout << i << ' ';
            cout << BestMoves[i][j] << ' ';
        }
        cout << endl;
    }*/
    AiMove = Best(BestMoves);
    //cout << ".." << endl;
    //cout  << AiMove[0] << " " << AiMove[1] << endl;

    // delete best moves
    for(int i=0; i<8; i++) {
        delete[] BestMoves[i];
    }
    delete[] BestMoves;

    return AiMove;

}


