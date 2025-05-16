#ifndef CHECKING_H
#define CHECKING_H

#include <vector>
#include <iostream>

/* ---------------------------------------------------------------------[<]-
Struct: Point
Synopsis: Represents a point with coordinates and flags indicating its position
           (top/bottom, left/right) in a rectangle.
---------------------------------------------------------------------[>]-*/
struct Point {
    int x, y;
    bool isTop;    // true for top points, false for bottom
    bool isLeft;   // true for left points, false for right
};

/* ---------------------------------------------------------------------[<]-
Class: Rectangle
Synopsis: Represents a rectangle defined by its corner points, with methods
           for geometric relationships and side detection.
---------------------------------------------------------------------[>]-*/
class Rectangle {
private:
    Point topLeft, bottomRight;
    Point topRight, bottomLeft;

    /* ---------------------------------------------------------------------[<]-
    Function: calculateOtherPoints
    Synopsis: Calculates top-right and bottom-left points based on top-left
               and bottom-right points.
    ---------------------------------------------------------------------[>]-*/
    void calculateOtherPoints() {
        topRight.x = bottomRight.x;
        topRight.y = topLeft.y;
        topRight.isTop = true;
        topRight.isLeft = false;
        
        bottomLeft.x = topLeft.x;
        bottomLeft.y = bottomRight.y;
        bottomLeft.isTop = false;
        bottomLeft.isLeft = true;
    }

public:
    /* ---------------------------------------------------------------------[<]-
    Function: Rectangle (constructor)
    Synopsis: Initializes rectangle with top-left and bottom-right points,
               calculating other corners.
    ---------------------------------------------------------------------[>]-*/
    Rectangle(Point tl, Point br) : topLeft(tl), bottomRight(br) {
        topLeft.isTop = true;
        topLeft.isLeft = true;
        bottomRight.isTop = false;
        bottomRight.isLeft = false;
        calculateOtherPoints();
    }

    // Accessor methods
    Point getTopLeft() const { return topLeft; }
    Point getTopRight() const { return topRight; }
    Point getBottomLeft() const { return bottomLeft; }
    Point getBottomRight() const { return bottomRight; }

    /* ---------------------------------------------------------------------[<]-
    Function: isPointOnSide
    Synopsis: Checks if a point lies exactly on any side of the rectangle.
    ---------------------------------------------------------------------[>]-*/
    bool isPointOnSide(Point p) const {
        // Top side (only for points with isTop = true)
        if (p.y == topLeft.y && p.isTop && 
            p.x >= topLeft.x && p.x <= topRight.x) return true;
            
        // Bottom side (only for points with isTop = false)
        if (p.y == bottomLeft.y && !p.isTop && 
            p.x >= bottomLeft.x && p.x <= bottomRight.x) return true;
            
        // Left side (only for points with isLeft = true)
        if (p.x == topLeft.x && p.isLeft && 
            p.y >= bottomLeft.y && p.y <= topLeft.y) return true;
            
        // Right side (only for points with isLeft = false)
        if (p.x == topRight.x && !p.isLeft && 
            p.y >= bottomRight.y && p.y <= topRight.y) return true;
            
        return false;
    }

    /* ---------------------------------------------------------------------[<]-
    Function: hasCommonSide
    Synopsis: Determines if two rectangles share a common side (adjacent edges).
    ---------------------------------------------------------------------[>]-*/
    bool hasCommonSide(const Rectangle& other) const {
        if (topLeft.y == other.getTopLeft().y &&
            ((topLeft.x >= other.getTopLeft().x && topLeft.x <= other.getTopRight().x) ||
             (topRight.x >= other.getTopLeft().x && topRight.x <= other.getTopRight().x) ||
             (other.getTopLeft().x >= topLeft.x && other.getTopLeft().x <= topRight.x))) {
            return true;
        }

        if (bottomLeft.y == other.getBottomLeft().y &&
            ((bottomLeft.x >= other.getBottomLeft().x && bottomLeft.x <= other.getBottomRight().x) ||
             (bottomRight.x >= other.getBottomLeft().x && bottomRight.x <= other.getBottomRight().x) ||
             (other.getBottomLeft().x >= bottomLeft.x && other.getBottomLeft().x <= bottomRight.x))) {
            return true;
        }

        if (topLeft.x == other.getTopLeft().x &&
            ((topLeft.y >= other.getBottomLeft().y && topLeft.y <= other.getTopLeft().y) ||
             (bottomLeft.y >= other.getBottomLeft().y && bottomLeft.y <= other.getTopLeft().y) ||

             (other.getTopLeft().y >= bottomLeft.y && other.getTopLeft().y <= topLeft.y) ||
            
             (other.getTopLeft().y <= topLeft.y && topLeft.y <= other.getBottomLeft().y )   ||
             (bottomLeft.y >= other.getBottomLeft().y &&  other.getBottomLeft().y >= topLeft.y) ||
             (bottomLeft.y >= other.getTopLeft().y &&  other.getTopLeft().y >= topLeft.y)       )  )
              {
            return true;
        }

        if (topRight.x == other.getTopRight().x &&
            ((topRight.y >= other.getBottomRight().y && topRight.y <= other.getTopRight().y) ||
             (bottomRight.y >= other.getBottomRight().y && topRight.y >= other.getBottomRight().y) ||
             (other.getTopRight().y >= bottomRight.y && other.getTopRight().y <= topRight.y) ||
            
             (other.getTopRight().y <= topRight.y &&  topRight.y <= other.getBottomRight().y) ||  
             (other.getBottomRight().y >= bottomRight.y &&  bottomRight.y >= other.getTopRight().y)  ||
             (bottomRight.y >= other.getBottomRight().y &&  other.getBottomRight().y >= topRight.y) ||
             (bottomRight.y >= other.getTopRight().y &&  other.getTopRight().y >= topRight.y) )) {
            return true;
        }

        return false;
    }
};

/* ---------------------------------------------------------------------[<]-
Function: isCloseEnoughToShareSide
Synopsis: Checks if two rectangles are adjacent (within 1 unit distance).
---------------------------------------------------------------------[>]-*/
bool isCloseEnoughToShareSide(const Rectangle& rect1, const Rectangle& rect2) {
    Point a1 = rect1.getTopLeft();
    Point a2 = rect1.getBottomRight();
    Point b1 = rect2.getTopLeft();
    Point b2 = rect2.getBottomRight();

    // Vertical adjacency
    if ((a2.x + 1 == b1.x || b2.x + 1 == a1.x) &&
        !(a2.y < b1.y || b2.y < a1.y)) {
        return true;
    }

    // Horizontal adjacency
    if ((a1.y == b2.y + 1 || b1.y == a2.y + 1) &&
        !(a2.x < b1.x || b2.x < a1.x)) {
        return true;
    }

    return false;
}

/* ---------------------------------------------------------------------[<]-
Function: hasCommonSideOrCorner
Synopsis: Comprehensive check for any geometric relationship between rectangles
           (shared sides, corners, adjacency, or diagonal contact).
---------------------------------------------------------------------[>]-*/
bool hasCommonSideOrCorner(const Rectangle& rect1, const Rectangle& rect2) {
    // 1. Check for shared corners
    if (rect1.getTopLeft().x == rect2.getTopLeft().x && rect1.getTopLeft().y == rect2.getTopLeft().y) return true;
    if (rect1.getTopLeft().x == rect2.getTopRight().x && rect1.getTopLeft().y == rect2.getTopRight().y) return true;
    if (rect1.getTopLeft().x == rect2.getBottomLeft().x && rect1.getTopLeft().y == rect2.getBottomLeft().y) return true;
    
    if (rect1.getTopRight().x == rect2.getTopLeft().x && rect1.getTopRight().y == rect2.getTopLeft().y) return true;
    if (rect1.getTopRight().x == rect2.getTopRight().x && rect1.getTopRight().y == rect2.getTopRight().y) return true;
    if (rect1.getTopRight().x == rect2.getBottomRight().x && rect1.getTopRight().y == rect2.getBottomRight().y) return true;
    
    if (rect1.getBottomLeft().x == rect2.getTopLeft().x && rect1.getBottomLeft().y == rect2.getTopLeft().y) return true;
    if (rect1.getBottomLeft().x == rect2.getBottomLeft().x && rect1.getBottomLeft().y == rect2.getBottomLeft().y) return true;
    if (rect1.getBottomLeft().x == rect2.getBottomRight().x && rect1.getBottomLeft().y == rect2.getBottomRight().y) return true;
    
    if (rect1.getBottomRight().x == rect2.getTopRight().x && rect1.getBottomRight().y == rect2.getTopRight().y) return true;
    if (rect1.getBottomRight().x == rect2.getBottomLeft().x && rect1.getBottomRight().y == rect2.getBottomLeft().y) return true;
    if (rect1.getBottomRight().x == rect2.getBottomRight().x && rect1.getBottomRight().y == rect2.getBottomRight().y) return true;

    // 2. Check for corners on sides
    if (rect2.isPointOnSide(rect1.getTopLeft())) return true;
    if (rect2.isPointOnSide(rect1.getTopRight())) return true;
    if (rect2.isPointOnSide(rect1.getBottomLeft())) return true;
    if (rect2.isPointOnSide(rect1.getBottomRight())) return true;
    
    if (rect1.isPointOnSide(rect2.getTopLeft())) return true;
    if (rect1.isPointOnSide(rect2.getTopRight())) return true;
    if (rect1.isPointOnSide(rect2.getBottomLeft())) return true;
    if (rect1.isPointOnSide(rect2.getBottomRight())) return true;

    // 3. Check for shared sides
    if (rect1.hasCommonSide(rect2)) return true;

    // 4. Check for horizontal/vertical adjacency (1 unit distance)
    if (isCloseEnoughToShareSide(rect1, rect2)) return true;

    // 5. Check for diagonal corner contact (1 unit diagonal distance)
    Point r1_tl = rect1.getTopLeft();
    Point r1_tr = rect1.getTopRight();
    Point r1_bl = rect1.getBottomLeft();
    Point r1_br = rect1.getBottomRight();
    
    Point r2_tl = rect2.getTopLeft();
    Point r2_tr = rect2.getTopRight();
    Point r2_bl = rect2.getBottomLeft();
    Point r2_br = rect2.getBottomRight();
    
    // rect1 bottom right touches rect2 top left
    if (r1_br.x == r2_tl.x - 1 && r1_br.y == r2_tl.y - 1) return true;
    // rect1 bottom left touches rect2 top right
    if (r1_bl.x == r2_tr.x + 1 && r1_bl.y == r2_tr.y - 1) return true;
    // rect1 top right touches rect2 bottom left
    if (r1_tr.x == r2_bl.x - 1 && r1_tr.y == r2_bl.y + 1) return true;
    // rect1 top left touches rect2 bottom right
    if (r1_tl.x == r2_br.x + 1 && r1_tl.y == r2_br.y + 1) return true;
    
    // Same checks for reverse cases
    // rect2 bottom right touches rect1 top left
    if (r2_br.x == r1_tl.x - 1 && r2_br.y == r1_tl.y - 1) return true;
    // rect2 bottom left touches rect1 top right
    if (r2_bl.x == r1_tr.x + 1 && r2_bl.y == r1_tr.y - 1) return true;
    // rect2 top right touches rect1 bottom left
    if (r2_tr.x == r1_bl.x - 1 && r2_tr.y == r1_bl.y + 1) return true;
    // rect2 top left touches rect1 bottom right
    if (r2_tl.x == r1_br.x + 1 && r2_tl.y == r1_br.y + 1) return true;

    return false;
}

#endif // CHECKING_H