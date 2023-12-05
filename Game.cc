#include "Game.h"
#include "Board.h"
#include "AbstractPlayer.h"
#include "AbstractPiece.h"
#include "PawnPiece.h"
#include <ostream>
#include <utility>
#include <iostream>
using namespace std;

Game::Game(AbstractPlayer* white, AbstractPlayer* black, bool whiteToMove, bool customProvided, Board *theCustomBoard) : 
    whitePlayer{white}, blackPlayer{black}, moveCount{0}, whiteToMove{whiteToMove}, board{theCustomBoard}
{
    if (!customProvided)
    {
        board = new Board(false, false);
    }
    whitePlayer->setBoard(board);
    blackPlayer->setBoard(board);
    board->setTurn(whiteToMove);
    printBoard();
}

Game::~Game()
{
    // delete board; IM USING UNIQUE POINTERS NOW
}

bool Game::getGameOver() {
    return gameOver;
}

bool Game::setGameOver(bool over) {
    gameOver = over;
}

AbstractPlayer* Game::getCurrPlayer() {
    if (board->isWhiteTurn == true) {
        return whitePlayer;
    } else {
        return blackPlayer;
    }
}

bool Game::getCurrTurn() {
    return board->isWhiteTurn;
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

        if (pc->getColour() == true) {
            if (board->isCheck(false) == true) {
                cout << "Black is in check." << endl;
                if (board->isCheckMate(false) == true) {
                    cout << "Checkmate! White wins." << endl;
                    this->setGameOver(true);
                }
            }
        }
        else if (pc->getColour() == false) {
            if (board->isCheck(true) == true) {
                cout << "White is in check." << endl;
                if (board->isCheckMate(true) == true) {
                    cout << "Checkmate! Black wins." << endl;
                    this->setGameOver(true);
                }
            }
        }
        
        //board->isCheck(true);
        //board->isCheck(false);
        
        
    }
    /*
    else {
        cerr << "Invalid Move" << endl;
    }

    if(board->isCheck(true)) {
        if (board->isCheckMate(true) == true) {
            cout << "Checkmate! Black wins." << endl;
        }
    }

    if(board->isCheck(false)) {
        if (board->isCheckMate(false) == true) {
            cout << "Checkmate! White wins." << endl;
        }
    }
    
    if (board->isCheck(true) || board->isCheck(false))
    {
        board->isCheckMate(true);
        board->isCheckMate(false);
    }
    */
    //whiteToMove = !whiteToMove;
    // ADD THE MOVE TO A VECTOR FOR THE UNDO FUNCTION
    //printBoard();
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
