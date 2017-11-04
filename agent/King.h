
#ifndef KING_H
#define KING_H
#include "Piece.h"
#include "Position.h"
#include <math.h>
class King : public Piece {
public:
    King(Color c);
    King(){};
    King(const King& orig);
    virtual ~King();
    void ValidMovesGenerator(int currentPos, Board * board, list <Move*> &generatedM);
    
private:
    const unsigned long long kingMask = 0x01c141c00;
    Position * kingMaskPos = new Position (D,2) ;
    const unsigned long long kingCastleMask[4] = {0xe,0x0e00000000000000,0x60,0x6000000000000000};

};

#endif /* KING_H */

