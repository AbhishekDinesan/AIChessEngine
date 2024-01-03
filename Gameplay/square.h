#ifndef __SQUARE__
#define __SQUARE__

#include "AbstractObserver.h"
#include "../Pieces/AbstractPiece.h"
#include <vector>

// NOTE: Square is not an observer, it will be observed though
//       (by textdisplay, graphicsdisplay)

class Square
{
    int x;
    int y;
    bool occupied;
    std::vector<Observer *> observers;

    Piece *occupiedBy;

public:
    Square();
    Square(const Square &other);
    ~Square();

    int getX();
    int getY();
    void setCoords(int x, int y);
    bool getOccupied();
    Piece *getOccupyingPc();

    void notifyObservers(Square &s);
    void attach(Observer *o);
    void setPiece(Piece *piece);
};

#endif __SQUARE__
