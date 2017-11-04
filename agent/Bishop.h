
#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

class Bishop : public Piece  {
public:
    Bishop(Color c);
    Bishop(){};
    Bishop(const Bishop& orig);
    virtual ~Bishop();
    void ValidMovesGenerator(int currentPos, Board * board, list <Move*> &generatedM);
private:

};

#endif /* BISHOP_H */

