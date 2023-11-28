#include "game.h"
#include "board.h" // Assuming you have a board.h file
// #include "player.h" // Assuming you have a player.h file

Game::Game() : board(nullptr)
{
}

Game::~Game()
{
    delete board;
}

void Game::init()
{
}

bool Game::ValidBoard()
{
    return false;
}

bool Game::endGame()
{
    return false;
}

void Game::movePiece()
{
}
