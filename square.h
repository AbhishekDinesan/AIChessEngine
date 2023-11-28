

#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "AbstractObserver.h"
#include "AbstractPiece.h"
#include <vector> 

 
//NOTE: Square is not an observer, it will be observed though
//      (by textdisplay, graphicsdisplay)

class Square {
    int x;
    int y;
    bool occupied; 
    std::vector<Observer *> observers; 
    
    Piece *occupiedBy;  

public:

    Square();
    ~Square();

    int getX();
    int getY();
    bool getOccupied(); 
    Piece *getOccupyingPc();

    void notifyObservers(); 
    void attach(Observer *o); 
};

#endif
