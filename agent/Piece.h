#ifndef PIECE_H
#define PIECE_H
#include "Move.h"
#include "Board.h"
#include <bits/stdc++.h>
using namespace std;



class Piece {
public:
    Color color;
    
    Piece();
    Piece(const Piece& orig);
    virtual ~Piece();
    virtual void ValidMovesGenerator(int currentPos, Board * board, list <Move*> &generatedM)= 0;
    virtual string GetType()=0;
    virtual PieceType GetPieceType()=0;
    virtual char drawchar()=0;
    

    
private:

};

#endif /* PIECE_H */

