#include "Rook.h"

Rook::Rook(Color c) {
    this->color=c;
}

Rook::Rook(const Rook& orig) {
}

Rook::~Rook() {
}

void Rook::ValidMovesGenerator(int currentPos, Board * board, list <Move*> &generatedM)// takes index of 0x88 
{
    bool next = true;
    int f , r , index , direction;
    int directions[4]={-1,1,-16,16};
    
    for(int i = 0; i<4 ; i++)
    {
        next = true;
        f = currentPos%16;
        r = currentPos/16;
        direction = directions[i];
        while(next)
        {
            f+=direction;
            index = 16 * r + f;
            if(!(index & 0x88))
            {
                if (board->board0x88[index]==0)
                    generatedM.push_back(new Move(currentPos , index));

                else 
                {
                    if(board->board0x88[index]->color!=this->color)
                        generatedM.push_back(new Move(currentPos , index));
                    next=false;
                }
            }
            else
                next=false;
        }  
    }
}
