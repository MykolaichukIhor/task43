#include <iostream>
#include <string>
#include <vector>
#include "checking.h"
using namespace std;

class RectangleWrapper {

    public:
     int value;
     Rectangle rect;

    RectangleWrapper(int val, int x1, int y1, int x2, int y2)
        : value(val), 
          rect(Point{x1, y1, true, true}, Point{x2, y2, false, false}) {}


          void print() const {
        Point tl = rect.getTopLeft();
        Point br = rect.getBottomRight();
        cout << "Rectangle (area " << value << "): [(" 
             << tl.x << "," << tl.y 
             << ")-(" << br.x << "," << br.y << ")]";
    }



};


class Solution {




};


class PuzzleSolver {
int max_attempts = 100000; // 10,000 attempts
    int max_backtrack_calls = 100000; // 10,000 backtracks calls max
    vector<vector<string>> initial_matrix;
    int width, height;
    vector<Solution> all_solutions;
    int backtrack_calls = 0;
    int solution_attempts = 0;

    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }


};


void backtrack() {



}



void backtrack_with_guessing(){




}


int main() {

    vector<vector<string>> matrix1 =  {
    { "-", "-", "-", "-", "-", "-", "-", "-"  },
        { "-", "-", "-", "-", "-", "-", "-", "-"  },
        { "-", "-", "43","-", "46" , "-", "-", "-"},
        { "-", "-", "-",  "-" , "-", "-", "-", "-"  },
        { "-", "-", "46", "-", "50" , "-", "-", "-"  },
        { "-", "-" , "-", "-", "-",  "-" , "-", "-"  },
        { "-", "-" , "-", "-", "-",  "-" , "-", "-"  },
        { "-", "-", "-", "-", "-" , "-", "-", "-" }
     };

     vector<vector<string>> matrix2 = {
         { "-", "-", "-", "-", "-", "-", "-", "-"  },
        { "-", "-", "-", "-", "-", "27", "-", "-"  },
        { "-", "-", "21","-", "-" , "-", "-", "-"},
        { "-", "0", "-",  "0" , "-", "-", "-", "-"  },
        { "-", "-", "19", "-", "25" , "-", "25", "-"  },
        { "-", "-" , "-", "-", "-",  "0" , "-", "-"  },
        { "-", "-" , "-", "-", "-",  "-" , "-", "-"  },
        { "-", "-", "16", "-", "-" , "-", "17", "-" },
        { "-", "-", "-", "-", "-", "-", "-", "-",  }
    };

cout << "Testing 1" << endl;


    return 0;
}