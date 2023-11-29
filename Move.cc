#include "Move.h"

Move::Move() {}
Move::~Move() {}
// Piece* Move::CapturedPiece() {}
bool Move::isCheck() { return false; }
void Move::UpdateBoard() {}
bool Move::willCheck() { return false; }