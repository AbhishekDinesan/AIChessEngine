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
        
        //check for White pawn promotion:
        for(int i = 0; i < 8; i ++) {
            if(board->getPiecePtr(i,0)->pieceType() == PieceEnum::Pawn) {
                char toPromote; 
                cout << "What do you want to Promote Pawn to? " << endl; 
                cin >> toPromote; 


                if(toPromote == 'R') {
                    delete board->getPiecePtr(i,0);
                    Rook *newpiece = new Rook(true, true, i, 0, true); 
                    board->squares[i][0].setPiece(newpiece); 
                }

                if(toPromote == 'Q') {
                    delete board->getPiecePtr(i,0);
                    Queen *newpiece = new Queen(true, true, i, 0);  
                    board->squares[i][0].setPiece(newpiece); 
                }

                if(toPromote == 'B') {
                    delete board->getPiecePtr(i,0);
                    Bishop *newpiece = new Bishop(true, true, i, 0);  
                    board->squares[i][0].setPiece(newpiece); 
                } 

                if(toPromote == 'N') {
                    delete board->getPiecePtr(i,0);
                    Knight *newpiece = new Knight(true, true, i, 0);  
                    board->squares[i][0].setPiece(newpiece); 
                }  
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
