#include "Game.h"
#include "Board.h"
#include "AbstractPlayer.h"
#include "AbstractPiece.h"
#include "PawnPiece.h"
#include <ostream>
#include <utility>
#include <iostream>
using namespace std;

Game::Game(bool whiteToMove, bool customProvided, Board *theCustomBoard) : moveCount{0}, whiteToMove{whiteToMove}, board{theCustomBoard}
{

    if (!customProvided)
    {
        board = new Board(false, false);
    }
    printBoard();
}

Game::~Game()
{
    // delete board; IM USING UNIQUE POINTERS NOW
}

void Game::init()
{
    // unique_ptr<Board> board = make_unique<Board>();
    // printBoard(); // this should create new 8 x 8 grid
    //  PlayerOne = new Player();
    //  PlayerTwo = new PlayerTwo();
    //  Player currentPlayer = PlayerOne;
    //  Vector pastmoves;
    //  std::vector<std::vector<Move>> pastMoves;
    moveCount = 0;
}

bool Game::endGame()
{ // consdier the stalemate case seperately
    // return board->isCheckMate();
    return true;
}

void Game::movePiece(int fromX, int fromY, int toX, int toY) // wouldn't this be called from the game function
{
    Move m = Move(board, fromX, fromY, toX, toY);
    board->isWhiteTurn = !board->isWhiteTurn;

    // TEMPORARY, PLEASE DELETE:
    std::vector<Move> moves = m.possibleMoves(board->getPiecePtr(fromX, fromY));

    Piece *pc = board->getPiecePtr(fromX, fromY);
    std::cout << "For Piece: " << (int)pc->pieceType() << endl;

    for (Move move : moves)
    {
        std::cout << (int)move.toX << " " << (int)move.toY << endl;
    }

    cout << "(3)" << endl;
    if (m.isValidMove())
    {
        board->movePiece(fromX, fromY, toX, toY);
        board->isCheck(true);
        board->isCheck(false);
    }
    if (board->isCheck(true) || board->isCheck(false))

    {
        board->isCheckMate(true);
        board->isCheckMate(false);
    }
    // ADD THE MOVE TO A VECTOR FOR THE UNDO FUNCTION
}

void Game::addPiece(int x, int y, char piece)
{
    board->addPiece(x, y, piece);
}

std::ostream &operator<<(std::ostream &out, const Game &g)
{
    out << g.board;
    return out;
}

void Game::printBoard()
{
    board->printBoard();
}
