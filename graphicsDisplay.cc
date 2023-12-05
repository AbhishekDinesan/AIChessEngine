/* #include "graphicsDisplay.h"
#include "window.h"
#include <string>
using namespace std;

GraphicsDisplay::GraphicsDisplay(Xwindow &w) : w{w} {}

//void drawPawn

void GraphicsDisplay::notify(Square &s) {
        const int sqSize = 75;
        const int fillColour = (s.getX() % 2 == s.getY() % 2) ? Xwindow::White : Xwindow::Green;
        int x = (s.getY() * sqSize) + 75;
        int y = (s.getX() * sqSize);
        w.fillRectangle(x, y, sqSize, sqSize, fillColour);

        w.drawString(37, 37, "8");
        w.drawString(37, 112, "7");
        w.drawString(37, 187, "6");
        w.drawString(37, 262, "5");
        w.drawString(37, 337, "4");
        w.drawString(37, 412, "3");
        w.drawString(37, 487, "2");
        w.drawString(37, 562, "1");

        w.drawString(112, 637, "A");
        w.drawString(187, 637, "B");
        w.drawString(262, 637, "C");
        w.drawString(337, 637, "D");
        w.drawString(412, 637, "E");
        w.drawString(487, 637, "F");
        w.drawString(562, 637, "G");
        w.drawString(637, 637, "H");

        int textX = x + 37;
        int textY = y + 37;
        Piece* p = s.getOccupyingPc();
        if (p->pieceType() == PieceEnum::Pawn) {
                if (p->getColour()) w.drawString(textX, textY, "P");
                else w.drawString(textX, textY, "p");
        }
        else if (p->pieceType() == PieceEnum::Rook) {
                if (p->getColour()) w.drawString(textX, textY, "R");
                else w.drawString(textX, textY, "r");
        }
        else if (p->pieceType() == PieceEnum::Knight) {
                if (p->getColour()) w.drawString(textX, textY, "N");
                else w.drawString(textX, textY, "n");
        }
        else if (p->pieceType() == PieceEnum::Bishop) {
                if (p->getColour()) w.drawString(textX, textY, "B");
                else w.drawString(textX, textY, "b");
        }
        else if (p->pieceType() == PieceEnum::Queen) {
                if (p->getColour()) w.drawString(textX, textY, "Q");
                else w.drawString(textX, textY, "q");
        }
        else if (p->pieceType() == PieceEnum::King) {
                if (p->getColour()) w.drawString(textX, textY, "K");
                else w.drawString(textX, textY, "k");
        }
}

GraphicsDisplay::~GraphicsDisplay() {}
*/