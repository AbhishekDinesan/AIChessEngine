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
#include "Board.h" 


Move::Move(Board *board, int fromX, int fromY, int toX, int toY) :
board{board}, fromX{fromX}, fromY{fromY}, toX{toX}, toY{toY} {
    captured = nullptr; 
    didcapture = false; 
}


//destructor for Move
Move::~Move() {}



//execute move:
bool Move::isValidMove() {
    // Create the target coordinates
    //coords movingTo = {x, y};

    
    cout << "(4)" << endl;
    Piece *p = board->getPiecePtr(fromX, fromY);
    //thisPiece represents the type of the piece that we are trying to move. 
    //Piece *thisPiece = board->getPiecePtr(p->getX(), p->getY()); 
    int currentX = p->getX(); 
    int currentY = p->getY(); 
    Piece *pieceAtMove = board->getPiecePtr(toX,toY);

    cout << "(6)" << endl;
    //********** BISHOP MOVE **********
    if(p->pieceType() == PieceEnum::Bishop) { 
        int deltaX = abs(currentX - toX); 
        int deltaY = abs(currentY - toY); 

        //bishop can only move diagonally: 
        if(deltaY != deltaX) {
            return false; 
        }

        //checking for obstructions along move path: 
        int stepX = (toX > currentX) ? 1 : -1;
        int stepY = (toY > currentY) ? 1 : -1;
        int checkX = currentX + stepX;
        int checkY = currentY + stepY;

        while(checkX != toX || checkY != toY) {
            //if there is an obstruction in path of bishop, 
            if(board->getPiecePtr(checkX, checkY)->pieceType() != PieceEnum::None) {
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
    } 

    //********** KING MOVE **********
    if (p->pieceType() == PieceEnum::King) {
        int deltaX = abs(currentX - toX);
        int deltaY = abs(currentY - toY);

        //make sure that the king can only move one square in any direction 
        if (deltaX > 1 || deltaY > 1) {
            return false;
        }

        //check for obstructions. 
        if (pieceAtMove->pieceType() != PieceEnum::None) {
            // If there is a piece at the destination, check to see if it is not our own: 
            if (pieceAtMove->getColour() == p->getColour()) {
                return false; 
            } else { //capture the opponent's piece: 
                didcapture = true;
                captured = pieceAtMove;
            }
        }

        //handle Castling: ***IDK What the fuck that is*** 
        // Anthony's Edit: LOL
    }

    //********** Pawn MOVE **********
    if(p->pieceType() == PieceEnum::Pawn) {
        //need to dynamically cast the superclass Piece pointer *p to a pawn:
        //otherwise we can't access subclass functions: 
        Pawn *pawnptr = dynamic_cast<Pawn *>(p); 
        cout << "(7)" << endl;

        int deltaX = toX - currentX; 
        int deltaY = toY - currentY; 

        //can move either one step forward or backward 
        int direction = p->getColour() ? 1 : -1; 

        //checking for standard move (based on colour) 
        if(deltaX == 0 && deltaY == direction) {
            //since pawn cannot capture forward: 
            if(pieceAtMove->pieceType() != PieceEnum::None) {
                //pawn can only capture diagonally 
                return false; 
            }
        //checking for first Move (need to cast to subclass Pawn):  
        } else if(pawnptr->isFirstMove() && deltaX == 0 && (deltaY == 2 * direction || deltaY == direction)) {
            //make sure the path is clear:

            //makes sure that the first move is valid: 
            if (pieceAtMove->pieceType() != PieceEnum::None) {
                return false; 
            } 

            // Checks to see if there is a peice obstructing a double move
            if (deltaY == 2 * direction && board->getPiecePtr(currentX, currentY + deltaY)->pieceType() == PieceEnum::None) {
                return false;
            }
            
        } else if(abs(deltaX) == 1 && abs(deltaY) == direction) {
            if(pieceAtMove->pieceType() == PieceEnum::None || pieceAtMove->getColour() == p->getColour()) {
                //diagonal moves need to be a capture: 
                return false; 
            } else {
                didcapture = true; 
                captured = pieceAtMove; 
            }
        } else {
            //in case of invalid move (defying behaviour of pawn) 
            return true; 
        }
    }

    //********** QUEEN MOVE **********
    if (p->pieceType() == PieceEnum::Queen) {
        int deltaX = abs(currentX - toX);
        int deltaY = abs(currentY - toY);

        //check for diagonal or straight move 
        bool isDiagonalMove = deltaX == deltaY;
        bool isStraightMove = deltaX == 0 || deltaY == 0;

        //queen can only move straight in a direction or diagonal. 
        if (!isDiagonalMove && !isStraightMove) {
            return false;  
        }

        //direction to step in: 
        int stepX = (toX > currentX) ? 1 : (toX < currentX) ? -1 : 0;
        int stepY = (toY > currentY) ? 1 : (toY < currentY) ? -1 : 0;

        //how we check for obstructions. 
        int checkX = currentX + stepX;
        int checkY = currentY + stepY;

        while (checkX != toX || checkY != toY) {
            if (board->getPiecePtr(checkX, checkY) != nullptr) {
                return false; // Obstruction in the path
            }
            checkX += stepX;
            checkY += stepY;
        }

        //check for capture: 
        if (pieceAtMove->pieceType() != PieceEnum::None) {
            if (pieceAtMove->getColour() == p->getColour()) {
                return false; // Cannot capture own piece
            } else {
                didcapture = true;
                captured = pieceAtMove;
            }
        }
    }

    //********** ROOK MOVE **********
    if (p->pieceType() == PieceEnum::Rook) {
        int deltaX = currentX - toX;
        int deltaY = currentY - toY;

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
        while (checkX != toX || checkY != toY) {
            if (board->getPiecePtr(checkX, checkY) != nullptr) {
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
    }

    //********** KNIGHT MOVE ********** 
    if (p->pieceType() == PieceEnum::Knight) {
        int deltaX = abs(currentX - toX);
        int deltaY = abs(currentY - toY);

        //checking for l-shaped moves: 
        if (!(deltaX == 2 && deltaY == 1) || !(deltaX == 1 && deltaY == 2)) {
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
    }

    //********** NONE MOVE ********** 
    if(p->pieceType() == PieceEnum::None) {
        //impossible to move the None Piece. 
        return false; 
    }

    return true;
}

bool Move::willCheck() { return false; }