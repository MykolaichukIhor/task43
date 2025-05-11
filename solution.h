#pragma once
#include <vector>
#include <string>
#include "rectangle_wrapper.h"

using namespace std;

class Solution {
public:
    vector<RectangleWrapper> rectangles;
    vector<vector<string>> current_matrix;
    
    void print() const {
        for (size_t i = 0; i < rectangles.size(); ++i) {

            rectangles[i].print();
            if (i != rectangles.size() - 1) cout << " -> ";
        }
        cout << "\n";
    }
};