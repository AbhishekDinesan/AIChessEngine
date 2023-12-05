#include "ComputerFour.h"
#include "PawnPiece.h"
#include <climits>
#include <map>

using namespace std;

ComputerFour::ComputerFour(bool isWhite, bool isHuman, bool isInCheck, Board *myboard) : Computer(isWhite, isHuman, isInCheck, myboard) {}

void ComputerFour::makeMove(int startFile, int startRank, int endFile, int endRank)
{
    map<PieceEnum, vector<vector<int>>> pieceMap; // Made this a pointer to piece, it was causing an error
    vector<vector<int>> Pmatrix;
    vector<vector<int>> Kmatrix;
    vector<vector<int>> Qmatrix;
    vector<vector<int>> Rmatrix;
    vector<vector<int>> Nmatrix;
    vector<vector<int>> Bmatrix;

    // prefer capturing moves, checking problem

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

    // COMPUTER LOGIC

    // 1. Avoid capture/Mate logic from Level 3
    // prefer certain pieces over others

    // this populates two vectors, one with all CPU possible moves, one with opponents moves
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
    // iterate over the opponents moves to determine if anything will capture us or check us
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
                // HERE I NEED TO ACT LOGIC IN ORDER TO PREFER CERTAIN PIECES
                vector<Move> deadMoves = tempMove.possibleMoves(board->squares[tempMove.toX][tempMove.toY].getOccupyingPc());
                if (deadMoves.size() != 0) // check if that captured piece has any possible moves to escape
                {
                    board->movePiece(deadMoves[0].fromX, deadMoves[0].fromY, deadMoves[0].toX, deadMoves[0].toY);
                    return;
                }
            }
        }
    }

    // 2. Prefer capture/Mate logic from Level 2
    // prefer certain pieces over others

    for (int x = 0; x < masterVector.size(); x++)
    {
        // INSERT LOGIC ABOUT HOW WE CAN PREFER CERTAIN MOVES
        Board tempBoard = *board;
        Move newMove = masterVector[x];
        tempBoard.movePiece(newMove.fromX, newMove.fromY, newMove.toX, newMove.toY);
        bool isKingInCheck = tempBoard.isCheck(!isWhite);
        if (isKingInCheck || newMove.willCapture())
        {
            // execute the checking/capturing move immediately
            board->movePiece(newMove.fromX, newMove.fromY, newMove.toX, newMove.toY);
            return;
        }
    }

    // 3. Prefer matrix moves (unique Level 4)

    /*
    loop through the possible moves
    deep copy onto a seperate board
    then compute the score by iterating through each piece
    then we use the map to return an integer value corresponding to piece @ position
    */
    // Move m(board, startFile, startRank, endFile, endRank);
    //  vector<Move> masterVector;
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

bool ComputerFour::getIsHuman()
{
    return false;
}

bool ComputerFour::getColour()
{
    return isWhite;
}

void ComputerFour::setBoard(Board *b)
{
    board = b;
}
