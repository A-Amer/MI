
#include "Move.h"

Move::Move(int from , int to) {
    
    this->CurrPos= from;
    this->NextPos= to;
    
}
Move::Move(){};

Move::Move(const Move& orig) {
}

Move::~Move() {
}

