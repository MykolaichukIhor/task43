#ifndef CHECKING_H
#define CHECKING_H

struct Point {
    int x, y;
    bool isTop;    // true для верхніх точок, false для нижніх
    bool isLeft;   // true для лівих точок, false для правих
};


class Rectangle {

private: 
 Point topLeft, bottomRight;
 Point topRight, bottomLeft;


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
    Rectangle(Point tl, Point br) : topLeft(tl), bottomRight(br) {
        topLeft.isTop = true;
        topLeft.isLeft = true;
        bottomRight.isTop = false;
        bottomRight.isLeft = false;
        calculateOtherPoints();
    }

    Point getTopLeft() const { return topLeft; }
    Point getTopRight() const { return topRight; }
    Point getBottomLeft() const { return bottomLeft; }
    Point getBottomRight() const { return bottomRight; }

bool isPointOnSide(Point p) const {
        // Верхня сторона (тільки для точок з isTop = true)
        if (p.y == topLeft.y && p.isTop && 
            p.x >= topLeft.x && p.x <= topRight.x) return true;
            
        // Нижня сторона (тільки для точок з isTop = false)
        if (p.y == bottomLeft.y && !p.isTop && 
            p.x >= bottomLeft.x && p.x <= bottomRight.x) return true;
            
        // Ліва сторона (тільки для точок з isLeft = true)
        if (p.x == topLeft.x && p.isLeft && 
            p.y >= bottomLeft.y && p.y <= topLeft.y) return true;
            
        // Права сторона (тільки для точок з isLeft = false)
        if (p.x == topRight.x && !p.isLeft && 
            p.y >= bottomRight.y && p.y <= topRight.y) return true;
            
        return false;
    }

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


bool isCloseEnoughToShareSide(const Rectangle& rect1, const Rectangle& rect2) {
    Point a1 = rect1.getTopLeft();
    Point a2 = rect1.getBottomRight();
    Point b1 = rect2.getTopLeft();
    Point b2 = rect2.getBottomRight();

    // Вертикальне прилягання
    if ((a2.x + 1 == b1.x || b2.x + 1 == a1.x) &&
        !(a2.y < b1.y || b2.y < a1.y)) {
        return true;
    }

    // Горизонтальне прилягання
    if ((a1.y == b2.y + 1 || b1.y == a2.y + 1) &&
        !(a2.x < b1.x || b2.x < a1.x)) {
        return true;
    }

    return false;
}





};




#endif  // CHECKING.h