/*
 * Reversi.h
 * 
 * 
 *
 *                  
 *
 * Author: HuiYu Long
 * Date: July 15, 2019
 */
# pragma once
# include <iostream>
# include <stdlib.h>
# include <string>


class Reversi {
    private:
        // recording a reversi game's UserCount and AiCount
        int UserCount;
        int AiCount;
        //char player;

    public:
        char** game_board;
        Reversi();
        char** init_game_board();

        // Pre Condition: check if the given move is available
        // Post Condition: return true if the given move is available
        //                 else return false
        //bool available_move(char** GameBoard, int* playerMove, char* player,)
        
        // Post Condition: update the GameBoard after one 
        //                 player made his move, and return
        //                 the updated GameBoard
        char** update(char** GameBoard, int* playerMove, char Player);

        //void start_a_new_game();
        void helpPrint(char** GameBoard);
        void helpPrint();
};
