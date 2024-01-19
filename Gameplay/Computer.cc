#include "AbstractComputer.h"
#include "Computer.h"
#include <vector>
#include "Move.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include <map>

using namespace std;

const int GRID_DIMENSION = 8;

map<PieceEnum, vector<vector<int>>> pieceMap;
vector<vector<int>> Pmatrix;
vector<vector<int>> Kmatrix;
vector<vector<int>> Qmatrix;
vector<vector<int>> Rmatrix;
vector<vector<int>> Nmatrix;
vector<vector<int>> Bmatrix;

ComputerThree::ComputerThree(bool isWhite, bool isHuman, bool isInCheck, Board *myboard) : Computer(isWhite, isHuman, isInCheck, myboard)
{

    Pmatrix = {{0, 0, 0, 0, 0, 0, 0, 0},
               {50, 50, 50, 50, 50, 50, 50, 50},
               {10, 10, 20, 30, 30, 20, 10, 10},
               {5, 5, 10, 25, 25, 10, 5, 5},
               {0, 0, 0, 20, 20, 0, 0, 0},
               {5, -5, -10, 0, 0, -10, -5, 5},
               {5, 10, 10, -20, -20, 10, 10, 5},
               {0, 0, 0, 0, 0, 0, 0, 0}};

    Nmatrix = {{-50, -40, -30, -30, -30, -30, -40, -50},
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

    pieceMap[PieceEnum::Pawn] = Pmatrix;
    pieceMap[PieceEnum::Bishop] = Bmatrix;
    pieceMap[PieceEnum::Knight] = Nmatrix;
    pieceMap[PieceEnum::Rook] = Rmatrix;
    pieceMap[PieceEnum::Queen] = Qmatrix;
    pieceMap[PieceEnum::King] = Kmatrix;
}

int EvaluateSquare(Square square)
{
    PieceEnum piece = square.getOccupyingPc()->pieceType();
    if (piece == PieceEnum::NonePc)
    {
        return 0;
    }
    return pieceMap[piece][square.getX()][square.getY()];
}

int EvaluationFunction(Board *board)
{
    int result = 0;
    for (int i = 0; i < GRID_DIMENSION; i++)
    {
        for (int j = 0; j < GRID_DIMENSION; j++)
        {
            result += EvaluateSquare(board->squares[i][j]);
        }
    }
    return result;
}

int max(int one, int two)
{
    if (one > two)
    {
        return one;
    }
    return two;
}

int MiniMax(Board *board, int depth, bool isMax)
{
    if (depth == 0)
    {
        return EvaluationFunction(board);
    }
    if (isMax)
    {
        int maxEval = INT_MIN;
        int max = INT_MIN;
        Board *tempBoard = board;
        // for each legal move
        //  create a temporary baord, simulate the move
        int eval = MiniMax(tempBoard, depth - 1, false);
        maxEval = max(maxEval, eval);
    }
    else
    {
        int minEval = INT_MAX;
        ChessBoard tempBoard = board;
        int eval = minimax(tempBoard, depth - 1, true);
        minEval = min(minEval, eval);
    }
    return minEval;
}

void ComputerThree::makeMove(int startFile, int startRank, int endFile, int endRank)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    Move m(board, startFile, startRank, endFile, endRank);
    vector<Move> masterVector;         // holds all CPU's possible moves
    vector<Move> opponentMasterVector; // holds all opponents possible moves
    for (int i = 0; i < GRID_DIMENSION; i++)
    {
        for (int j = 0; j < GRID_DIMENSION; j++)
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
    // cout << EvaluationFunction(board) << endl;
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