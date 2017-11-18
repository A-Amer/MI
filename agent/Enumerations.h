#ifndef ENUMERATIONS_H
#define ENUMERATIONS_H

enum PieceType {
        WhiteKing,
        WhiteQueen,
        WhiteRooks,
        WhiteBishops,
        WhiteKnights,
        WhitePawns,
        BlackKing,
        BlackQueen,
        BlackRooks,
        BlackBishops,
        BlackKnights,
        BlackPawns,
        WhitePieces,
        BlackPieces,
        NoPiece = -1
};


enum Color {
        
        White,
        Black
};

enum File {
        a = 0,
        b = 1,
        c = 2,
        d = 3,
        e = 4,
        f = 5,
        g = 6,
        h = 7,
        None = -1
};
    const unsigned long long FILE_A=
     1L      |  (1L<<8) | (1L<<16) | (1L<<24) |
    (1L<<32) | (1L<<40) | (1L<<48) | (1L<<56);
    const unsigned long long FILE_B = FILE_A <<1;
    const unsigned long long FILE_H=
     0x80L      |  (0x80L<<8) | (0x80L<<16) | (0x80L<<24) |
    (0x80L<<32) | (0x80L<<40) | (0x80L<<48) | (0x80L<<56);
    const unsigned long long FILE_G = FILE_H >>1;
    
    
#endif /* ENUMERATIONS_H */

