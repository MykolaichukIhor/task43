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






};




#endif  // CHECKING.h