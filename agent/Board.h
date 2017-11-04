
#ifndef BOARD_H
#define BOARD_H
#include "Enumerations.h"
class Piece;
class Board {

public:
    
    Piece * board0x88 [128];
    unsigned long long bitBoards [14];
    bool castleKSide[2];
    bool castleQSide[2];
    
    Board();
    Board(const Board& orig);
    virtual ~Board();
private:
    

};

#endif /* BOARD_H */

