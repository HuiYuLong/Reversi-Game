# include "AiTech.cpp"
# include <cstdlib>
# include <string>
# include <ctime>

int main() {
    char input = 0;
    Reversi c;
    char** GameBoard = c.init_game_board();
    srand(time(NULL)); 
    /********************* create an user *********************/
    int* UserMove = new int[2];
    char User = 'x';
    /********************* create an ai *********************/
    AiTech AI;
    int* AiMove = new int[2];
    char Ai = 'o';
    int ai_count = get_ai_count(GameBoard);
    int user_count = get_user_count(GameBoard);
    int num_random_plays = 10;
    bool check;
    while( !isWin(User, ai_count, user_count) || !isWin(Ai, ai_count, user_count) || !isFull(ai_count, user_count) ) {
        /********************* user's turn *********************/
        cout << "User's turn (eg. '3 4' is 'x')" << endl;
        check = false;
        while(!check) {
            cin >> UserMove[0];
            cin >> UserMove[1];
            if(c.update(GameBoard, UserMove, User) != NULL) {
                // GameBoard will be changed
                GameBoard = c.update(GameBoard, UserMove, User);
                check = true;
            }
        }
        c.game_board = GameBoard;
        c.helpPrint();

        /********************** ai's turn **********************/
        cout << "AI's turn..." << endl;
        check = false;
        while(!check) {
        //for(int i=0; i<1; i++) {
            //cin >> AiMove[0];
            //cin >> AiMove[1];
            AiMove = AI.BestMove(GameBoard, num_random_plays, AiMove);
            //cout  << AiMove[0] << " " << AiMove[1] << endl;
            if(c.update(GameBoard, AiMove, Ai) != NULL) {
                GameBoard = c.update(GameBoard, AiMove, Ai);
                check = true;
            }
        }
        c.game_board = GameBoard;
        c.helpPrint();
        ai_count = get_ai_count(GameBoard);
        user_count = get_user_count(GameBoard);
        cout << "AiCount: " << ai_count << "    UserCount: " << user_count << endl;
        /*AiMove = AI.BestMove(GameBoard, num_random_plays);
        if(c.update(GameBoard, AiMove, Ai) != NULL) {
            GameBoard = c.update(GameBoard, AiMove, Ai);
            c.game_board = GameBoard;
            c.helpPrint();
        }*/
    }

}

