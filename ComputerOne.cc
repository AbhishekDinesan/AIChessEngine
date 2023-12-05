
#include "AbstractComputer.h"
#include "AbstractPiece.h"
#include "Move.h"
#include "Board.h"
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>
using namespace std;

class ComputerOne : public Computer
{

public:
    ComputerOne(bool isWhite, bool isHuman, bool isInCheck, Board *myboard) : Computer(isWhite, isHuman, isInCheck, myboard) {}
    virtual void makeMove(int startFile, int startRank, int endFile, int endRank)
        override
    {
        Move m(board, startFile, startRank, endFile, endRank);
        vector<Move> masterVector;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if ((board->squares[i][j].getOccupyingPc()->getColour() == isWhite) &&
                    (board->squares[i][j].getOccupyingPc()->pieceType() != PieceEnum::None))
                {
                    vector<Move> tempVector = m.possibleMoves(board->squares[i][j].getOccupyingPc());
                    masterVector.insert(masterVector.end(), tempVector.begin(), tempVector.end());
                    // std ::cout << "(" << board->squares[i][j].getX() << "," << board->squares[i][j].getY() << ")" << std::endl;
                }
            }
        }
        int vectorLength = masterVector.size();
        srand(static_cast<unsigned>(std::time(0)));
        int random_number = rand() % (vectorLength + 1);
        Move newMove = masterVector[random_number];
        board->movePiece(newMove.fromX, newMove.fromY, newMove.toX, newMove.toY);
    }
};