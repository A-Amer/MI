#ifndef PIECE_H
#define PIECE_H
#include "Move.h"
#include "Board.h"
#include <list> 
using namespace std;

class Piece {
public:
    Color color;
    
    Piece();
    Piece(const Piece& orig);
    virtual ~Piece();
    virtual void ValidMovesGenerator(int currentPos, Board * board, list <Move*> &generatedM)= 0;

    
private:

};

#endif /* PIECE_H */

