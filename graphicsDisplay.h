/*
#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H

#include "AbstractObserver.h"
#include "window.h"
#include "square.h"
#include "AbstractPiece.h"

class GraphicsDisplay : public Observer {
    Xwindow &w;
public:
    GraphicsDisplay(Xwindow &w);
    void notify(Square &s) override;
    ~GraphicsDisplay();
};

#endif
*/