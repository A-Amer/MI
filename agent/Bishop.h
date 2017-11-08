
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
    string GetType(){return "bishop"; }
private:

};

#endif /* BISHOP_H */

