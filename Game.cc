#include "Game.h"
#include "Board.h"
#include "AbstractPlayer.h"
#include "AbstractPiece.h"
#include "PawnPiece.h"
#include "RookPiece.h"
#include "QueenPiece.h"
#include "KingPiece.h" 
#include "BishopPiece.h"
#include "KnightPiece.h" 
#include "NonePiece.h" 
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

/* 
void Game::passantMove(int fromX, int fromY, int toX, int toY) {
    if (fromX > toX) {
        delete board->squares[fromX - 1][fromY].getOccupyingPc();
        NonePc *emptyPiece = new NonePc(fromX - 1, fromY);
        board->squares[fromX - 1][fromY].setPiece(emptyPiece);
    }
    else if (fromY < toX) {
        delete board->squares[fromX + 1][fromY].getOccupyingPc();
        NonePc *emptyPiece = new NonePc(fromX + 1, fromY);
        board->squares[fromX + 1][fromY].setPiece(emptyPiece);
    }
}
*/ 

void Game::movePiece(int fromX, int fromY, int toX, int toY) // wouldn't this be called from the game function
{
    Move m = Move(board, fromX, fromY, toX, toY);

    Piece *pc = board->getPiecePtr(fromX, fromY);

    if (m.isValidMove())
    {
        board->movePiece(fromX, fromY, toX, toY);

        /* 
        if (m.getDidPassant() == true) {
            this->passantMove(fromX, fromY, toX, toY);
        }
        board->isCheck(true);
        board->isCheck(false);
        */ 
        
        //check for White pawn promotion:
        for(int i = 0; i < 8; i++) { 
            if(board->getPiecePtr(i, 0)->pieceType() == PieceEnum::Pawn && 
               board->getPiecePtr(i,0)->getColour() == true) {
                char toPromote; 
                do {
                    cout << "What do you want to Promote Pawn to? (Q, R, B, N) " << endl; 
                    cin >> toPromote;
                } while(toPromote != 'Q' && toPromote != 'R' && toPromote != 'B' && toPromote != 'N');

                delete board->getPiecePtr(i, 0);

                switch (toPromote) {
                    case 'R':
                        board->squares[i][0].setPiece(new Rook(true, true, i, 0, true));
                        break;
                    case 'Q':
                        board->squares[i][0].setPiece(new Queen(true, true, i, 0));
                        break;
                    case 'B':
                        board->squares[i][0].setPiece(new Bishop(true, true, i, 0));
                        break;
                    case 'N':
                        board->squares[i][0].setPiece(new Knight(true, true, i, 0));
                        break;
                }
                break; // Break after promoting a pawn
            }
        }



        //check for black pawn promotion: 
        for(int j = 0; j < 8; j++) { 
            if(board->getPiecePtr(j, 7)->pieceType() == PieceEnum::Pawn && 
               board->getPiecePtr(j,7)->getColour() == false) {
                char toPromote; 
                do {
                    cout << "What do you want to Promote Pawn to? (q, r, b, n) " << endl; 
                    cin >> toPromote;
                } while(toPromote != 'q' && toPromote != 'r' && toPromote != 'b' && toPromote != 'n');

                delete board->getPiecePtr(j, 7);

                switch (toPromote) {
                    case 'r':
                        board->squares[j][7].setPiece(new Rook(false, true, j, 7, true));
                        break;
                    case 'q':
                        board->squares[j][7].setPiece(new Queen(false, true, j, 7));
                        break;
                    case 'b':
                        board->squares[j][7].setPiece(new Bishop(false, true, j, 7));
                        break;
                    case 'n':
                        board->squares[j][7].setPiece(new Knight(false, true, j, 7));
                        break;
                }
                break; // Break after promoting a pawn
            }
        }

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
    else {
        cerr << "Invalid Move" << endl;

    }
    /*
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
