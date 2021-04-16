# include <iostream>
using namespace std;

bool isCorner(int* playerMove) {
    if(playerMove[0] == 0 || playerMove[1] == 7 || playerMove[0] == 0 || playerMove[1] == 7 )
        return true;
    else
        return false;
    
}

/* bool isRisk(int* playerMove) {
    if(playerMove[0] == 1 || playerMove[1] == 7 || playerMove[0] == 0 || playerMove[1] == 7 )
        return true;
    else
        return false;
}*/