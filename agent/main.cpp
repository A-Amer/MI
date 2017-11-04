
//#include <cstdlib>
#include "Enumerations.h"
#include "Board.h"
#include "Position.h"
#include "Move.h"
#include "King.h"
#include"Rook.h"
#include"Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include <iostream>
#include <list> 
#include <math.h>
using namespace std;
void draw(unsigned long long d)
{
    
    for (int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(d%2==0)
            {
                d=d>>1;
                cout<<"0  ";
            }
            else 
            {
                d=d>>1;
                cout<<"1  ";
            }
        }
        cout<<"\n";
        
    }
    cout<<"\n---------------------------------------------------\n";
    
}

void MovesGenerator(Board * board, list<Move*> &generatedM)//no castling moves yet
{
    int i=0;
    for(int j=0 ; j<8 ; j++)
    {
        while(!(i & 0x88))
        {
            if(board->board0x88[i]!=0)
                board->board0x88[i]->ValidMovesGenerator(i,board,generatedM);
            i++;
        }
        i+=8;
    }
    return;
}

void TestMoveGenerator()//change the initial values in the board constructor to get different moves  
{
    Board * b = new Board();
    list <Move*> generatedM;
    MovesGenerator(b,generatedM);
    list <Move *> ::iterator  it = generatedM.begin();
    Move *temp;
    while(it != generatedM.end())
    {
         temp = (*it); 
        cout<<"r:"<<temp->CurrPos/8<<" f: "<<temp->CurrPos%8<<"    ,   r:"<<temp->NextPos/8<<" f: "<<temp->NextPos%8<<"\n";
        it++;
    }
}

int main()
{
    TestMoveGenerator();
    return 0;
}
