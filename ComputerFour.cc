#include "AbstractComputer.h"
#include "AbstractPiece.h"
#include "PawnPiece.h"
#include <map>

using namespace std;

class ComputerFour : public Computer
{
    ComputerFour(bool isWhite, bool isHuman, bool isInCheck, Board *myboard) : Computer(isWhite, isHuman, isInCheck, myboard) {}

public:
    void makeMove(int startFile, int startRank, int endFile, int endRank)
        override
    {
        map<Piece *, vector<vector<int>>> pieceMap; // Made this a pointer to piece, it was causing an error
        vector<vector<int>> Pmatrix;
        vector<vector<int>> Kmatrix;
        vector<vector<int>> Qmatrix;
        vector<vector<int>> Rmatrix;
        vector<vector<int>> Nmatrix;
        vector<vector<int>> Bmatrix;

        Pmatrix = {{0, 0, 0, 0, 0, 0, 0, 0},
                   {50, 50, 50, 50, 50, 50, 50, 50},
                   {10, 10, 20, 30, 30, 20, 10, 10},
                   {5, 5, 10, 25, 25, 10, 5, 5},
                   {0, 0, 0, 20, 20, 0, 0, 0},
                   {5, -5, -10, 0, 0, -10, -5, 5},
                   {5, 10, 10, -20, -20, 10, 10, 5},
                   {0, 0, 0, 0, 0, 0, 0, 0}};

        Kmatrix = {{-50, -40, -30, -30, -30, -30, -40, -50},
                   {-40, -20, 0, 0, 0, 0, -20, -40},
                   {-30, 0, 10, 15, 15, 10, 0, -30},
                   {-30, 5, 15, 20, 20, 15, 5, -30},
                   {-30, 0, 15, 20, 20, 15, 0, -30},
                   {-30, 5, 10, 15, 15, 10, 5, -30},
                   {-40, -20, 0, 5, 5, 0, -20, -40},
                   {-50, -40, -30, -30, -30, -30, -40, -50}};

        Bmatrix = {{-20, -10, -10, -10, -10, -10, -10, -20},
                   {-10, 0, 0, 0, 0, 0, 0, -10},
                   {-10, 0, 5, 10, 10, 5, 0, -10},
                   {-10, 5, 5, 10, 10, 5, 5, -10},
                   {-10, 0, 10, 10, 10, 10, 0, -10},
                   {-10, 10, 10, 10, 10, 10, 10, -10},
                   {-10, 5, 0, 0, 0, 0, 5, -10},
                   {-20, -10, -10, -10, -10, -10, -10, -20}};

        Rmatrix = {{0, 0, 0, 0, 0, 0, 0, 0},
                   {5, 10, 10, 10, 10, 10, 10, 5},
                   {-5, 0, 0, 0, 0, 0, 0, -5},
                   {-5, 0, 0, 0, 0, 0, 0, -5},
                   {-5, 0, 0, 0, 0, 0, 0, -5},
                   {-5, 0, 0, 0, 0, 0, 0, -5},
                   {-5, 0, 0, 0, 0, 0, 0, -5},
                   {0, 0, 0, 5, 5, 0, 0, 0}};

        Qmatrix = {{-20, -10, -10, -5, -5, -10, -10, -20},
                   {-10, 0, 0, 0, 0, 0, 0, -10},
                   {-10, 0, 5, 5, 5, 5, 0, -10},
                   {-5, 0, 5, 5, 5, 5, 0, -5},
                   {0, 0, 5, 5, 5, 5, 0, -5},
                   {-10, 5, 5, 5, 5, 5, 0, -10},
                   {-10, 0, 5, 0, 0, 0, 0, -10},
                   {-20, -10, -10, -5, -5, -10, -10, -20}};

        Kmatrix = {{-30, -40, -40, -50, -50, -40, -40, -30},
                   {-30, -40, -40, -50, -50, -40, -40, -30},
                   {-30, -40, -40, -50, -50, -40, -40, -30},
                   {-30, -40, -40, -50, -50, -40, -40, -30},
                   {-20, -30, -30, -40, -40, -30, -30, -20},
                   {-10, -20, -20, -20, -20, -20, -20, -10},
                   {20, 20, 0, 0, 0, 0, 20, 20},
                   {20, 30, 10, 0, 0, 10, 30, 20}};
        Pawn P();
        // pieceMap[P] = Pmatrix;

        /*
        loop through the possible moves
        deep copy onto a seperate board
        then compute the score by iterating through each piece
        then we use the map to return an integer value corresponding to piece @ position
        */
        Move m(board, startFile, startRank, endFile, endRank);
        vector<Move> masterVector;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                // if it is the right colour and not nonepiece
                vector<Move> tempVector = m.possibleMoves(board->squares[i][j].getOccupyingPc());
                masterVector.insert(masterVector.end(), tempVector.begin(), tempVector.end());
            }
        }
        int highestindex = INT_MIN;

        for (int x = 0; x < masterVector.size(); x++)
        {

            // Board tempboard = board;
            Move m = masterVector[x];
            // execute the move
            // evaluate the board
            int greatestScore = 0;
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    int temp; // let this map the value
                    if (temp > greatestScore)
                    {
                        greatestScore = temp;
                        highestindex = x;
                    }
                }
            }
        }

        // execute the move that is masterVector[x]
    }
};
