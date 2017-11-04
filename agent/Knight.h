
#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"
#include "Position.h"
#include <math.h>
class Knight : public Piece {
public:
    Knight(Color c);
    Knight (){};
    Knight(const Knight& orig);
    virtual ~Knight();
    void ValidMovesGenerator(int currentPos, Board * board, list <Move*> &generatedM);

private:
    const unsigned long long knightMask = 0x284400442800 ;
    Position * knightMaskPos = new Position (E,3) ;
};

#endif /* KNIGHT_H */

