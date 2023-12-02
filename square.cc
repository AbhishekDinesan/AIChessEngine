// square.cc
#include <iostream>
#include "square.h"
//#include "NonePiece.h"
using namespace std;


//Default constructor for square 
Square::Square() : x(0), y(0), occupied(false), occupiedBy(nullptr) {
    //None *emptyPiece = new None();
}  


//Destructor for square 
Square::~Square() {
    for(auto obs : observers) {
        delete obs; 
    }
}

//returns the X value of the square 
int Square::getX() {
    return x;
}

//returns the Y value of the square
int Square::getY() {
    return y;
}

void Square::setCoords(int x, int y) {
    this->x = x;
    this->y = y;
}

bool Square::getOccupied() {
    return occupied;
}

Piece *Square::getOccupyingPc() {
    return this->occupiedBy; 
}

//the square will notify all of the observers about a change that has happened on this
//    square. 
void Square::notifyObservers(Square &s) {
    for(Observer *obs : observers) {
        obs->notify(s);
    }
}

void Square::attach(Observer *o) {
    observers.emplace_back(o); 
}

//setPiece(piece) sets the piece to the current square, and
//    and notifies the observers of a change to the piece 
// NOTE: THIS IS NOT IN THE UML, WILL NEED TO INCLUDE IN REPORT 
void Square::setPiece(Piece *piece) {
    occupiedBy = piece; 
    notifyObservers(*this); 
}


