
#include "King.h"
#include <iostream>

King::King(Color c) {
    this->color = c;
}

King::King(const King& orig) {
}

King::~King() {
}

void draw(unsigned long long d);

void King::ValidMovesGenerator(int currentPos, Board * board, list <Move*> &generatedM)// takes index of 0x88 
{

    unsigned long long newMask;
    int shift=0;
    Position current;
    current.file=static_cast<File>(currentPos%16);
    current.rank=currentPos/16;
    shift = kingMaskPos->file - current.file;
    if(shift >=0)//shift king mask left
        newMask= (kingMask >> shift) & ~FILE_H;
    else //shift king mask right
        newMask= (kingMask << (-shift)) & ~FILE_A;
    
    shift = kingMaskPos->rank - current.rank;
    if(shift >=0)//shift king mask up
        newMask= (newMask >> shift*8);
    else //shift king mask down
        newMask= (newMask << (-shift*8));
    
    newMask = newMask & ~ board->bitBoards[this->color+12];
    unsigned long long m;
    int index;

    while (newMask!=0)
    {
        index = floor(log2(newMask));
      
        if (index >30)
        {
            m=(1<<30);
            m=m<<index-30;
        }
        else
            m=1<<index;

        newMask = newMask & ~m;
        generatedM.push_back(new Move(currentPos , (index/8)*16+(index%8)));
    }
    if(board->castleQSide[this->color])
    {
        if(QSCastlingMove(current.file,current.rank, board))
            generatedM.push_back(new Move(currentPos , currentPos-2));
    }
    if(board->castleKSide[this->color])
    {
        if(KSCastlingMove(current.file,current.rank, board))
            generatedM.push_back(new Move(currentPos , currentPos+2));
    }
    return ;
}

bool King::QSCastlingMove(int f, int r, Board* board)
{//0:QSideWhite,1:QSideBlack
    int enumdiff [2]={6,0};
    int direction [2]={1,-1};

    if(this->EmptyCastleMask[this->color]&(board->bitBoards[WhitePieces]|board->bitBoards[BlackPieces]))
    {
        //cout<<"\n\nNo Queen Side Castling for "<<this->color<<"\n\n";
        return false;
    }
    if (!BRQCastling(f, r, board,1, "rook"))
    {
        //cout<<"\n\nNo Queen Side Castling for "<<this->color<<" : Rook or Queen in the way horizontally \n\n";
        return false;
    }
    
    for (int i=0;i<3;i++)
    {
        if((KnightCasleMask[this->color]>>i)&board->bitBoards[WhiteKnights+enumdiff[this->color]])
        {
            //cout<<"\n\nNo Queen Side Castling for "<<this->color<<" : Knight in the way-> "<<i<<" \n\n";
            return false;
        }
        if((PawnCastleMask[this->color]>>i)&board->bitBoards[WhitePawns+enumdiff[this->color]])
        {
            //cout<<"\n\nNo Queen Side Castling for "<<this->color<<" : Pawn in the way-> "<<i<<"\n\n";
            return false;
        }
        if((KingCastleMask[this->color]>>i)&board->bitBoards[WhiteKing+enumdiff[this->color]])
        {
            //cout<<"\n\nNo Queen Side Castling for "<<this->color<<" : King in the way-> "<<i<<"\n\n";
            return false;
        }
        if(!BRQCastling(f, r, board,16*direction[this->color], "rook"))
        {
            //cout<<"\n\nNo Queen Side Castling for "<<this->color<<" : Rook or Queen in the way vertically-> "<<i<<"\n\n";
        return false;
    }
        if(!BRQCastling(f, r, board,15*direction[this->color], "bishop"))
        {
            //cout<<"\n\nNo Queen Side Castling for "<<this->color<<" : Bishop or Queen in the way top right-> "<<i<<"\n\n";
            return false;
        }
        if(!BRQCastling(f, r, board,17*direction[this->color], "bishop"))
        {
            //cout<<"\n\nNo Queen Side Castling for "<<this->color<<" : Rook or Queen in the way top left-> "<<i<<"\n\n";
            return false;
        }
        f--;
    }
}

bool King::KSCastlingMove(int f, int r, Board * board)
{//2:QSideWhite,3:QSideBlack
    int enumdiff [2]={6,0};
    int direction [2]={1,-1};
    
    if(this->EmptyCastleMask[this->color+2]&(board->bitBoards[WhitePieces]|board->bitBoards[BlackPieces]))
    {
        //cout<<"\n\nNo King Side Castling for "<<this->color<<"\n\n";
        return false;
    }
    if (!BRQCastling(f, r, board,-1, "rook"))
    {
        //cout<<"\n\nNo King Side Castling for "<<this->color<<" : Rook or Queen in the way horizontally \n\n";
        return false;
    }
    
    for (int i=0;i<3;i++)
    {
        if((KnightCasleMask[this->color]<<i)&board->bitBoards[WhiteKnights+enumdiff[this->color]])
        {
            //cout<<"\n\nNo King Side Castling for "<<this->color<<" : Knight in the way-> "<<i<<" \n\n";
            return false;
        }
        if((PawnCastleMask[this->color]<<i)&board->bitBoards[WhitePawns+enumdiff[this->color]])
        {
            //cout<<"\n\nNo King Side Castling for "<<this->color<<" : Pawn in the way-> "<<i<<"\n\n";
            return false;
        }
        if((KingCastleMask[this->color]<<i)&board->bitBoards[WhiteKing+enumdiff[this->color]])
        {
            //cout<<"\n\nNo King Side Castling for "<<this->color<<" : King in the way-> "<<i<<"\n\n";
            return false;
        }
        if(!BRQCastling(f, r, board,16*direction[this->color], "rook"))
        {
        //cout<<"\n\nNo King Side Castling for "<<this->color<<" : Rook or Queen in the way vertically-> "<<i<<"\n\n";
        return false;
    }
        if(!BRQCastling(f, r, board,15*direction[this->color], "bishop"))
        {
            //cout<<"\n\nNo King Side Castling for "<<this->color<<" : Bishop or Queen in the way top right-> "<<i<<"\n\n";
            return false;
        }
        if(!BRQCastling(f, r, board,17*direction[this->color], "bishop"))
        {
            //cout<<"\n\nNo King Side Castling for "<<this->color<<" : Rook or Queen in the way top left-> "<<i<<"\n\n";
            return false;
        }
        f++;
    }
}

bool King::BRQCastling(int f, int r, Board* board, int direction,string BorR)
{//return false if king is in check
    int index;
    while(true)
    {
        f+=direction;
        index = 16 * r + f;
        if(!(index & 0x88))
        {
            if (board->board0x88[index]!=0)                   
            {
                if(board->board0x88[index]->color!=this->color
                        &&(board->board0x88[index]->GetType()==BorR||
                        board->board0x88[index]->GetType()=="queen"))
                    return false;
                else                
                    return true;                
            }
        }
        else
            return true;
    }     
}

