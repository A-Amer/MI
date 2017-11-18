
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
    string GetType(){return "knight";}
    void ValidMovesGenerator(int currentPos, Board * board, list <Move*> &generatedM);
    PieceType GetPieceType()
    {
        if(this->color==White)
            return WhiteKnights;
        return BlackKnights;
    };
    char drawchar()
    {
        if(this->color==White)
            return 'N';
        return 'n';
    }

private:
    const unsigned long long knightMask = 0x284400442800 ;
    Position * knightMaskPos = new Position (e,3) ;
};

#endif /* KNIGHT_H */

