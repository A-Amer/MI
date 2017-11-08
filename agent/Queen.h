
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
    void ValidMovesGenerator(int currentPos, Board * board, list <Move*> &generatedM);
private:

};

#endif /* QUEEN_H */

