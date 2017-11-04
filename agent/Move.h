
#ifndef MOVE_H
#define MOVE_H

class Move {
public:
    Move(int from , int to);
    Move();
    int CurrPos;
    int NextPos;
    Move(const Move& orig);
    virtual ~Move();
private:
    
    

};

#endif /* MOVE_H */

