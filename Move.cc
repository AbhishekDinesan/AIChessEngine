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

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
// WE MUST CHANGE ALL INSTANCES OF None TO NonePc FOR GRAPHICS TO WORK
//  ALSO CHANGE ALL nullptr to PieceEnum::NonePc MOVE LOGIC WAS MESSED UP A BIT
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

Move::Move(Board *board, int fromX, int fromY, int toX, int toY) : board{board}, fromX{fromX}, fromY{fromY}, toX{toX}, toY{toY}
{
    captured = nullptr;
    didcapture = false;
}

// destructor for Move
Move::~Move() {}

Piece *Move::CapturedPiece()
{
    return captured;
}

bool Move::willCapture()
{
    return didcapture;
}

// execute move:
bool Move::isValidMove()
{
    // Create the target coordinates
    // coords movingTo = {x, y};

    Piece *p = board->getPiecePtr(fromX, fromY);
    if (p->getColour() == board->isWhiteTurn)
    {
        board->isWhiteTurn = !board->isWhiteTurn;
        return false;
    }
    // thisPiece represents the type of the piece that we are trying to move.
    // Piece *thisPiece = board->getPiecePtr(p->getX(), p->getY());
    int currentX = p->getX();
    int currentY = p->getY();
    Piece *pieceAtMove = board->getPiecePtr(toX, toY);

    //********** BISHOP MOVE **********
    if (p->pieceType() == PieceEnum::Bishop)
    {
        int deltaX = abs(currentX - toX);
        int deltaY = abs(currentY - toY);

        // bishop can only move diagonally:
        if (deltaY != deltaX)
        {
            return false;
        }

        // checking for obstructions along move path:
        int stepX = (toX > currentX) ? 1 : -1;
        int stepY = (toY > currentY) ? 1 : -1;
        int checkX = currentX + stepX;
        int checkY = currentY + stepY;

        while (checkX != toX || checkY != toY)
        {
            // if there is an obstruction in path of bishop,
            if (board->getPiecePtr(checkX, checkY)->pieceType() != PieceEnum::None)
            {
                return false;
            }
            checkX += stepX;
            checkY += stepY;
        }

        // check if there is an opponent on the position that we want to move to (capture):
        if (pieceAtMove->pieceType() != PieceEnum::None && pieceAtMove->getColour() != p->getColour())
        {
            didcapture = true;
            captured = pieceAtMove;
        }
    }

    //********** KING MOVE **********
    if (p->pieceType() == PieceEnum::King)
    {
        int deltaX = abs(currentX - toX);
        int deltaY = abs(currentY - toY);

        // make sure that the king can only move one square in any direction
        if (deltaX > 1 || deltaY > 1)
        {
            return false;
        }

        // check for obstructions.
        if (pieceAtMove->pieceType() != PieceEnum::None)
        {
            // If there is a piece at the destination, check to see if it is not our own:
            if (pieceAtMove->getColour() == p->getColour() && pieceAtMove->pieceType() != PieceEnum::None)
            {
                return false;
            }
            else
            { // capture the opponent's piece:
                didcapture = true;
                captured = pieceAtMove;
            }
        }

        // handle Castling: ***IDK What the fuck that is***
        //  Anthony's Edit: LOL
    }

    //********** Pawn MOVE **********
    if (p->pieceType() == PieceEnum::Pawn)
    {
        Pawn *pawnptr = dynamic_cast<Pawn *>(p);
        int deltaX = toX - currentX;
        int deltaY = toY - currentY;
        int direction = (pawnptr->getColour() != true) ? 1 : -1;

        // Standard one square forward move
        if (deltaX == 0 && deltaY == direction)
        {
            if (pieceAtMove->pieceType() != PieceEnum::None)
            {
                return false; // Forward move but square is not empty
            }
        }
        // First move - two squares forward
        else if (pawnptr->isFirstMove() && deltaX == 0 && deltaY == 2 * direction)
        {
            // Check if the path is clear (both squares)
            if (board->getPiecePtr(currentX, currentY + direction)->pieceType() != PieceEnum::None ||
                pieceAtMove->pieceType() != PieceEnum::None)
            {
                return false;
            }
            pawnptr->setFirstMove(false);
        }
        // Diagonal capture
        else if (abs(deltaX) == 1 && deltaY == direction)
        {
            if (pieceAtMove->pieceType() == PieceEnum::None || pieceAtMove->getColour() == pawnptr->getColour())
            {
                return false; // Either no piece to capture or trying to capture own piece
            }
            else
            {
                didcapture = true;
                captured = pieceAtMove;
            }
        }
        else
        {
            return false; // Not a valid Pawn move
        }
    }

    //********** QUEEN MOVE **********
    if (p->pieceType() == PieceEnum::Queen)
    {
        if (toX == currentX && toY == currentY)
        {
            return false;
        }

        int deltaX = abs(currentX - toX);
        int deltaY = abs(currentY - toY);

        // check for diagonal or straight move
        bool isDiagonalMove = deltaX == deltaY;
        bool isStraightMove = deltaX == 0 || deltaY == 0;

        // queen can only move straight in a direction or diagonal.
        if (!isDiagonalMove && !isStraightMove)
        {
            return false;
        }

        // direction to step in:
        int stepX = (toX > currentX) ? 1 : (toX < currentX) ? -1
                                                            : 0;
        int stepY = (toY > currentY) ? 1 : (toY < currentY) ? -1
                                                            : 0;

        // how we check for obstructions.
        int checkX = currentX + stepX;
        int checkY = currentY + stepY;

        while (checkX != toX || checkY != toY)
        {
            if (board->getPiecePtr(checkX, checkY)->pieceType() != PieceEnum::None)
            {
                return false; // Obstruction in the path
            }
            checkX += stepX;
            checkY += stepY;
        }

        // check for capture:
        if (pieceAtMove->pieceType() != PieceEnum::None)
        {
            if (pieceAtMove->getColour() == p->getColour() && pieceAtMove->pieceType() != PieceEnum::None)
            {
                return false; // Cannot capture own piece
            }
            else
            {
                didcapture = true;
                captured = pieceAtMove;
            }
        }
        return true;
    }

    //********** ROOK MOVE **********
    if (p->pieceType() == PieceEnum::Rook)
    {
        int deltaX = abs(currentX - toX);
        int deltaY = abs(currentY - toY);

        // Rook can move either horizontally or vertically
        if ((deltaX != 0 && deltaY != 0) || (deltaX == 0 && deltaY == 0))
        {
            return false; // Invalid move for a Rook
        }

        // direction:
        int stepX = (deltaX != 0) ? (deltaX > 0 ? -1 : 1) : 0;
        int stepY = (deltaY != 0) ? (deltaY > 0 ? -1 : 1) : 0;

        // checking for obstructions using checkX, checkY
        int checkX = currentX + stepX;
        int checkY = currentY + stepY;

        // cannot "jump" over any other pieces
        while (checkX != toX || checkY != toY)
        {
            if (board->getPiecePtr(checkX, checkY)->pieceType() != PieceEnum::None)
            {
                return false;
            }
            checkX += stepX;
            checkY += stepY;
        }

        // seeing if there is another piece at the spot we want to move to.
        if (pieceAtMove->pieceType() != PieceEnum::None)
        {
            // can't capture own piece.
            if (pieceAtMove->getColour() == p->getColour() && pieceAtMove->pieceType() != PieceEnum::None)
            {
                return false;
                // if not our own piece:
            }
            else
            {
                didcapture = true;
                captured = pieceAtMove;
            }
        }
        return true;
    }

    //********** KNIGHT MOVE **********
    if (p->pieceType() == PieceEnum::Knight)
    {
        int deltaX = abs(currentX - toX);
        int deltaY = abs(currentY - toY);

        // Check for L-shaped move: 2 squares in one direction and 1 square in the other
        if (!((deltaX == 2 && deltaY == 1) || (deltaX == 1 && deltaY == 2)))
        {
            return false;
        }

        // Get the piece at the destination, if any
        Piece *pieceAtMove = board->getPiecePtr(toX, toY);

        // Check if there's a piece at the destination
        if (pieceAtMove->pieceType() != PieceEnum::None)
        {
            // If there is a piece, check if it's a capture (cannot capture pieces of the same color)
            if (pieceAtMove->getColour() == p->getColour() && pieceAtMove->pieceType() != PieceEnum::None)
            {
                return false; // Cannot capture own piece
            }
            else
            {
                didcapture = true;
                captured = pieceAtMove;
            }
        }
        return true;
    }

    //********** NONE MOVE **********
    if (p->pieceType() == PieceEnum::None)
    {
        // impossible to move the None Piece.
        return false;
    }

    return true;
}

bool Move::willCheck() { return false; }

bool isWithinBounds(int x, int y)
{
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

std::vector<Move> Move::possibleMoves(Piece *p)
{
    std::vector<Move> moves;

    int currentX = p->getX();
    int currentY = p->getY();

    switch (p->pieceType())
    {

    //********* PAWN POSSIBLE MOVES ************
    case PieceEnum::Pawn:
    {
        // need to dynamically cast to a Pawn to access pawn methods:
        Pawn *pawnptr = dynamic_cast<Pawn *>(p);

        // Direction of moves based on colour:
        int direction = (pawnptr->getColour() != true) ? 1 : -1;

        // Forward move (one square)
        // checks for: within bounds, no obsturctions,
        if (isWithinBounds(currentX, currentY + direction) &&
            board->getPiecePtr(currentX, currentY + direction)->pieceType() == PieceEnum::None)
        {
            moves.push_back(Move(this->board, currentX, currentY, currentX, currentY + direction));
        }

        // Forward move (two squares)
        // checkes for first move, no obstructions,
        if (isWithinBounds(currentX, currentY + direction * 2) && pawnptr->isFirstMove() &&
            board->getPiecePtr(currentX, currentY + direction)->pieceType() == PieceEnum::None &&
            board->getPiecePtr(currentX, currentY + direction * 2)->pieceType() == PieceEnum::None)
        {
            moves.push_back(Move(this->board, currentX, currentY, currentX, currentY + direction * 2));
        }

        // Capture to the right (from the pawn's perspective)
        // checks for: move within bounds, piece at diagonal is opponent.
        if (isWithinBounds(currentX + 1, currentY + direction) && pawnptr->isFirstMove() &&
            board->getPiecePtr(currentX + 1, currentY + direction)->getColour() != pawnptr->getColour() && board->getPiecePtr(currentX + 1, currentY + direction)->pieceType() != PieceEnum::None)
        {
            Move newmove = Move(this->board, currentX, currentY, currentX + 1, currentY + direction);
            newmove.didcapture = true;
            moves.push_back(newmove);
        }

        // capture to the left (from pawn's perspective):
        // checks for: move within bounds, piece at diagonal is opponent.
        if (isWithinBounds(currentX - 1, currentY + direction) &&
            board->getPiecePtr(currentX - 1, currentY + direction)->getColour() != pawnptr->getColour() && board->getPiecePtr(currentX - 1, currentY + direction)->pieceType() != PieceEnum::None)
        {
            Move newmove = Move(this->board, currentX, currentY, currentX - 1, currentY + direction);
            newmove.didcapture = true;
            moves.push_back(newmove);
        }

        // check for: en passant.
        return moves;
    }
    break;

    //********* BISHOP POSSIBLE MOVES ************
    case PieceEnum::Bishop:
    {
        // Iterate to the top-left direction
        for (int i = 1; i <= std::min(currentX, currentY); ++i)
        {
            int x = currentX - i;
            int y = currentY - i;

            // Check for no obstructions
            if (board->getPiecePtr(x, y)->pieceType() != PieceEnum::None)
            {
                // If it's an opponent's piece, add as a capture move
                if (board->getPiecePtr(x, y)->getColour() != p->getColour() &&
                    board->getPiecePtr(x, y)->pieceType() != PieceEnum::None)
                {
                    Move capturemove = Move(this->board, currentX, currentY, x, y);
                    capturemove.didcapture = true;
                    moves.push_back(capturemove);
                }
                // Bishop cannot jump over pieces, so break the loop
                break;
            }

            // If the diagonal square is empty, add as a potential move
            moves.push_back(Move(this->board, currentX, currentY, x, y));
        }

        // Iterate to the top-right direction
        for (int i = 1; currentX + i < 8 && currentY - i >= 0; ++i)
        {
            int x = currentX + i;
            int y = currentY - i;

            if (board->getPiecePtr(x, y)->pieceType() != PieceEnum::None)
            {
                if (board->getPiecePtr(x, y)->getColour() != p->getColour() &&
                    board->getPiecePtr(x, y)->pieceType() != PieceEnum::None)
                {
                    Move capturemove = Move(this->board, currentX, currentY, x, y);
                    capturemove.didcapture = true;
                    moves.push_back(capturemove);
                }
                break;
            }

            moves.push_back(Move(this->board, currentX, currentY, x, y));
        }

        // iterate to the bottom-left direction:
        for (int i = 1; currentX - i >= 0 && currentY + i < 8; ++i)
        {
            int x = currentX - i;
            int y = currentY + i;

            if (board->getPiecePtr(x, y)->pieceType() != PieceEnum::None)
            {
                if (board->getPiecePtr(x, y)->getColour() != p->getColour() &&
                    board->getPiecePtr(x, y)->pieceType() != PieceEnum::None)
                {
                    Move capturemove = Move(this->board, currentX, currentY, x, y);
                    capturemove.didcapture = true;
                    moves.push_back(capturemove);
                }
                break;
            }

            moves.push_back(Move(this->board, currentX, currentY, x, y));
        }

        // iterate to the bottom-left direction
        for (int i = 1; currentX + i < 8 && currentY + i < 8; ++i)
        {
            int x = currentX + i;
            int y = currentY + i;

            if (board->getPiecePtr(x, y)->pieceType() != PieceEnum::None)
            {
                if (board->getPiecePtr(x, y)->getColour() != p->getColour() &&
                    board->getPiecePtr(x, y)->pieceType() != PieceEnum::None)
                {
                    Move capturemove = Move(this->board, currentX, currentY, x, y);
                    capturemove.didcapture = true;
                    moves.push_back(capturemove);
                }
                break;
            }
            moves.push_back(Move(this->board, currentX, currentY, x, y));
        }
        return moves;
    }
    break;

    //********* QUEEN POSSIBLE MOVES ************
    case PieceEnum::Queen:
    {
        // Iterate to the top-left direction
        for (int i = 1; i <= std::min(currentX, currentY); ++i)
        {
            int x = currentX - i;
            int y = currentY - i;

            // Check for no obstructions
            if (board->getPiecePtr(x, y)->pieceType() != PieceEnum::None)
            {
                // If it's an opponent's piece, add as a capture move
                if (board->getPiecePtr(x, y)->getColour() != p->getColour() &&
                    board->getPiecePtr(x, y)->pieceType() != PieceEnum::None)
                {
                    Move capturemove = Move(this->board, currentX, currentY, x, y);
                    capturemove.didcapture = true;
                    moves.push_back(capturemove);
                }
                // Bishop cannot jump over pieces, so break the loop
                break;
            }

            // If the diagonal square is empty, add as a potential move
            moves.push_back(Move(this->board, currentX, currentY, x, y));
        }

        // Iterate to the top-right direction
        for (int i = 1; currentX + i < 8 && currentY - i >= 0; ++i)
        {
            int x = currentX + i;
            int y = currentY - i;

            if (board->getPiecePtr(x, y)->pieceType() != PieceEnum::None)
            {
                if (board->getPiecePtr(x, y)->getColour() != p->getColour() &&
                    board->getPiecePtr(x, y)->pieceType() != PieceEnum::None)
                {
                    Move capturemove = Move(this->board, currentX, currentY, x, y);
                    capturemove.didcapture = true;
                    moves.push_back(capturemove);
                }
                break;
            }

            moves.push_back(Move(this->board, currentX, currentY, x, y));
        }

        // iterate to the bottom-left direction:
        for (int i = 1; currentX - i >= 0 && currentY + i < 8; ++i)
        {
            int x = currentX - i;
            int y = currentY + i;

            if (board->getPiecePtr(x, y)->pieceType() != PieceEnum::None)
            {
                if (board->getPiecePtr(x, y)->getColour() != p->getColour() &&
                    board->getPiecePtr(x, y)->pieceType() != PieceEnum::None)
                {
                    Move capturemove = Move(this->board, currentX, currentY, x, y);
                    capturemove.didcapture = true;
                    moves.push_back(capturemove);
                }
                break;
            }

            moves.push_back(Move(this->board, currentX, currentY, x, y));
        }

        // iterate to the bottom-left direction
        for (int i = 1; currentX + i < 8 && currentY + i < 8; ++i)
        {
            int x = currentX + i;
            int y = currentY + i;

            if (board->getPiecePtr(x, y)->pieceType() != PieceEnum::None)
            {
                if (board->getPiecePtr(x, y)->getColour() != p->getColour() &&
                    board->getPiecePtr(x, y)->pieceType() != PieceEnum::None)
                {
                    Move capturemove = Move(this->board, currentX, currentY, x, y);
                    capturemove.didcapture = true;
                    moves.push_back(capturemove);
                }
                break;
            }
            moves.push_back(Move(this->board, currentX, currentY, x, y));
        }

        // check horizontally to the right:
        for (int x = currentX + 1; x < 8; x++)
        {
            // Is there a piece in the way? We can capture this piece.
            if (board->getPiecePtr(x, currentY)->pieceType() != PieceEnum::None)
            {
                if (board->getPiecePtr(x, currentY)->pieceType() != PieceEnum::None && board->getPiecePtr(x, currentY)->getColour() != p->getColour())
                {
                    Move capturemove = Move(this->board, currentX, currentY, x, currentY);
                    moves.push_back(capturemove);
                }
                break;
                // normal move:
            }
            else
            {
                moves.push_back(Move(this->board, currentX, currentY, x, currentY));
            }
        }

        // check horizontally to the left:
        for (int x = currentX - 1; x >= 0; x--)
        {
            // Is there a piece in the way? We can capture this piece.
            if (board->getPiecePtr(x, currentY)->pieceType() != PieceEnum::None)
            {
                if (board->getPiecePtr(x, currentY)->pieceType() != PieceEnum::None && board->getPiecePtr(x, currentY)->getColour() != p->getColour())
                {
                    Move capturemove = Move(this->board, currentX, currentY, x, currentY);
                    moves.push_back(capturemove);
                }
                break;
                // normal move:
            }
            else
            {
                moves.push_back(Move(this->board, currentX, currentY, x, currentY));
            }
        }

        // check vertically down:
        for (int y = currentY - 1; y >= 0; y--)
        {
            // Is there a piece in the way? We can capture this piece.
            if (board->getPiecePtr(currentX, y)->pieceType() != PieceEnum::None)
            {
                if (board->getPiecePtr(currentX, y)->pieceType() != PieceEnum::None && board->getPiecePtr(currentX, y)->getColour() != p->getColour())
                {
                    Move capturemove = Move(this->board, currentX, currentY, currentX, y);
                    moves.push_back(capturemove);
                }
                break;
                // normal move:
            }
            else
            {
                moves.push_back(Move(this->board, currentX, currentY, currentX, y));
            }
        }

        // check vertically up:
        for (int y = currentY + 1; y < 8; y++)
        {
            // Is there a piece in the way? We can capture this piece.
            if (board->getPiecePtr(currentX, y)->pieceType() != PieceEnum::None)
            {
                if (board->getPiecePtr(currentX, y)->pieceType() != PieceEnum::None && board->getPiecePtr(currentX, y)->getColour() != p->getColour())
                {
                    Move capturemove = Move(this->board, currentX, currentY, currentX, y);
                    moves.push_back(capturemove);
                }
                break;
                // normal move:
            }
            else
            {
                moves.push_back(Move(this->board, currentX, currentY, currentX, y));
            }
        }

        return moves;
    }
    break;

    //********* ROOK POSSIBLE MOVES ************
    case PieceEnum::Rook:
    {
        // check horizontally to the right:
        for (int x = currentX + 1; x < 8; x++)
        {
            // Is there a piece in the way? We can capture this piece.
            if (board->getPiecePtr(x, currentY)->pieceType() != PieceEnum::None)
            {
                if (board->getPiecePtr(x, currentY)->pieceType() != PieceEnum::None && board->getPiecePtr(x, currentY)->getColour() != p->getColour())
                {
                    Move capturemove = Move(this->board, currentX, currentY, x, currentY);
                    moves.push_back(capturemove);
                }
                break;
                // normal move:
            }
            else if (board->getPiecePtr(x, currentY)->pieceType() == PieceEnum::None)
            {
                moves.push_back(Move(this->board, currentX, currentY, x, currentY));
            }
        }

        // check horizontally to the left:
        for (int x = currentX - 1; x >= 0; x--)
        {
            // Is there a piece in the way? We can capture this piece.
            if (board->getPiecePtr(x, currentY)->pieceType() != PieceEnum::None)
            {
                if (board->getPiecePtr(x, currentY)->pieceType() != PieceEnum::None && board->getPiecePtr(x, currentY)->getColour() != p->getColour())
                {
                    Move capturemove = Move(this->board, currentX, currentY, x, currentY);
                    moves.push_back(capturemove);
                }
                break;
                // normal move:
            }
            else if (board->getPiecePtr(x, currentY)->pieceType() == PieceEnum::None)
            {
                moves.push_back(Move(this->board, currentX, currentY, x, currentY));
            }
        }

        // check vertically down:
        for (int y = currentY - 1; y >= 0; y--)
        {
            // Is there a piece in the way? We can capture this piece.
            if (board->getPiecePtr(currentX, y)->pieceType() != PieceEnum::None)
            {
                if (board->getPiecePtr(currentX, y)->pieceType() != PieceEnum::None && board->getPiecePtr(currentX, y)->getColour() != p->getColour())
                {
                    Move capturemove = Move(this->board, currentX, currentY, currentX, y);
                    moves.push_back(capturemove);
                }
                break;
                // normal move:
            }
            else
            {
                moves.push_back(Move(this->board, currentX, currentY, currentX, y));
            }
        }

        // check vertically up:
        for (int y = currentY + 1; y < 8; y++)
        {
            // Is there a piece in the way? We can capture this piece.
            if (board->getPiecePtr(currentX, y)->pieceType() != PieceEnum::None)
            {
                if (board->getPiecePtr(currentX, y)->pieceType() != PieceEnum::None && board->getPiecePtr(currentX, y)->getColour() != p->getColour())
                {
                    Move capturemove = Move(this->board, currentX, currentY, currentX, y);
                    moves.push_back(capturemove);
                }
                break;
                // normal move:
            }
            else
            {
                moves.push_back(Move(this->board, currentX, currentY, currentX, y));
            }
        }
        return moves;
    }
    break;

    //********* KING POSSIBLE MOVES ************
    case PieceEnum::King:
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; i <= 1; i++)
            {
                if ((i != 0) || (j != 0))
                {
                    if (isWithinBounds(currentX + i, currentY + j))
                    {
                        if (board->getPiecePtr(currentX + i, currentY + j)->getColour() != p->getColour() &&
                            board->getPiecePtr(currentX + i, currentY + j)->pieceType() != PieceEnum::None)
                        {
                            // capture:
                            Move capturemove = Move(this->board, currentX, currentY, currentX + i, currentY + j);
                            capturemove.didcapture = true;
                            moves.push_back(capturemove);
                        }
                        else if (board->getPiecePtr(currentX + i, currentY + j)->pieceType() == PieceEnum::None)
                        {
                            // no capture:
                            moves.push_back(Move(this->board, currentX, currentY, currentX + i, currentY + j));
                        }
                    }
                }
            }
        }
        // moving up:
        // check for: within bounds, and capture,
        /*if (isWithinBounds(currentX, currentY + 1))
        {
            if (board->getPiecePtr(currentX, currentY + 1)->getColour() != p->getColour() &&
                board->getPiecePtr(currentX, currentY + 1)->pieceType() != PieceEnum::None)
            {
                // capture:
                Move capturemove = Move(this->board, currentX, currentY, currentX, currentY + 1);
                capturemove.didcapture = true;
                moves.push_back(capturemove);
            }
            else if (board->getPiecePtr(currentX, currentY + 1)->pieceType() == PieceEnum::None)
            {
                // no capture:
                moves.push_back(Move(this->board, currentX, currentY, currentX, currentY + 1));
            }
        }

        // moving down:
        // check for: within bounds, and capture:
        if (isWithinBounds(currentX, currentY - 1))
        {
            if (board->getPiecePtr(currentX, currentY - 1)->getColour() != p->getColour() &&
                board->getPiecePtr(currentX, currentY - 1)->pieceType() != PieceEnum::None)
            {
                // capture:
                Move capturemove = Move(this->board, currentX, currentY, currentX, currentY - 1);
                capturemove.didcapture = true;
                moves.push_back(capturemove);
            }
            else if (board->getPiecePtr(currentX, currentY - 1)->pieceType() == PieceEnum::None)
            {
                // no capture:
                moves.push_back(Move(this->board, currentX, currentY, currentX, currentY - 1));
            }
        }

        // moving right:
        // check for: within bounds, and capture:
        if (isWithinBounds(currentX + 1, currentY))
        {
            if (board->getPiecePtr(currentX + 1, currentY)->getColour() != p->getColour() &&
                board->getPiecePtr(currentX + 1, currentY)->pieceType() != PieceEnum::None)
            {
                // capture:
                Move capturemove = Move(this->board, currentX, currentY, currentX + 1, currentY);
                capturemove.didcapture = true;
                moves.push_back(capturemove);
            }
            else if (board->getPiecePtr(currentX + 1, currentY)->pieceType() == PieceEnum::None)
            {
                // no capture:
                moves.push_back(Move(this->board, currentX, currentY, currentX + 1, currentY));
            }
        }

        // moving left:
        // check for: within bounds, and capture:
        if (isWithinBounds(currentX - 1, currentY))
        {
            if (board->getPiecePtr(currentX - 1, currentY)->getColour() != p->getColour() &&
                board->getPiecePtr(currentX - 1, currentY)->pieceType() != PieceEnum::None)
            {
                // capture:
                Move capturemove = Move(this->board, currentX, currentY, currentX - 1, currentY);
                capturemove.didcapture = true;
                moves.push_back(capturemove);
            }
            else if (board->getPiecePtr(currentX - 1, currentY)->pieceType() == PieceEnum::None)
            {
                // no capture:
                moves.push_back(Move(this->board, currentX, currentY, currentX - 1, currentY));
            }
        }*/
    }
    break;

    case PieceEnum::Knight:
    {
        // 2D Vector that is going to store the possible movements that a Knight can make in X,Y pairs.
        int knightMoves[8][2] = {
            {1, 2}, {2, 1}, {-1, 2}, {-2, 1}, {1, -2}, {2, -1}, {-1, -2}, {-2, -1}};

        // loop over possible relative moves:
        for (int i = 0; i < 8; i++)
        {
            int newX = currentX + knightMoves[i][0];
            int newY = currentY + knightMoves[i][1];

            // checks for:
            // within bounds, and enemy piece:
            if (isWithinBounds(newX, newY))
            {
                // check for captures:
                if (board->getPiecePtr(newX, newY)->getColour() != p->getColour() || board->getPiecePtr(newX, newY)->pieceType() == PieceEnum::None)
                {
                    Move move = Move(this->board, currentX, currentY, newX, newY);

                    // make the move.didcapture flag be true, if the possible move has a piece on it.
                    move.didcapture = (board->getPiecePtr(newX, newY)->pieceType() != PieceEnum::None);
                    moves.push_back(move);
                }
            }
        }
        return moves;
    }
    break;

    //********* NONE POSSIBLE MOVES ************
    case PieceEnum::None:
    {
        return moves;
    }
    }

    return moves;
}
