#include "AbstractPlayer.h"
#include "Move.h"

class Player : public AbstractPlayer
{
public:
    void makeMove(int startFile, int startRank, int endFile, int endRank)
        override = 0;
    ~Player() = default;
};
