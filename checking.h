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

bool hasCommonSideOrCorner(const Rectangle& rect1, const Rectangle& rect2) {
    // 1. Перевірка на спільні кути
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

    // 2. Перевірка на кути, що лежать на сторонах
    if (rect2.isPointOnSide(rect1.getTopLeft())) return true;
    if (rect2.isPointOnSide(rect1.getTopRight())) return true;
    if (rect2.isPointOnSide(rect1.getBottomLeft())) return true;
    if (rect2.isPointOnSide(rect1.getBottomRight())) return true;
    
    if (rect1.isPointOnSide(rect2.getTopLeft())) return true;
    if (rect1.isPointOnSide(rect2.getTopRight())) return true;
    if (rect1.isPointOnSide(rect2.getBottomLeft())) return true;
    if (rect1.isPointOnSide(rect2.getBottomRight())) return true;

    // 3. Перевірка на спільні сторони
    if (rect1.hasCommonSide(rect2)) return true;

    // 4. Перевірка на горизонтальне/вертикальне прилягання на відстані 1
    if (isCloseEnoughToShareSide(rect1, rect2)) return true;

    // 5. Перевірка на діагональне торкання кутів (відстань 1 по діагоналі)
    Point r1_tl = rect1.getTopLeft();
    Point r1_tr = rect1.getTopRight();
    Point r1_bl = rect1.getBottomLeft();
    Point r1_br = rect1.getBottomRight();
    
    Point r2_tl = rect2.getTopLeft();
    Point r2_tr = rect2.getTopRight();
    Point r2_bl = rect2.getBottomLeft();
    Point r2_br = rect2.getBottomRight();
    
    // rect1 нижній правий торкається rect2 верхнього лівого
    if (r1_br.x == r2_tl.x - 1 && r1_br.y == r2_tl.y - 1) return true;
    // rect1 нижній лівий торкається rect2 верхнього правого
    if (r1_bl.x == r2_tr.x + 1 && r1_bl.y == r2_tr.y - 1) return true;
    // rect1 верхній правий торкається rect2 нижнього лівого
    if (r1_tr.x == r2_bl.x - 1 && r1_tr.y == r2_bl.y + 1) return true;
    // rect1 верхній лівий торкається rect2 нижнього правого
    if (r1_tl.x == r2_br.x + 1 && r1_tl.y == r2_br.y + 1) return true;
    
    // Те ж саме для зворотних випадків
    // rect2 нижній правий торкається rect1 верхнього лівого
    if (r2_br.x == r1_tl.x - 1 && r2_br.y == r1_tl.y - 1) return true;
    // rect2 нижній лівий торкається rect1 верхнього правого
    if (r2_bl.x == r1_tr.x + 1 && r2_bl.y == r1_tr.y - 1) return true;
    // rect2 верхній правий торкається rect1 нижнього лівого
    if (r2_tr.x == r1_bl.x - 1 && r2_tr.y == r1_bl.y + 1) return true;
    // rect2 верхній лівий торкається rect1 нижнього правого
    if (r2_tl.x == r1_br.x + 1 && r2_tl.y == r1_br.y + 1) return true;

    return false;
}





};




#endif  // CHECKING.h