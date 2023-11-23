#ifndef __WINDOW_H__
#define __WINDOW_H__
//#include <X11/Xlib.h>     ?GIVING ERROR?
#include <iostream>
#include <string>

class Xwindow {
  //Display *d;      ?GIVING ERROR?
  //Window w;        ?GIVING ERROR?
  int s;
  //GC gc;           ?GIVING ERROR?
  unsigned long colours[10];

 public:
  Xwindow(int width=500, int height=500);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  enum {White=0, Black, Red, Green, Blue}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg);

};

#endif