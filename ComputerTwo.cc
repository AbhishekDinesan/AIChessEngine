#include "AbstractComputer.h"
#include "ComputerTwo.h"
#include <vector>
#include "Move.h"
#include "Board.h"
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;


    ComputerTwo::ComputerTwo(bool isWhite, bool isHuman, bool isInCheck, Board *myboard) : 
        Computer(isWhite, isHuman, isInCheck, myboard) {}

    void ComputerTwo::makeMove(int startFile, int startRank, int endFile, int endRank) {
        Move m(board, startFile, startRank, endFile, endRank);
        vector<Move> masterVector;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board->squares[i][j].getOccupyingPc()->getColour() == isWhite &&
                    board->squares[i][j].getOccupyingPc()->pieceType() != PieceEnum::NonePc)
                {
                    vector<Move> tempVector = m.possibleMoves(board->squares[i][j].getOccupyingPc());
                    masterVector.insert(masterVector.end(), tempVector.begin(), tempVector.end());
                }
            }
        }
        for (int x = 0; x < masterVector.size(); x++)
        {
            Board tempBoard(false, true);
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    tempBoard.squares[i][j].setPiece(board->squares[i][j].getOccupyingPc());
                }
            }
            Move newMove = masterVector[x];
            tempBoard.movePiece(newMove.fromX, newMove.fromY, newMove.toX, newMove.toY);
            
            if (tempBoard.isCheck(!this->getColour())) // if the board produced a check, then you execute move on real board
            {
                board->movePiece(newMove.fromX, newMove.fromY, newMove.toX, newMove.toY);
                return;
            }
        }
        int vectorLength = masterVector.size();
        srand(static_cast<unsigned>(std::time(0)));
        int random_number = rand() % (vectorLength + 1);
        Move newMove2 = masterVector[random_number];
        board->movePiece(newMove2.fromX, newMove2.fromY, newMove2.toX, newMove2.toY);
        // if there are no chequaing moves, then you can generate a random move
        // no checking moves, generate a random move
    }

    bool ComputerTwo::getIsHuman() {
        return false;
    }

    bool ComputerTwo::getColour() {
        return isWhite;
    }

    void ComputerTwo::setBoard(Board* b) {
        board = b;
    }