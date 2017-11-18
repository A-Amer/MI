#include "Piece.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Board.h"
#include <bits/stdc++.h>
#include <string> 

using namespace std;
void draw(unsigned long long d);
class Chess {
	public:
        Board * boardRep;
        map <char,File> FileMapping;
        map <char,int> RankMapping;
	string board;               //Part of FEN string that represents the board
	string turn;                //Side to move
	string castlingRights;      //Castling Rights for each side 
	string enPassantTargetSquare;    // en passant target square equals "-" if previous move was not pawn double push
	int halfMoveClock;              // counter that increments with each turn once
	int fullMoveCounter;            // counter that increments when both sides play once
	
	

	/* -------------- Initialization --------------*/
	Chess()
	{
                boardRep=new Board();
                FileMapping ={{'a',a},{'b',b},{'c',c},{'d',d},{'e',e},{'f',f},{'g',g},{'h',h},{'-',None}};
                RankMapping ={{'1',0},{'2',1},{'3',2},{'4',3},{'5',4},{'6',5},{'7',6},{'8',7}};
		board = "";
		turn = "";
		enPassantTargetSquare = "";
		castlingRights = "";
		halfMoveClock = 0;
		fullMoveCounter = 0;
	}
	
	/* -------------- Translation from FEN to 0x88 --------------*/
	vector<Piece*> BoardTo0x88(vector<string> s)
	{
		/* ((7 - i) * 16 + j )  is the index of the piece in the 0x88 board*/
		vector<Piece*> board(8 * 16);
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (s[i][j] == 'R')
				{
					board[(7 - i) * 16 + j] = this->boardRep->WhiteRookObj;
				}
				else if (s[i][j] == 'N')
				{
					board[(7 - i) * 16 + j] = this->boardRep->WhiteKnightObj;
				}
				else if (s[i][j] == 'B')
				{
					board[(7 - i) * 16 + j] = this->boardRep->WhiteBishopObj;
				}
				else if (s[i][j] == 'Q')
				{
					board[(7 - i) * 16 + j] = this->boardRep->WhiteQueenObj;
				}
				else if (s[i][j] == 'K')
				{
					board[(7 - i) * 16 + j] = this->boardRep->WhiteKingObj;
				}
				else if (s[i][j] == 'P')
				{
					board[(7 - i) * 16 + j] = this->boardRep->WhitePawnObj;
				}
				else if (s[i][j] == 'r')
				{
					board[(7 - i) * 16 + j] = this->boardRep->BlackRookObj;
				}
				else if (s[i][j] == 'n')
				{
					board[(7 - i) * 16 + j] = this->boardRep->BlackKnightObj;
				}
				else if (s[i][j] == 'b')
				{
					board[(7 - i) * 16 + j] = this->boardRep->BlackBishopObj;
				}
				else if (s[i][j] == 'q')
				{
					board[(7 - i) * 16 + j] = this->boardRep->BlackQueenObj;
				}
				else if (s[i][j] == 'k')
				{
					board[(7 - i) * 16 + j] = this->boardRep->BlackKingObj;
				}
				else if (s[i][j] == 'p')
				{
					board[(7 - i) * 16 + j] = this->boardRep->BlackPawnObj;
				}
			}
		}
		return board;
	}
        
	/* --------------Translation from FEN to Bitboards-------------- */
	vector<unsigned long long> BoardToBitboards(vector<string> s)
	{
            unsigned long long  WhiteKing=0;
            unsigned long long  WhiteQueen=0;
            unsigned long long  WhiteRooks=0;
            unsigned long long  WhiteBishops=0;
            unsigned long long  WhiteKnights=0;
            unsigned long long  WhitePawns=0;
            unsigned long long  BlackKing=0;
            unsigned long long  BlackQueen=0;
            unsigned long long  BlackRooks=0;
            unsigned long long  BlackBishops=0;
            unsigned long long  BlackKnights=0;
            unsigned long long  BlackPawns=0;
            
		// we bitwise OR (1 << (i * 8 + j)) to set the ((i * 8) + j)th bit
		vector<unsigned long long> board;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (s[7-i][j] == 'R')
				{
					unsigned long long  set = (unsigned long long )(pow(2, (i * 8 + j)));
					WhiteRooks |= set;
				}
				else if (s[7-i][j] == 'N')
				{
					unsigned long long  set = (unsigned long long )(pow(2, (i * 8 + j)));
					WhiteKnights |= set;
				}
				else if (s[7-i][j] == 'B')
				{
					unsigned long long  set = (unsigned long long )(pow(2, (i * 8 + j)));
					WhiteBishops |= set;
				}
				else if (s[7-i][j] == 'Q')
				{
					unsigned long long  set = (unsigned long long )(pow(2, (i * 8 + j)));
					WhiteQueen |= set;
				}
				else if (s[7-i][j] == 'K')
				{
					unsigned long long  set = (unsigned long long )(pow(2, (i * 8 + j)));
					WhiteKing |= set;
				}
				else if (s[7-i][j] == 'P')
				{
					unsigned long long  set = (unsigned long long )(pow(2, (i * 8 + j)));
					WhitePawns |= set;
				}
				else if (s[7-i][j] == 'r')
				{
					unsigned long long  set = (unsigned long long )(pow(2, (i * 8 + j)));
					BlackRooks |= set;
				}
				else if (s[7-i][j] == 'n')
				{
					unsigned long long  set = (unsigned long long )(pow(2, (i * 8 + j)));
					BlackKnights |= set;
				}
				else if (s[7-i][j] == 'b')
				{
					unsigned long long  set = (unsigned long long )(pow(2, (i * 8 + j)));
					BlackBishops |= set;
				}
				else if (s[7-i][j] == 'q')
				{
					unsigned long long  set = (unsigned long long )(pow(2, (i * 8 + j)));
					BlackQueen |= set;
				}
				else if (s[7-i][j] == 'k')
				{
					unsigned long long  set = (unsigned long long )(pow(2, (i * 8 + j)));
					BlackKing |= set;
				}
				else if (s[7-i][j] == 'p')
				{
					unsigned long long  set = (unsigned long long )(pow(2, (i * 8 + j)));
					BlackPawns |= set;
				}
			}
		}
		board.push_back(WhiteKing);
		board.push_back(WhiteQueen);
		board.push_back(WhiteRooks);
		board.push_back(WhiteBishops);
		board.push_back(WhiteKnights);
		board.push_back(WhitePawns);
		board.push_back(BlackKing);
		board.push_back(BlackQueen);
		board.push_back(BlackRooks);
		board.push_back(BlackBishops);
		board.push_back(BlackKnights);
		board.push_back(BlackPawns);
                board.push_back(WhiteKing|WhiteQueen|WhiteRooks|WhiteBishops|WhiteKnights|WhitePawns);
                board.push_back(BlackKing|BlackQueen|BlackRooks|BlackBishops|BlackKnights|BlackPawns);
               
		return board;
	}
        
	/* -------------- Parsing FEN string to a human-readable board --------------*/
	vector<string> FenToBoard(string FEN)
	{
		string board_row = "";
		vector<string> board;
		for (int i = 0; i < FEN.size(); i++)
		{
			if (FEN[i] >= '1' && FEN[i] <= '8')
			{
				for (int j = 0; j < FEN[i] - '0'; j++)
				{
					board_row += ".";
				}
			}
			else if (FEN[i] != '/')
			{
				board_row += FEN[i];
			}
			else
			{
				board.push_back(board_row);
				board_row = "";
			}
		}
		if (board_row != "")
		{
			board.push_back(board_row);
		}
		for (string row : board)
		{
			cout << row << endl;
		}
		return board;
	}
        
	/* -------------- Parsing FEN string --------------*/
	void parseFEN(string FEN)
	{
		vector<string> tokens;
		stringstream ss(FEN);
		string token;
		while (ss >> token) {
			tokens.push_back(token);
		}
		this->board = tokens[0];
		this->turn = tokens[1];
		this->castlingRights = tokens[2];
		this->enPassantTargetSquare = tokens[3];
		this->halfMoveClock = stoi(tokens[4]);
		this->fullMoveCounter = stoi(tokens[5]);
                boardRep->SetCastlingRights(this->castlingRights,turn,enPassantTargetSquare,FileMapping,RankMapping);
	}
                       
        void TestMoveGenerator()//used in testing 
        {
            list <Move*> generatedM;
            this->boardRep->MovesGenerator(generatedM);
            list <Move *> ::iterator  it = generatedM.begin();
            Move *temp;
            while(it != generatedM.end())
            {
                 temp = (*it); 
                cout<<"r:"<<temp->CurrPos/16<<" f: "<<temp->CurrPos%16<<"    ,   r:"<<temp->NextPos/16<<" f: "<<temp->NextPos%16<<"\n";
                it++;
            }
        }    
};

void draw(unsigned long long d)//used in testing 
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

void drawBoard (Board * b)//used in testing 
{
    for(int i =7 ; i >=0 ; i--)
    {
        for(int j=0;j<8;j++)
        {
            if(b->board0x88[i*16+j]!=0)
                cout<<b->board0x88[i*16+j]->drawchar()<<" ";
            else
                cout <<". ";
        }
        cout<<"\n";
    }
}

int main() {
	Chess* Game = new Chess();
	string FEN = "r111k11r/7p/8/6P1/1Pp5/8/R111111p/R11QKP11 b KQq b3 0 1";//change FEN
	Game->parseFEN(FEN);
	vector<string> board = Game->FenToBoard(Game->board);
	Game->boardRep->board0x88 = Game->BoardTo0x88(board);
	Game->boardRep->bitBoards = Game->BoardToBitboards(board);
        Game->TestMoveGenerator();
        Move * move = new Move();
        int r1,f1,r2,f2;
        char p;
        cout<<"\nenter selected move (a value from 0 to 7) :\n";
        cin >> r1;
        while(r1>=0)//this is a trial for applying and generating moves , enter -1 to stop
        {             
            cin >> f1 >> r2 >> f2;
            cin >> p;   // p is the type you want the pawn to be promoted to in case of promotion
            //enter Q:white queen, q:black queen, N: white knight, n:black knight,
            //R:white rook, r:black rook, B:white bishop, b:black bishop 
            //or any other character if the move doesn't lead to a promotion
            move->CurrPos = r1*16+f1;
            move->NextPos = r2*16+f2;
            Game->boardRep->ApplyMove(move,p);
            drawBoard(Game->boardRep);
            Game->TestMoveGenerator();
            Game->boardRep->heuristic();
            cout<<"\nenter selected move (a value from 0 to 7) :\n";
            cin >> r1;
        }
}