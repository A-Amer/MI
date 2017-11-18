
#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"
using namespace std;

class Bishop : public Piece  {
public:
    Bishop(Color c);
    Bishop(){};
    Bishop(const Bishop& orig);
    virtual ~Bishop();
    void ValidMovesGenerator(int currentPos, Board * board, list <Move*> &generatedM);
    string GetType(){return "bishop"; };
    PieceType GetPieceType()
    {
        if(this->color==White)
            return WhiteBishops;
        return BlackBishops;
    };
    char drawchar()
    {
        if(this->color==White)
            return 'B';
        return 'b';
    }
private:

};

#endif /* BISHOP_H */

