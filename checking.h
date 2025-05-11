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



};




#endif  // CHECKING.h