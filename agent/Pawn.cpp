
#include "Pawn.h"
Pawn::Pawn(Color c) {
    this->color = c;
}

Pawn::Pawn(const Pawn& orig) {
}

Pawn::~Pawn() {
}

void Pawn::ValidMovesGenerator(int currentPos, Board* board, list<Move*>& generatedM)
{
    int index ;
    int initialRank[2]={1,6};
    int attack[4]= {17,-17,15,-15};
    int step[2]={16,-16};
    index = currentPos+step[this->color];
    if(!(index & 0x88))//one step forward
    {
        if(board->board0x88[index]==0)
        {
            generatedM.push_back(new Move(currentPos,index));
            if((currentPos/16)==initialRank[this->color])//two steps forward if first time to move
            {
                index = currentPos+2*step[this->color];
                if(!(index & 0x88))
                {
                    if(board->board0x88[index]==0)
                        generatedM.push_back(new Move(currentPos,index));
                }                   
            }
        }
    }
    index = currentPos+attack[this->color];   
    for(int i=0;i<2;i++)
    {
        if(!(index & 0x88))
        {
            if(board->board0x88[index]!=0)
            {
                if(board->board0x88[index]->color!=this->color)
                    generatedM.push_back(new Move(currentPos,index));
            }
        }
        index = currentPos+attack[this->color+2];
    }
    
    if(board->enPassent->file != None)
    {
        index = (board->enPassent->rank) * 16 + board->enPassent->file + step[1-this->color];
        if(abs(index - currentPos)==1)
            generatedM.push_back(new Move(currentPos,index+step[this->color]));
    }
    
}