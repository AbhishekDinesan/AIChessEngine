#include "Game.h"
#include "Board.h"          // Assuming you have a board.h file
#include "AbstractPlayer.h" // Assuming you have a player.h file

Game::Game() {}

Game::~Game()
{
    delete board;
}

void Game::init()
{
    board = new Board(); // this should create new 8 x 8 grid
                         // PlayerOne = new Player();
                         // PlayerTwo = new PlayerTwo();
                         // Player currentPlayer = PlayerOne;
                         // Vector pastmoves;
                         // std::vector<std::vector<Move>> pastMoves;
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

void Game::movePiece() // wouldn't this be called from the game function
{
    Move *newMove = new Move();
}
