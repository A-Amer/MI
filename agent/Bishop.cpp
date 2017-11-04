
#include "Bishop.h"

Bishop::Bishop(Color c) {
    this->color = c;
}

Bishop::Bishop(const Bishop& orig) {
}

Bishop::~Bishop() {
}

void Bishop::ValidMovesGenerator(int currentPos, Board * board, list <Move*> &generatedM)// takes index of 0x88 
{
    bool next = true;
    int current = (currentPos/16)*8+currentPos%16;
    int f , r , index , direction;
    int directions[4]={-15,15,-17,17};
    
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
                    generatedM.push_back(new Move(current ,  (index/16)*8+(index%16)));

                else 
                {
                    if( board->board0x88[index]->color!=this->color)
                        generatedM.push_back(new Move(current ,  (index/16)*8+(index%16)));
                    next=false;
                }
            }
            else
                next=false;
        }  
    }
}

