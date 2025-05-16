#pragma once
#include <vector>
#include <string>
#include "rectangle_wrapper.h"

using namespace std;

/* ---------------------------------------------------------------------[<]-
 Class: Solution
 Synopsis: Represents a solution to the puzzle, containing a sequence of 
           rectangles and the resulting matrix state after applying them.
 ---------------------------------------------------------------------[>]-*/
class Solution {
public:
    vector<RectangleWrapper> rectangles;
    vector<vector<string>> current_matrix;
    
    /* ---------------------------------------------------------------------[<]-
     Function: print
     Synopsis: Prints the solution by displaying all rectangles in sequence,
               separated by arrows to show the order of operations.
    ---------------------------------------------------------------------[>]-*/
    void print() const {
        for (size_t i = 0; i < rectangles.size(); ++i) {
            rectangles[i].print();
            if (i != rectangles.size() - 1) cout << " -> ";
        }
        cout << "\n";
    }
};