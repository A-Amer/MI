
#include "Queen.h"

Queen::Queen(Color c) {
    this->color = c;
}
Queen::Queen(const Queen& orig) {
}

Queen::~Queen() {
}

void Queen::ValidMovesGenerator(int currentPos, Board * board, list <Move*> &generatedM)
{
    Bishop b;
    b.color=this->color;
    b.ValidMovesGenerator(currentPos,board,generatedM);
    Rook r;
    r.color=this->color;
    r.ValidMovesGenerator(currentPos,board,generatedM);
}
