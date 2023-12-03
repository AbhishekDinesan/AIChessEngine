#include "AbstractComputer.h"
#include <vector>
#include "Move.h"

using namespace std;

class ComputerTwo : public Computer
{
public:
    void makeMove(int startFile, int startRank, int endFile, int endRank)
        override
    {
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
            Board temp = board;
            // execute masterVector[i];
            //  if it captures or pawns, break and actually execute this move
        }
    }
};