
#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"
class Pawn : public Piece {
public:
    Pawn(Color c);
    Pawn(){};
    Pawn(const Pawn& orig);
    virtual ~Pawn();
    string GetType(){return "pawn";}
    PieceType GetPieceType()
    {
        if(this->color==White)
            return WhitePawns;
        return BlackPawns;
    };
    char drawchar()
    {
        if(this->color==White)
            return 'P';
        return 'p';
    }
    void ValidMovesGenerator(int currentPos, Board * board, list <Move*> &generatedM);
private:

};

#endif /* PAWN_H */

