#include "Player.h"
#include "Board.h"

Player::Player (bool isWhite, bool isHuman, bool isInCheck, Board *myboard) : 
    AbstractPlayer(isWhite, isHuman, isInCheck, myboard) {}


void Player::makeMove(int startFile, int startRank, int endFile, int endRank) {
    board->movePiece(startFile, startRank, endFile, endRank);
}

bool Player::getIsHuman() {
    return true;
}

bool Player::getColour() {
    return true;
}

void Player::setBoard(Board* b) {
        board = b;
}
