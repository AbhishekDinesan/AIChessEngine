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

Piece *Move::CapturedPiece() {
    return captured; 
}



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
            if (pieceAtMove->getColour() == p->getColour() && pieceAtMove->pieceType() != PieceEnum::None) {
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
        Pawn *pawnptr = dynamic_cast<Pawn *>(p); 
        int deltaX = toX - currentX; 
        int deltaY = toY - currentY; 
        int direction = (pawnptr->getColour() == true) ? 1 : -1; 

        // Standard one square forward move
        if(deltaX == 0 && deltaY == direction) {
            if(pieceAtMove->pieceType() != PieceEnum::None) {
                return false;  // Forward move but square is not empty
            }
        }
        // First move - two squares forward
        else if(pawnptr->isFirstMove() && deltaX == 0 && deltaY == 2 * direction) {
            // Check if the path is clear (both squares)
            if(board->getPiecePtr(currentX, currentY + direction)->pieceType() != PieceEnum::None ||
                    pieceAtMove->pieceType() != PieceEnum::None) {
                        return false;
            }
            pawnptr->firstMove = false; 
        }
        // Diagonal capture
        else if(abs(deltaX) == 1 && deltaY == direction) {
            if(pieceAtMove->pieceType() == PieceEnum::None || pieceAtMove->getColour() == pawnptr->getColour()) {
                return false;  // Either no piece to capture or trying to capture own piece
            } else {
                didcapture = true; 
                captured = pieceAtMove;
            }
        }
        else {
            return false;  // Not a valid Pawn move
        }
    }

    //********** QUEEN MOVE **********
    if (p->pieceType() == PieceEnum::Queen) {
        if(toX == currentX && toY == currentY) {
            return false; 
        }


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
            if (pieceAtMove->getColour() == p->getColour() && pieceAtMove->pieceType() != PieceEnum::None) {
                return false; // Cannot capture own piece
            } else {
                didcapture = true;
                captured = pieceAtMove;
            }
        }
        return true; 
    }

    //********** ROOK MOVE **********
    if (p->pieceType() == PieceEnum::Rook) {
        int deltaX = abs(currentX - toX);
        int deltaY = abs(currentY - toY);

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
            if (pieceAtMove->getColour() == p->getColour() && pieceAtMove->pieceType() != PieceEnum::None) {
                return false; 
            //if not our own piece: 
            } else {
                didcapture = true;
                captured = pieceAtMove;
            }
        }
        return true; 
    }

    //********** KNIGHT MOVE **********
    if (p->pieceType() == PieceEnum::Knight) {
        int deltaX = abs(currentX - toX);
        int deltaY = abs(currentY - toY);


        // Check for L-shaped move: 2 squares in one direction and 1 square in the other
        if (!((deltaX == 2 && deltaY == 1) || (deltaX == 1 && deltaY == 2))) {
            cout << "HERE" << endl;
            return false; 
        }

        // Get the piece at the destination, if any
        Piece* pieceAtMove = board->getPiecePtr(toX, toY);

        // Check if there's a piece at the destination
        if (pieceAtMove != nullptr) {
            // If there is a piece, check if it's a capture (cannot capture pieces of the same color)
            if (pieceAtMove->getColour() == p->getColour() && pieceAtMove->pieceType() != PieceEnum::None) {
                return false; // Cannot capture own piece
            } else {
                didcapture = true; 
                captured = pieceAtMove; 
            }
        }
        return true; 
    }


    //********** NONE MOVE ********** 
    if(p->pieceType() == PieceEnum::None) {
        //impossible to move the None Piece. 
        return false; 
    }

    return true;
}

bool Move::willCheck() { return false; }

bool isWithinBounds(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y <8; 
}


std::vector<Move> Move::possibleMoves(Piece *p) {
    std::vector<Move> moves;
    int currentX = p->getX();
    int currentY = p->getY();

    switch (p->pieceType()) {

        //********* PAWN POSSIBLE MOVES ************ 
        case PieceEnum::Pawn: {
            Pawn *pawnptr = dynamic_cast<Pawn *>(p);  

            //direction of moves based on colour: 
            int direction = (pawnptr->getColour() == true) ? 1 : -1; 
            //check forward move
            if (board->getPiecePtr(currentX, currentY + direction)->pieceType() == PieceEnum::None) {
                moves.push_back(Move(this->board, currentX, currentY, currentX, currentY + direction));
            }
            //check captures
            if (isWithinBounds(currentX + 1, currentY + direction) && 
                board->getPiecePtr(currentX + 1, currentY + direction)->getColour() != p->getColour()) {
                moves.push_back(Move(this->board, currentX, currentY, currentX + 1, currentY + direction));
            }
            if (isWithinBounds(currentX - 1, currentY + direction) && 
                board->getPiecePtr(currentX - 1, currentY + direction)->getColour() != p->getColour()) {
                moves.push_back(Move(this->board, currentX, currentY, currentX - 1, currentY + direction));
            }

            //moving two space in the first move for Pawns: 
            //need to check if the move is within bounds, that moving two spaces is unobstructed (Pawn can't jump), and 
            //the move is within the bounds of the board. 
            if (pawnptr->isFirstMove() && 
                    isWithinBounds(currentX, currentY + 2 * direction) && //is move within board's bounds. 
                    board->getPiecePtr(currentX, currentY + direction)->pieceType() == PieceEnum::None && //
                    board->getPiecePtr(currentX, currentY + 2 * direction)->pieceType() == PieceEnum::None) {
                    moves.push_back(Move(this->board, currentX, currentY, currentX, currentY + 2 * direction));
            }
        }

        //********* BISHOP POSSIBLE MOVES ************
        case PieceEnum::Bishop: {
            //need to check in all 4 directions. 
            //step by 2 in X direction and by 2 in Y direction: 
            for (int deltaX = -1; deltaX <= 1; deltaX += 2) {
                for (int deltaY = -1; deltaY <= 1; deltaY += 2) {
                    int checkX = currentX + deltaX;
                    int checkY = currentY + deltaY;
                    
                    //check until we are out of bounds, or blocked. 
                    while (isWithinBounds(checkX, checkY)) {
                        Piece *pieceAtSquare = board->getPiecePtr(checkX, checkY);

                        if (pieceAtSquare->pieceType() == PieceEnum::None) {
                            // Empty square - add as a possible move
                            moves.push_back(Move(this->board, currentX, currentY, checkX, checkY));
                        } else {
                            // Encounter another piece
                            if (pieceAtSquare->getColour() != p->getColour()) {
                                // Opponent's piece - can capture it
                                moves.push_back(Move(this->board, currentX, currentY, checkX, checkY));
                            }
                            //bishop cannot jump 
                            break;
                        }
                        checkX += deltaX;
                        checkY += deltaY;
                    }
                }
            }
            break;
        }
    }


    return moves;
}