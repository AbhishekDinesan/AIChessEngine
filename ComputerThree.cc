#include "AbstractComputer.h"
#include "ComputerThree.h"
#include <vector>
#include "Move.h"

using namespace std;

ComputerThree::ComputerThree(bool isWhite, bool isHuman, bool isInCheck, Board *myboard) : Computer(isWhite, isHuman, isInCheck, myboard) {}

void ComputerThree::makeMove(int startFile, int startRank, int endFile, int endRank)
    {
        // now this is for the opponents moves
        Move m(board, startFile, startRank, endFile, endRank);
        vector<Move> masterVector;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                vector<Move> tempVector = m.possibleMoves(board->squares[i][j].getOccupyingPc());
                masterVector.insert(masterVector.end(), tempVector.begin(), tempVector.end());
            }
        }

        for (int i = 0; i < masterVector.size(); i++)
        {
            // Board temp = board;
            //  execute masterVector[i];
            //   if it captures or cheques, get the ending position and move the piece there
            //  if not possible to move that piece, then move onto something else
        }

        // then do the logic from computerII
    }

    bool ComputerThree::getIsHuman() {
        return false;
    }

    bool ComputerThree::getColour() {
        return isWhite;
    }

    void ComputerThree::setBoard(Board* b) {
        board = b;
    }

    // literally the same logic from q2
