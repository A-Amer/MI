
#include "Position.h"

Position::Position(File f , int r) {
    
    this->file = f;
    this->rank = r;
}
Position::Position()
{
    
}

Position::Position(const Position& orig) {
}

Position::~Position() {
}

