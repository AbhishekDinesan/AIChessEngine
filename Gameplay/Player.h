#include "AbstractPlayer.h"
#include "Board.h"
#include "Move.h"

class Player : public AbstractPlayer
{
public:
    Player(bool isWhite, bool isHuman, bool isInCheck, Board *myboard);
    void makeMove(int startFile, int startRank, int endFile, int endRank)
        override;
    virtual void setBoard(Board* b) override;
    bool getIsHuman() override;
    bool getColour() override;
    ~Player() = default;
};
