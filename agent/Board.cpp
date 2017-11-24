
#include "Board.h"
#include "King.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Queen.h"
#include "Knight.h"



Board::Board() {
  
    this->castleKSide[0]=1;
    this->castleQSide[0]=1;                                                         
    this->castleKSide[1]=1;
    this->castleQSide[1]=1;
    
    this->enPassent = new Position (None,-1);
    this->turn = White;
    
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

}

void Board::SetCastlingRights(string s , string turn, string enPassentTS, map <char,File> lookupF,map <char,int> lookupR)
{
    if(turn=="b")
        this->turn=Black;
    else
        this->turn=White;
    this->castleKSide[0]=0;
    this->castleQSide[0]=0;
    this->castleKSide[1]=0;
    this->castleQSide[1]=0;
    if(enPassentTS[0]!='-')
    {        
        this->enPassent->file = lookupF[enPassentTS[0]];
        this->enPassent->rank = lookupR[enPassentTS[1]];
    }
        
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
    this->castleKSide[0]=orig.castleKSide[0];
    this->castleKSide[1]=orig.castleKSide[1];
    this->castleQSide[0]=orig.castleQSide[0];
    this->castleQSide[1]=orig.castleQSide[1];
    
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
    
    this->turn=orig.turn;
    this->enPassent = new Position(orig.enPassent->file,orig.enPassent->rank);
    
    PieceType type;
    int i=0;
    for(int j=0 ; j<8 ; j++)
    {
        while(!(i & 0x88))
        {
            if(orig.board0x88[i]!=0)
            {
                type=orig.board0x88[i]->GetPieceType();
                switch(type){
                    case WhiteQueen:
                        this->board0x88[i]=this->WhiteQueenObj;                  
                        break;
                    case BlackQueen:
                        this->board0x88[i]=this->BlackQueenObj;
                        break;
                    case WhiteKnights:
                        this->board0x88[i]=this->WhiteKnightObj;
                        break;
                    case BlackKnights:
                        this->board0x88[i]=this->BlackKnightObj;
                        break;
                    case WhiteRooks:
                        this->board0x88[i]=this->WhiteRookObj;
                        break;
                    case BlackRooks:
                        this->board0x88[i]=this->BlackRookObj;
                        break;
                    case WhiteBishops:
                        this->board0x88[i]=this->WhiteBishopObj;
                        break;
                    case BlackBishops:
                        this->board0x88[i]=this->BlackBishopObj;
                        break; 
                    case WhiteKing:
                        this->board0x88[i]=this->WhiteKingObj;
                        break;
                    case BlackKing:
                        this->board0x88[i]=this->BlackKingObj;
                        break;
                    case WhitePawns:  
                        this->board0x88[i]=this->WhitePawnObj;
                        break;
                    case BlackPawns:
                        this->board0x88[i]=this->BlackPawnObj;
                        break;
                }
            }
            i++;
        }
        i+=8;
    }
    
    for(int i=0;i<14;i++){
        this->bitBoards[i]=orig.bitBoards[i];
    }
}

Board::~Board() {
    this->board0x88.clear();
    this->bitBoards.clear();
    
    delete this->BlackBishopObj;
    delete this->BlackKingObj;
    delete this->BlackKnightObj;
    delete this->BlackPawnObj;
    delete this->BlackQueenObj;
    delete this->BlackRookObj;
    
    delete this->WhiteBishopObj;
    delete this->WhiteKingObj;
    delete this->WhiteKnightObj;
    delete this->WhitePawnObj;
    delete this->WhiteQueenObj;
    delete this->WhiteRookObj;
    
    delete this->enPassent;
}

void Board::MovesGenerator(list<Move*> &generatedM)
{
    int i=0;
    for(int j=0 ; j<8 ; j++)
    {
        while(!(i & 0x88))
        {
            if(board0x88[i]!=0)
            {
                if (board0x88[i]->color==this->turn)
                    board0x88[i]->ValidMovesGenerator(i,this,generatedM);
            }
            i++;
        }
        i+=8;
    }
    return;
}

unsigned long long ToBitBoardConverter(int r,int f)//r:0 -> 7 , f:A -> H
{
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

void Board::ApplyMove(Move * m, char promotion)
{
    int ePTSF = enPassent->file;
    int ePTSR = enPassent->rank;
    enPassent->file = None;
    enPassent->rank = -1;           
    string type = board0x88[m->CurrPos]->GetType();
    if(type == "king")
    {
        castleKSide[turn]= false;
        castleQSide[turn]= false;
        int rookbb [2] = {WhiteRooks,BlackRooks};
        if (((m->NextPos%16) - (m->CurrPos%16))>1)
        {
            //cout<<"\nking is castling king side\n";
            board0x88[m->NextPos-1]=board0x88[m->CurrPos+3];
            board0x88[m->CurrPos+3]=0;
            bitBoards[rookbb[turn]]=
                    (bitBoards[rookbb[turn]]
                    &~ToBitBoardConverter((m->CurrPos+3)/16,(m->CurrPos+3)%16))
                    |ToBitBoardConverter((m->NextPos-1)/16,(m->NextPos-1)%16);
        }
        else if (((m->CurrPos%16)-(m->NextPos%16))>1)
        {
            //cout<<"\nking is castling queen side\n";
            board0x88[m->NextPos+1]=board0x88[m->CurrPos-4];
            board0x88[m->CurrPos-4]=0;
            bitBoards[rookbb[turn]]=
                    (bitBoards[rookbb[turn]]
                    &~ToBitBoardConverter((m->CurrPos-4)/16,(m->CurrPos-4)%16))
                    |ToBitBoardConverter((m->NextPos+1)/16,(m->NextPos+1)%16);
        }
    }
    else if (type == "pawn")
    {
        int promRank[2]={7,0};
        int diff [2] = {-1,1}; 
        int pawnbb[2] = {WhitePawns,BlackPawns};
        if(abs((m->CurrPos/16)-(m->NextPos/16))>1)
        {
            enPassent->file=static_cast<File>(m->NextPos%16);
            enPassent->rank=(m->NextPos/16)+diff[turn];
        }
        else if (ePTSF != None&&((m->NextPos)==(ePTSR*16+ePTSF)))
        {                  
                board0x88[((ePTSR+diff[turn])*16+ePTSF)]=0;
                bitBoards[pawnbb[1-turn]]
                        &= (~ToBitBoardConverter(ePTSR+diff[turn],ePTSF));               
        }
        else if(m->NextPos/16==promRank[turn])
        {
            switch(promotion){               
                case 'q':
                    if(this->turn==White)
                        board0x88[m->NextPos]=this->WhiteQueenObj;  
                    else
                        board0x88[m->NextPos]=this->BlackQueenObj;
                    break;
                case 'n':
                    if(this->turn==White)
                        board0x88[m->NextPos]=this->WhiteKnightObj;
                    else
                        board0x88[m->NextPos]=this->BlackKnightObj;
                    break;
                case 'r':
                    if(this->turn==White)
                        board0x88[m->NextPos]=this->WhiteRookObj;
                    else
                        board0x88[m->NextPos]=this->BlackRookObj;
                    break;
                case 'b':
                    if(this->turn==White)
                        board0x88[m->NextPos]=this->WhiteBishopObj;
                    else
                        board0x88[m->NextPos]=this->BlackBishopObj;
                    break;                   
            }
            bitBoards[board0x88[m->NextPos]->GetPieceType()] 
                    |=ToBitBoardConverter((m->NextPos)/16,(m->NextPos)%16);
            bitBoards[pawnbb[turn]]&=(~ToBitBoardConverter((m->CurrPos)/16,(m->CurrPos)%16));
            board0x88[m->CurrPos]=0;
            bitBoards[WhitePieces]=
                    bitBoards[WhiteKing]|bitBoards[WhiteQueen]
                    |bitBoards[WhiteRooks]|bitBoards[WhiteBishops]
                    |bitBoards[WhiteKnights]|bitBoards[WhitePawns];
            bitBoards[BlackPieces]=
                    bitBoards[BlackPieces]|bitBoards[BlackPieces]
                    |bitBoards[BlackPieces]|bitBoards[BlackPieces]
                    |bitBoards[BlackPieces]|bitBoards[BlackPieces];
            turn=static_cast<Color>(1-turn);
            return;
        }
    }
    else if(type == "rook")
    {
        if(static_cast <File>(m->CurrPos%16)==h)
            castleKSide[turn]=false;
        else if (static_cast <File>(m->CurrPos%16)==a)
            castleQSide[turn]=false;
    }

    PieceType pt;
    if(board0x88[m->NextPos]!=0)
    {
        pt= board0x88[m->NextPos]->GetPieceType();
        bitBoards[pt] &=(~ToBitBoardConverter((m->NextPos)/16,(m->NextPos)%16));               
    }
    pt = board0x88[m->CurrPos]->GetPieceType();
    bitBoards[pt] |=ToBitBoardConverter((m->NextPos)/16,(m->NextPos)%16);
    bitBoards[pt] &=(~ToBitBoardConverter((m->CurrPos)/16,(m->CurrPos)%16));
    board0x88[m->NextPos]=board0x88[m->CurrPos];
    board0x88[m->CurrPos]=0;
    bitBoards[WhitePieces]=
            bitBoards[WhiteKing]|bitBoards[WhiteQueen]
            |bitBoards[WhiteRooks]|bitBoards[WhiteBishops]
            |bitBoards[WhiteKnights]|bitBoards[WhitePawns];
    bitBoards[BlackPieces]=
            bitBoards[BlackPieces]|bitBoards[BlackPieces]
            |bitBoards[BlackPieces]|bitBoards[BlackPieces]
            |bitBoards[BlackPieces]|bitBoards[BlackPieces];
    turn=static_cast<Color>(1-turn);
}

double Board::heuristic(bool &whiteKing, bool &blackKing){
	int pw = 0;
	int nw = 0; 
	int bw = 0;
	int rw = 0;
	int qw = 0;
	int kw = 0;
	int pb = 0;
	int nb = 0;
	int bb = 0;
	int rb = 0;
	int qb = 0;
	int kb = 0;
        blackKing=false;
        whiteKing=false;

	for (int i = 0; i < 128; i++){
		if (dynamic_cast<King*>(board0x88[i]) != nullptr && board0x88[i]->color == White){
			//cout << "Found White King\n";
                    whiteKing=true;
                    kw++;
		}
		else if (dynamic_cast<Queen*>(board0x88[i]) != nullptr && board0x88[i]->color == White){
			//cout << "Found White Queen\n";
			qw++;
		}
		else if (dynamic_cast<Rook*>(board0x88[i]) != nullptr && board0x88[i]->color == White){
			//cout << "Found White Rook\n";
			rw++;
		}
		else if (dynamic_cast<Bishop*>(board0x88[i]) != nullptr && board0x88[i]->color == White){
			//cout << "Found White Bishop\n";
			bw++;
		}
		else if (dynamic_cast<Knight*>(board0x88[i]) != nullptr && board0x88[i]->color == White){
			//cout << "Found White Knight\n";
			nw++;
		}
		else if (dynamic_cast<Pawn*>(board0x88[i]) != nullptr && board0x88[i]->color == White){
			//cout << "Found White Pawn\n";
			pw++;
		}
		else if (dynamic_cast<King*>(board0x88[i]) != nullptr && board0x88[i]->color == Black){
			//cout << "Found Black King\n";
                    blackKing=true;
                    kb++;
		}
		else if (dynamic_cast<Queen*>(board0x88[i]) != nullptr && board0x88[i]->color == Black){
			//cout << "Found Black Queen\n";
			qb++;
		}
		else if (dynamic_cast<Rook*>(board0x88[i]) != nullptr && board0x88[i]->color == Black){
			//cout << "Found Black Rook\n";
			rb++;
		}
		else if (dynamic_cast<Bishop*>(board0x88[i]) != nullptr && board0x88[i]->color == Black){
			//cout << "Found Black Bishop\n";
			bb++;
		}
		else if (dynamic_cast<Knight*>(board0x88[i]) != nullptr && board0x88[i]->color == Black){
			//cout << "Found Black Knight\n";
			nb++;
		}
		else if (dynamic_cast<Pawn*>(board0x88[i]) != nullptr && board0x88[i]->color == Black){
			//cout << "Found Black Pawn\n";
			pb++;
		}
	}
   
		double heu = 200 * 10000 * (kw - kb) + 9 * 1000 * (qw - qb) + 5 * 525 * (rw - rb) 
                    + 3 * 350 * (nw - nb + bw - bb) + 100 * (pw - pb);

		//cout << heu << endl ;	//Check The Function
		return heu;
}
