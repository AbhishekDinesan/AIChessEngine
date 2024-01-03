#include "AbstractComputer.h"
#include "Computer.h"
#include <vector>
#include "Move.h"
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

ComputerThree::ComputerThree(bool isWhite, bool isHuman, bool isInCheck, Board *myboard) : Computer(isWhite, isHuman, isInCheck, myboard) {}

void ComputerThree::makeMove(int startFile, int startRank, int endFile, int endRank)
{
    Move m(board, startFile, startRank, endFile, endRank);
    vector<Move> masterVector;         // holds all CPU's possible moves
    vector<Move> opponentMasterVector; // holds all opponents possible moves
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board->squares[i][j].getOccupyingPc()->getColour() == isWhite &&
                board->squares[i][j].getOccupyingPc()->pieceType() != PieceEnum::NonePc)
            {
                // populates all possible moves for CPU
                vector<Move> tempVector = m.possibleMoves(board->squares[i][j].getOccupyingPc());
                masterVector.insert(masterVector.end(), tempVector.begin(), tempVector.end());
            }
            if ((board->squares[i][j].getOccupyingPc()->getColour() == (!isWhite)) &&
                board->squares[i][j].getOccupyingPc()->pieceType() != PieceEnum::NonePc)
            {
                vector<Move> ptempVector = m.possibleMoves(board->squares[i][j].getOccupyingPc());
                opponentMasterVector.insert(opponentMasterVector.end(), ptempVector.begin(), ptempVector.end());
            }
        }
    }
    // now we iterate over the opponents Moves
    for (int x = 0; x < opponentMasterVector.size(); x++)
    {
        Board tempBoard = *board;
        Move newMove = opponentMasterVector[x];
        tempBoard.movePiece(newMove.fromX, newMove.fromY, newMove.toX, newMove.toY); // we simulate the move
        bool isKingInCheck = tempBoard.isCheck(isWhite);                             // check if CPU king is in check
        if (isKingInCheck || newMove.willCapture())                                  // if my king is in check, or if my piece will be captured
        {
            vector<int> KingPos = board->findKing(isWhite); // generate all possible King Moves
            Move tempMove = opponentMasterVector[x];
            vector<Move> allKingMoves = tempMove.possibleMoves(board->squares[KingPos[0]][KingPos[1]].getOccupyingPc());
            if (allKingMoves.size() != 0) // if the king has possible, legal moves....execute them
            {
                board->movePiece(allKingMoves[0].fromX, allKingMoves[0].fromY, allKingMoves[0].toX, allKingMoves[0].toY);
                return;
            }
            if (tempMove.willCapture()) // if the simulated board has captured
            {
                vector<Move> deadMoves = tempMove.possibleMoves(board->squares[tempMove.toX][tempMove.toY].getOccupyingPc());
                if (deadMoves.size() != 0) // check if that captured piece has any possible moves to escape
                {
                    board->movePiece(deadMoves[0].fromX, deadMoves[0].fromY, deadMoves[0].toX, deadMoves[0].toY);
                    return;
                }
            }
        }
    }

    // now lets iterate over our own moves, and borrow the same logic from LEVEL 2
    for (int x = 0; x < masterVector.size(); x++)
    {
        Board tempBoard = *board;
        Move newMove = masterVector[x];
        tempBoard.movePiece(newMove.fromX, newMove.fromY, newMove.toX, newMove.toY);
        bool isKingInCheck = tempBoard.isCheck(!isWhite);
        if (isKingInCheck || newMove.willCapture())
        {
            board->movePiece(newMove.fromX, newMove.fromY, newMove.toX, newMove.toY);
            return;
        }
    }
    // else we are going to do a random move
    int vectorLength = masterVector.size();
    srand(static_cast<unsigned>(std::time(0)));
    int random_number = rand() % (vectorLength + 1);
    Move newMove2 = masterVector[random_number];
    board->movePiece(newMove2.fromX, newMove2.fromY, newMove2.toX, newMove2.toY);
}

bool ComputerThree::getIsHuman()
{
    return false;
}

bool ComputerThree::getColour()
{
    return isWhite;
}

void ComputerThree::setBoard(Board *b)
{
    board = b;
}