#include "AbstractComputer.h"
#include <vector>
#include "Move.h"

using namespace std;

class ComputerTwo : public Computer
{
    ComputerTwo(bool isWhite, bool isHuman, bool isInCheck, Board *myboard) : Computer(isWhite, isHuman, isInCheck, myboard) {}

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
                if (board->squares[i][j].getOccupyingPc()->getColour() == isWhite &&
                    board->squares[i][j].getOccupyingPc()->pieceType() != PieceEnum::None)
                {
                    vector<Move> tempVector = m.possibleMoves(board->squares[i][j].getOccupyingPc());
                    masterVector.insert(masterVector.end(), tempVector.begin(), tempVector.end());
                    // std ::cout << "(" << board->squares[i][j].getX() << "," << board->squares[i][j].getY() << ")" << std::endl;
                }
            }
        }
        for (int i = 0; i < masterVector.size(); i++)
        {
            Board b(false, true);
            //  then for each board, initialize the piece at each board
            //  by going into a double for loop
            //  execute masterVector[i]on the board
            //  if is in check, execute that move, return
            //  if you execute the move, and you isCaptured is true
            // execute that move, return
        }
        // if there are no chequaing moves, then you can generate a random move
        // no checking moves, generate a random move
    }
};