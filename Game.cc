#include "Game.h"
#include "Board.h"          // Assuming you have a board.h file
#include "AbstractPlayer.h" // Assuming you have a player.h file
#include "AbstractPiece.h"
#include "PawnPiece.h"
#include <ostream>
#include <memory>
using namespace std;

Game::Game() : moveCount{0}
{
    board = make_unique<Board>();
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

bool Game::ValidBoard()
{
    int whiteKcount;
    int blackKcount;
    bool isCheck;
    for (int x = 0; x < 8; ++x)
    {
        for (int y = 0; y < 8; ++y)
        {
            /*
            if (board->getPiece() == PieceEnum::King) // still need to check if this is white/black
            {
                whiteKcount++;
            }
            */
            if (x == 0 || x == 7)
            {
                /*
                if (board->getPiece() == PieceEnum::Pawn)
                {
                    return false;
                }
                */
            }
        }
    }
    return whiteKcount && !isCheck;
}

bool Game::endGame()
{ // consdier the stalemate case seperately
    // return board->isCheckMate();
    return true;
}

/*
void Game::movePiece() // wouldn't this be called from the game function
{

    //Move *newMove = new Move();
}
*/

void Game::addPiece(char piece, int x, int y)
{
    Piece *p;
    if (piece == 'P')
    {
        bool beenMoved = (x == 6) ? true : false;
        p = new Pawn(true, true, beenMoved, x, y);
    }
    else if (piece == 'p')
    {
        bool beenMoved = (x == 1) ? true : false;
        p = new Pawn(false, true, beenMoved, x, y);
    }
}

std::ostream &operator<<(std::ostream &out, const Game &g)
{
    out << g.board;
    return out;
}

void Game::printBoard()
{
    std::cout << *board->td; // Use a pointer to dereference and print the Board
}

std::unique_ptr<Board> &Game::getBoard()
{
    return board;
}