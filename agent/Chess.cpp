#include "Piece.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Board.h"
#include <bits/stdc++.h>
using namespace std;
void draw(unsigned long long d);
class Chess {
	public:
        Board * boardRep;
	string board;               //Part of FEN string that represents the board
	string turn;                //Side to move
	string castlingRights;      //Castling Rights for each side 
	string enPassantTargetSquare;    // en passant target square equals "-" if previous move was not pawn double push
	int halfMoveClock;              // counter that increments with each turn once
	int fullMoveCounter;            // counter that increments when both sides play once
	
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
	
	/* -------------- Bitboard 64-bit Integers Declaration --------------*/
	unsigned long long  WhiteKing;
	unsigned long long  WhiteQueen;
	unsigned long long  WhiteRooks;
	unsigned long long  WhiteBishops;
	unsigned long long  WhiteKnights;
	unsigned long long  WhitePawns;
	unsigned long long  WhitePieces;
	unsigned long long  BlackKing;
	unsigned long long  BlackQueen;
	unsigned long long  BlackRooks;
	unsigned long long  BlackBishops;
	unsigned long long  BlackKnights;
	unsigned long long  BlackPawns;
	unsigned long long  BlackPieces;

	/* -------------- Initialization --------------*/
	Chess()
	{
                boardRep=new Board();
		board = "";
		turn = "";
		enPassantTargetSquare = "";
		castlingRights = "";
		BlackKingObj = new King(Black);
		WhiteKingObj = new King(White);
		BlackBishopObj = new Bishop(Black);
		WhiteBishopObj = new Bishop(White);
		BlackPawnObj = new Pawn(Black);
		WhitePawnObj = new Pawn(White);
		BlackQueenObj = new Queen(Black);
		WhiteQueenObj = new Queen(White);
		BlackKnightObj = new Knight(Black);
		WhiteKnightObj = new Knight(White);
		BlackRookObj = new Rook(Black);
		WhiteRookObj = new Rook(White);
		WhiteKing = 0;
		WhiteQueen = 0;
		WhiteRooks = 0;
		WhiteBishops = 0;
		WhiteKnights = 0;
		WhitePawns = 0;
		WhitePieces = 0;
		BlackKing = 0;
		BlackQueen = 0;
		BlackRooks = 0;
		BlackBishops = 0;
		BlackKnights = 0;
		BlackPawns = 0;
		BlackPieces = 0;
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
					board[(7 - i) * 16 + j] = WhiteRookObj;
				}
				if (s[i][j] == 'N')
				{
					board[(7 - i) * 16 + j] = WhiteKnightObj;
				}
				if (s[i][j] == 'B')
				{
					board[(7 - i) * 16 + j] = WhiteBishopObj;
				}
				if (s[i][j] == 'Q')
				{
					board[(7 - i) * 16 + j] = WhiteQueenObj;
				}
				if (s[i][j] == 'K')
				{
					board[(7 - i) * 16 + j] = WhiteKingObj;
				}
				if (s[i][j] == 'P')
				{
					board[(7 - i) * 16 + j] = WhitePawnObj;
				}
				if (s[i][j] == 'r')
				{
					board[(7 - i) * 16 + j] = BlackRookObj;
				}
				if (s[i][j] == 'n')
				{
					board[(7 - i) * 16 + j] = BlackKnightObj;
				}
				if (s[i][j] == 'b')
				{
					board[(7 - i) * 16 + j] = BlackBishopObj;
				}
				if (s[i][j] == 'q')
				{
					board[(7 - i) * 16 + j] = BlackQueenObj;
				}
				if (s[i][j] == 'k')
				{
					board[(7 - i) * 16 + j] = BlackKingObj;
				}
				if (s[i][j] == 'p')
				{
					board[(7 - i) * 16 + j] = BlackPawnObj;
				}
				if (((i * 16 + j) % 16 )== 0 && (i * 16 + j) != 0)
				{
					cout << endl;
				}
				cout << i * 16 + j << " ";
			}
		}
		return board;
	}
        
	/* --------------Translation from FEN to Bitboards-------------- */
	vector<unsigned long long> BoardToBitboards(vector<string> s)
	{
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
                boardRep->SetCastlingRights(this->castlingRights,turn);
	}
};

void MovesGenerator(Board * board, list<Move*> &generatedM,Color c)//no castling moves yet
{
    int i=0;
    for(int j=0 ; j<8 ; j++)
    {
        while(!(i & 0x88))
        {
            if(board->board0x88[i]!=0)
            {
                if (board->board0x88[i]->color==c)
                    board->board0x88[i]->ValidMovesGenerator(i,board,generatedM);
            }
            i++;
        }
        i+=8;
    }
    return;
}

void TestMoveGenerator(Board * b,Color c)//change the initial values in the board constructor to get different moves  
{
    list <Move*> generatedM;
    MovesGenerator(b,generatedM,c);
    list <Move *> ::iterator  it = generatedM.begin();
    Move *temp;
    while(it != generatedM.end())
    {
         temp = (*it); 
        cout<<"r:"<<temp->CurrPos/16<<" f: "<<temp->CurrPos%16<<"    ,   r:"<<temp->NextPos/16<<" f: "<<temp->NextPos%16<<"\n";
        it++;
    }
}

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

int main() {
	Chess* Game = new Chess();
	string FEN = "r111k11r/pppp1p1p/5P2/8/8/8/RP111P1P/111QK111 b KQkq e3 0 1";//change FEN
	Game->parseFEN(FEN);
	vector<string> board = Game->FenToBoard(Game->board);
	Game->boardRep->board0x88 = Game->BoardTo0x88(board);
	Game->boardRep->bitBoards = Game->BoardToBitboards(board);
        cout<<"\n\n";
        TestMoveGenerator(Game->boardRep,Game->boardRep->turn);//change Color
}