
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
    string GetType(){return "king";};
    void ValidMovesGenerator(int currentPos, Board * board, list <Move*> &generatedM);
    bool QSCastlingMove(int f, int r, Board * board);
    bool KSCastlingMove(int f, int r, Board * board);
    bool BRQCastling(int f, int r, Board * board, int direction,string BorR);
    PieceType GetPieceType()
    {
        if(this->color==White)
            return WhiteKing;
        return BlackKing;
    };
    char drawchar()
    {
        if(this->color==White)
            return 'K';
        return 'k';
    }
 
private:
    const unsigned long long kingMask = 0x01c141c00;
    Position * kingMaskPos = new Position (d,2) ;
    const unsigned long long EmptyCastleMask[4] = {0xe,0x0e00000000000000,0x60,0x6000000000000000};
    const unsigned long long KnightCasleMask[2] = {0x0284400,0x44280000000000};
    const unsigned long long PawnCastleMask[2] = {0x02800,0x028000000000000};
    const unsigned long long KingCastleMask[2] = {0x03828,0x2838000000000000};
};

#endif /* KING_H */

