
#include "Board.h"
#include "Rook.h"
#include "King.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
/*function used for testing*/

Board::Board() {
  
    /*Correct Initial Values*/
    this->castleKSide[0]=1;
    this->castleQSide[0]=1;
    this->castleKSide[1]=1;
    this->castleQSide[1]=1;

}

void Board::SetCastlingRights(string s , string turn)
{
    if(turn=="b")
        this->turn=Black;
    else
        this->turn=White;
    this->castleKSide[0]=0;
    this->castleQSide[0]=0;
    this->castleKSide[1]=0;
    this->castleQSide[1]=0;
    if(s[0]=='-')
        return;
    for(int i=0 ; i< s.size() ; i++)
    {
        if(s[i]=='K')
            this->castleKSide[0]=1;
        else if(s[i]=='Q')
            this->castleQSide[0]=1;
        else if (s[i]=='k')
            this->castleKSide[1]=1;
        else if (s[i]=='q')
            this->castleQSide[1]=1;
    }       
}

Board::Board(const Board& orig) {
}

Board::~Board() {
}

