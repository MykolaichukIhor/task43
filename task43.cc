#include <iostream>
#include <string>
#include <vector>
#include <checking.h>
using namespace std;

class RectangleWrapper {

    public:
     int value;
     RectangleWrapper(int val = 0) : value(val) {}

     bool isPrime() const {
        if (value <= 1) return false;
        for (int i = 2; i * i <= value; ++i) {
            if (value % i == 0) return false;
        }
        return true;
    }



};


void printMatrix(const vector<vector<string>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << elem << "\t";
        }
        cout << endl;
    }
}


int findMaxNumber(const vector<vector<string>>& matrix) {
    int maxNum = INT_MIN;
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            try {
                int num = stoi(elem);
                if (num > maxNum) {
                    maxNum = num;
                }
            } catch (const invalid_argument&) {
                
                continue;
            }
        }
    }
    return maxNum;
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