#pragma once
#include <iostream>
#include <string>
#include "checking.h"

using namespace std;

/* ---------------------------------------------------------------------[<]-
 Class: RectangleWrapper
 Synopsis: Wraps a Rectangle with additional value information and provides
           printing functionality. Connects a rectangle with its numeric value.
 ---------------------------------------------------------------------[>]-*/
class RectangleWrapper {
public:
    int value;
    Rectangle rect;

    /* ---------------------------------------------------------------------[<]-
     Function: RectangleWrapper (constructor)
     Synopsis: Creates a new RectangleWrapper with specified value and coordinates.
               Initializes the contained Rectangle with given corner points.
    ---------------------------------------------------------------------[>]-*/
    RectangleWrapper(int val, int x1, int y1, int x2, int y2)
        : value(val), 
          rect(Point{x1, y1, true, true}, Point{x2, y2, false, false}) {}

    /* ---------------------------------------------------------------------[<]-
     Function: print
     Synopsis: Prints the rectangle's details including its value and coordinates
               in a human-readable format.
    ---------------------------------------------------------------------[>]-*/
    void print() const {
        Point tl = rect.getTopLeft();
        Point br = rect.getBottomRight();
        cout << "Rectangle (area " << value << "): [(" 
             << tl.x << "," << tl.y 
             << ")-(" << br.x << "," << br.y << ")]";
    }
};