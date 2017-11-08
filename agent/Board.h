
#ifndef BOARD_H
#define BOARD_H
#include "Enumerations.h"
#include <vector>
#include <bits/stdc++.h>
using namespace std;
class Piece;
class Board {

public:
    vector<Piece *> board0x88{vector<Piece *>(128)};
    vector<unsigned long long> bitBoards{vector<unsigned long long> (14)};
 
    bool castleKSide[2];
    bool castleQSide[2];
    Color turn;
    void SetCastlingRights(string s, string turn);
    Board();
    Board(const Board& orig);
    virtual ~Board();
private:
    

};

#endif /* BOARD_H */

