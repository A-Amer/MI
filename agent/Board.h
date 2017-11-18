
#ifndef BOARD_H
#define BOARD_H
#include "Enumerations.h"
#include <vector>
#include "Move.h"
#include"Position.h"
//#include "Bishop.h"
//#include "King.h"
//#include "Queen.h"
//#include "Pawn.h"
//#include "Rook.h"
//#include "Knight.h"
#include <bits/stdc++.h>
using namespace std;
class Piece;
class King;
class Pawn;
class Queen;
class Knight;
class Rook;
class Bishop;
class Board {

public:
    vector<Piece *> board0x88{vector<Piece *>(128)};
   //Piece * board0x88 [128];
    vector<unsigned long long> bitBoards{vector<unsigned long long> (14)};
 
    bool castleKSide[2];
    bool castleQSide[2];
    Color turn;
    Position * enPassent;
    /* -------------- Chess Pieces Declaration --------------*/
	King* BlackKingObj;
	King*WhiteKingObj;
	Bishop* BlackBishopObj;
	Bishop* WhiteBishopObj;
	Pawn* BlackPawnObj;
	Pawn* WhitePawnObj;
	Queen* BlackQueenObj;
	Queen* WhiteQueenObj;
	Knight* BlackKnightObj;
	Knight* WhiteKnightObj;
	Rook* BlackRookObj;
	Rook* WhiteRookObj;
    void SetCastlingRights(string s, string turn, string enPassentTS, map <char,File> lookupF,map <char,int> lookupR);
    void MovesGenerator(list<Move*> &generatedM);
    void ApplyMove(Move * m,char promotion);
    double heuristic();
    Board();
    Board(const Board& orig);
    virtual ~Board();
private:
    

};

#endif /* BOARD_H */

