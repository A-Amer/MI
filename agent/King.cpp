
#include "King.h"
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
    currentPos = current.rank*8+current.file;
    int j=0;
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
        //m = pow(2,index);
        newMask = newMask & ~m;
        generatedM.push_back(new Move(currentPos , index));
        j++;
    }
    return ;
}