#include "Move.h"
#include "NonePiece.h"
#include "BishopPiece.h"
#include "KingPiece.h"
#include "PawnPiece.h"
#include "QueenPiece.h"
#include "RookPiece.h"
#include "KnightPiece.h" 
#include <stdlib.h> 
#include "Game.h" 


Move::Move(Board *board, Piece *piece, coords From, coords To) :
board{board}, piece{piece}, From{From}, To{To} {
    captured = nullptr; 
    didcapture = false; 
}


//destructor for Move
Move::~Move() {}



//execute move:
bool Move::executeMove(Game *g, int x, int y, Piece *p) {
    // Create the target coordinates
    coords movingTo = {x, y};

    Board *boardptr; 

    //thisPiece represents the type of the piece that we are trying to move. 
    PieceEnum thisPiece = boardptr->getPiece(p->getX(), p->getY()); 
    int currentX = p->getX(); 
    int currentY = p->getY(); 
    Piece *pieceAtMove = boardptr->getPiecePtr(x,y);


    //********** BISHOP MOVE **********
    if(thisPiece == PieceEnum::Bishop) { 
        int deltaX = abs(currentX - x); 
        int deltaY = abs(currentY - y); 

        //bishop can only move diagonally: 
        if(deltaY != deltaX) {
            return false; 
        }

        //checking for obstructions along move path: 
        int stepX = (x > currentX) ? 1 : -1;
        int stepY = (y > currentY) ? 1 : -1;
        int checkX = currentX + stepX;
        int checkY = currentY + stepY;

        while(checkX != x || checkY != y) {
            //if there is an obstruction in path of bishop, 
            if(boardptr->getPiece(checkX, checkY) != PieceEnum::None) {
                return false; 
            }

            checkX += stepX; 
            checkY += stepY; 
        }

        //check if there is an opponent on the position that we want to move to (capture): 
        if (pieceAtMove != nullptr && pieceAtMove->getColour() != p->getColour()) {
            didcapture = true; 
            captured = pieceAtMove; 
        }
        p->setX(x);
        p->setY(y); 
        return true; 
    } 

    //********** KING MOVE **********
    if (thisPiece == PieceEnum::King) {
        int deltaX = abs(currentX - x);
        int deltaY = abs(currentY - y);

        //make sure that the king can only move one square in any direction 
        if (deltaX > 1 || deltaY > 1) {
            return false;
        }

        //check for obstructions. 
        if (pieceAtMove != nullptr) {
            // If there is a piece at the destination, check to see if it is not our own: 
            if (pieceAtMove->getColour() == p->getColour()) {
                return false; 
            } else { //capture the opponent's piece: 
                didcapture = true;
                captured = pieceAtMove;
            }
        }

        //handle Castling: ***IDK What the fuck that is*** 

        // Update the King's position
        p->setX(x);
        p->setY(y);
        return true;
    }

    //********** Pawn MOVE **********
    if(thisPiece == PieceEnum::Pawn) {
        //need to dynamically cast the superclass Piece pointer *p to a pawn:
        //otherwise we can't access subclass functions: 
        Pawn *pawnptr = dynamic_cast<Pawn *>(p); 

        int deltaX = x - currentX; 
        int deltaY = y = currentY; 

        //can move either one step forward or backward 
        int direction = p->getColour() ? 1 : -1; 

        //checking for standard move (based on colour) 
        if(deltaX == 0 && deltaY == direction) {
            //since pawn cannot capture forward: 
            if(pieceAtMove != nullptr) {
                //pawn can only capture diagonally 
                return false; 
            }
        //checking for first Move (need to cast to subclass Pawn):  
        } else if(pawnptr->isFirstMove() && deltaX == 0 && deltaY == 2 * direction) {
            //make sure the path is clear:

            //makes sure that the first move is valid: 
            if (pieceAtMove != nullptr || boardptr->getPiecePtr(currentX, currentY + direction) != nullptr) {
                return false; 
            } 
        } else if(abs(deltaX) == 1 && abs(deltaY) == direction) {
            if(pieceAtMove == nullptr || pieceAtMove->getColour() == p->getColour()) {
                //diagonal moves need to be a capture: 
                return false; 
            } else {
                didcapture = true; 
                captured = pieceAtMove; 
            }
        } else {
            //in case of invalid move (defying behaviour of pawn) 
            return false; 
        }
        p->setX(x); 
        p->setY(y); 

        //a move was succesfully carried out: 
        return true; 
    }

    //********** QUEEN MOVE **********
    if (thisPiece == PieceEnum::Queen) {
        int deltaX = abs(currentX - x);
        int deltaY = abs(currentY - y);

        //check for diagonal or straight move 
        bool isDiagonalMove = deltaX == deltaY;
        bool isStraightMove = deltaX == 0 || deltaY == 0;

        //queen can only move straight in a direction or diagonal. 
        if (!isDiagonalMove && !isStraightMove) {
            return false;  
        }

        //direction to step in: 
        int stepX = (x > currentX) ? 1 : (x < currentX) ? -1 : 0;
        int stepY = (y > currentY) ? 1 : (y < currentY) ? -1 : 0;

        //how we check for obstructions. 
        int checkX = currentX + stepX;
        int checkY = currentY + stepY;

        while (checkX != x || checkY != y) {
            if (boardptr->getPiecePtr(checkX, checkY) != nullptr) {
                return false; // Obstruction in the path
            }
            checkX += stepX;
            checkY += stepY;
        }

        //check for capture: 
        if (pieceAtMove != nullptr) {
            if (pieceAtMove->getColour() == p->getColour()) {
                return false; // Cannot capture own piece
            } else {
                didcapture = true;
                captured = pieceAtMove;
            }
        }

        //update the queen's position. 
        p->setX(x);
        p->setY(y);

        return true;
    }

    //********** ROOK MOVE **********
    if (thisPiece == PieceEnum::Rook) {
        int deltaX = currentX - x;
        int deltaY = currentY - y;

        // Rook can move either horizontally or vertically
        if ((deltaX != 0 && deltaY != 0) || (deltaX == 0 && deltaY == 0)) {
            return false; // Invalid move for a Rook
        }

        //direction: 
        int stepX = (deltaX != 0) ? (deltaX > 0 ? -1 : 1) : 0;
        int stepY = (deltaY != 0) ? (deltaY > 0 ? -1 : 1) : 0;

        //checking for obstructions using checkX, checkY 
        int checkX = currentX + stepX;
        int checkY = currentY + stepY;

        //cannot "jump" over any other pieces 
        while (checkX != x || checkY != y) {
            if (boardptr->getPiecePtr(checkX, checkY) != nullptr) {
                return false; 
            }
            checkX += stepX;
            checkY += stepY;
        }

        //seeing if there is another piece at the spot we want to move to. 
        if (pieceAtMove != nullptr) {
            //can't capture own piece. 
            if (pieceAtMove->getColour() == p->getColour()) {
                return false; 
            //if not our own piece: 
            } else {
                didcapture = true;
                captured = pieceAtMove;
            }
        }

        //succesful move: 
        p->setX(x);
        p->setY(y);

        return true;
    }

    //********** KNIGHT MOVE ********** 
    if (thisPiece == PieceEnum::Knight) {
        int deltaX = abs(currentX - x);
        int deltaY = abs(currentY - y);

        //checking for l-shaped moves: 
        if (!((deltaX == 2 && deltaY == 1) || (deltaX == 1 && deltaY == 2))) {
            return false; // Invalid move for a Knight
        }

        //NOTE: knights can jump, no need to check for obstructions 

        //did we "land" on a piece: 
        if (pieceAtMove != nullptr) {
            //cannot capture our own piece: 
            if (pieceAtMove->getColour() == p->getColour()) {
                return false; 
            } else {
                didcapture = true;
                captured = pieceAtMove;
            }
        }

        //successful move: 
        p->setX(x);
        p->setY(y);

        return true;
    }

    //********** NONE MOVE ********** 
    if(thisPiece == PieceEnum::None) {
        //impossible to move the None Piece. 
        return false; 
    }
}







