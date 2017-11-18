
#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"
#include "Bishop.h"
#include "Rook.h"

class Queen : public Piece{
public:
    Queen(Color c);
    Queen(){};
    Queen(const Queen& orig);
    virtual ~Queen();
    string GetType(){return "queen";}
    PieceType GetPieceType()
    {
        if(this->color==White)
            return WhiteQueen;
        return BlackQueen;
    };
    char drawchar()
    {
        if(this->color==White)
            return 'Q';
        return 'q';
    }
    void ValidMovesGenerator(int currentPos, Board * board, list <Move*> &generatedM);
private:

};

#endif /* QUEEN_H */

