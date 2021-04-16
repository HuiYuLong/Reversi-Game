/*
 * AiTech.h
 * 
 * 
 *
 *                  
 *
 * Author: HuiYu Long
 * Date: July 29, 2019
 */
# pragma once
# include <iostream>
# include <stdlib.h>
# include <string>
# include <vector>


class AiTech {
    private:
    public:
        AiTech();

        // Post Condition: update the GameBoard after one 
        //                 player made his move, and return
        //                 the updated GameBoard
        char** temp_update(char** GameBoard, int* playerMove, char* Player);
        int random(int MAX_NUM);
        int* Best(int** BestMoves);
        bool simulate(char** GameBoard, int* AiMove);
        int* BestMove(char** GameBoard, int num_random_plays, int* AiMove);
};
