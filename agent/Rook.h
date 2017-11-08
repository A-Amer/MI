
#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"
class Rook : public Piece {
public:
    Rook(Color c);
    Rook(){};
    Rook(const Rook& orig);
    virtual ~Rook();
    string GetType(){return "rook";}
    void ValidMovesGenerator(int currentPos, Board * board, list <Move*> &generatedM);
private:
    

};

#endif /* ROOK_H */

