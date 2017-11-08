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
        BlackPieces
};


enum Color {
        
        White,
        Black
};

enum File {
        A = 0,
        B = 1,
        C = 2,
        D = 3,
        E = 4,
        F = 5,
        G = 6,
        H = 7,
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

