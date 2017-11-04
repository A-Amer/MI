

#ifndef POSITION_H
#define POSITION_H
#include "Enumerations.h"

class Position {
    
public:
    File file;
    int rank;
    
    Position(File f , int r);
    Position();
    Position(const Position& orig);
    virtual ~Position();
    
private:
    
    

};

#endif /* POSITION_H */

