
#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"
class Pawn : public Piece {
public:
    Pawn(Color c);
    Pawn(){};
    Pawn(const Pawn& orig);
    virtual ~Pawn();
    void ValidMovesGenerator(int currentPos, Board * board, list <Move*> &generatedM);
private:

};

#endif /* PAWN_H */

