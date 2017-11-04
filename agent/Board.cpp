
#include "Board.h"
#include "Rook.h"
#include "King.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
/*function used for testing*/
unsigned long long ToBitBoardConverter(int r,File f)//r:0 -> 7 , f:A -> H
{
    int fi=f;
    int index = r*8+f;
    unsigned long long m;
    if (index >30)
    {
        m=(1L<<30);
        m=m<<index-30;
    }
    else
        m=1<<index;
    return m;
}
Board::Board() {
 
    /*Random Initial values for testing only*/
    this->bitBoards[BlackRooks]=ToBitBoardConverter(4,D);
    this->bitBoards[BlackBishops]=ToBitBoardConverter(4,B);
    this->bitBoards[BlackKing]=ToBitBoardConverter(2,F);
    this->bitBoards[BlackQueen]=0;
    this->bitBoards[BlackKnights]=0;
    this->bitBoards[WhiteKing]=0;
    this->bitBoards[WhiteQueen]=ToBitBoardConverter(3,C);
    this->bitBoards[WhiteRooks]=0;
    this->bitBoards[WhiteBishops]=0;
    this->bitBoards[WhiteKnights]=ToBitBoardConverter(5,C);
    this->bitBoards[WhitePawns]=ToBitBoardConverter(4,C)|ToBitBoardConverter(1,C);
        
    this->board0x88[0x43]=new Rook(Black);
    this->board0x88[0x41]=new Bishop (Black);
    this->board0x88[0x32]=new Queen (White);
    this->board0x88[0x52]=new Knight (White);
    this->board0x88[0x25]=new King (Black);
    this->board0x88[0x42]=new Pawn(White);
    this->board0x88[0x12]=new Pawn(White);
    
    /*Correct Initial Values*/
    this->castleKSide[0]=1;
    this->castleQSide[0]=1;
    this->castleKSide[1]=1;
    this->castleQSide[1]=1;
    this->bitBoards[WhitePieces]=bitBoards[WhiteKing]|bitBoards[WhiteQueen]|bitBoards[WhiteRooks]|
          bitBoards[WhiteBishops]|bitBoards[WhiteKnights]|bitBoards[WhitePawns];
    this->bitBoards[BlackPieces]=bitBoards[BlackKing]|bitBoards[BlackQueen]|bitBoards[BlackRooks]|
          bitBoards[BlackBishops]|bitBoards[BlackKnights]|bitBoards[BlackPawns];
}

Board::Board(const Board& orig) {
}

Board::~Board() {
}

