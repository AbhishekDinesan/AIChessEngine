#include "AbstractComputer.h"
#include <vector>
#include "Move.h"
#include "Board.h"
#include <cstdlib>
#include <ctime>
#include <random>

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
            
            /*
            if (tempBoard.isCheck()) // if the board produced a check, then you execute move on real board
            {
                board->movePiece(newMove.fromX, newMove.fromY, newMove.toX, newMove.toY);
                return;
            }
            // if this move will result in a capture, then execute that move
            */ 
        }
        int vectorLength = masterVector.size();
        srand(static_cast<unsigned>(std::time(0)));
        int random_number = rand() % (vectorLength + 1);
        Move newMove2 = masterVector[random_number];
        board->movePiece(newMove2.fromX, newMove2.fromY, newMove2.toX, newMove2.toY);
        // if there are no chequaing moves, then you can generate a random move
        // no checking moves, generate a random move
    }
};