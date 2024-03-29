#include "textdisplay.h"
#include "square.h"
using namespace std;

TextDisplay::TextDisplay() : theDisplay(8, std::vector<char>(8, '_')) {}

void TextDisplay::notify(Square &s)
{
    Piece *p = s.getOccupyingPc();
    if (p->pieceType() == PieceEnum::NonePc) {
        //int xCoord = s.getX();
        //int yCoord = s.getY();
        char spaceColour = (s.getX() % 2 == s.getY() % 2) ? ' ' : '_';
       theDisplay[s.getX()][s.getY()] = spaceColour;
    }
    else if (p->pieceType() == PieceEnum::Pawn && p->getColour()) {
       theDisplay[s.getX()][s.getY()] = 'P';
    } 
    else if (p->pieceType() == PieceEnum::Pawn) {
        theDisplay[s.getX()][s.getY()] = 'p';
    }
    else if (p->pieceType() == PieceEnum::Rook && p->getColour()) {
       theDisplay[s.getX()][s.getY()] = 'R';
    } 
    else if (p->pieceType() == PieceEnum::Rook) {
        theDisplay[s.getX()][s.getY()] = 'r';
    }
    else if (p->pieceType() == PieceEnum::Knight && p->getColour()) {
       theDisplay[s.getX()][s.getY()] = 'N';
    } 
    else if (p->pieceType() == PieceEnum::Knight) {
        theDisplay[s.getX()][s.getY()] = 'n';
    } 
    else if (p->pieceType() == PieceEnum::Bishop && p->getColour()) {
       theDisplay[s.getX()][s.getY()] = 'B';
    } 
    else if (p->pieceType() == PieceEnum::Bishop) {
        theDisplay[s.getX()][s.getY()] = 'b';
    }
    else if (p->pieceType() == PieceEnum::Queen && p->getColour()) {
       theDisplay[s.getX()][s.getY()] = 'Q';
    } 
    else if (p->pieceType() == PieceEnum::Queen) {
       theDisplay[s.getX()][s.getY()] = 'q';
    } 
    else if (p->pieceType() == PieceEnum::King && p->getColour()) {
        theDisplay[s.getX()][s.getY()] = 'K';
    }
    else if (p->pieceType() == PieceEnum::King) {
        theDisplay[s.getX()][s.getY()] = 'k';
    }
} 

TextDisplay::~TextDisplay() {}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td)
{
    cout << endl;
    for (int i = 0; i < 8; ++i)
    {
        out << abs(i - 8) << " ";
        for (int j = 0; j < 8; ++j)
        {
            out << td.theDisplay[i][j];
        }
        out << '\n';
    }
    out << "\n  abcdefgh" << endl << endl;
    return out;
}
