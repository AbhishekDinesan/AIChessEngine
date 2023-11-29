#include "AbstractPlayer.h"
#include "Move.h"

class Player : public AbstractPlayer
{
public:
    void makeMove(Move &m) = 0;
    ~Player() = default;
};
