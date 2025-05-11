#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
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

public:
    const vector<Solution>& get_solutions() const { return all_solutions; }
    
    PuzzleSolver(const vector<vector<string>>& m) : initial_matrix(m) {
        // checking if the matrix is valid (no unknown chars)
        for (const auto& row : m) {
            for (const auto& cell : row) {
                if (cell != "-" && cell != "0" && cell != "=") {
                    try {
                        int num = stoi(cell);
                        if (num <= 0) {
                            cerr << "Found negative number in the matrix. Abortion... " << cell << endl;
                        }
                    } catch (const invalid_argument&) {
                        cerr << "Found unknown char in the matrix. Abortion..." << cell 
                             << " It can be 0, - or any positive number)" << endl;
                    } catch (const out_of_range&) {
                        cerr << "The number in the matrix is too big! " << cell << endl;
                    }
                }
            }
        }

        height = initial_matrix.size();
        if (height > 0) width = initial_matrix[0].size();
    }

    void solve() {
        Solution current;
        current.current_matrix = initial_matrix;
        backtrack(current, false);
        
        if (all_solutions.empty()) {
            backtrack_with_guessing(current);
        }
        
        cout << "Total backtrack calls: " << backtrack_calls << endl;
        cout << "Total solution attempts: " << solution_attempts << endl;
    }

    void print_solutions() {
        if (all_solutions.empty()) {
            cout << "No solutions found\n";
            return;
        }
        
        cout << "\nFound solution:\n";
        all_solutions[0].print();
    }
private:


bool can_place_rectangle(const vector<vector<string>>& matrix, const RectangleWrapper& rect) {
        Point tl = rect.rect.getTopLeft();
        Point br = rect.rect.getBottomRight();
        
        // Check if rectangle contains any "0" or "="
        for (int y = tl.y; y <= br.y; ++y) {
            for (int x = tl.x; x <= br.x; ++x) {
                string cell = matrix[y-1][x-1];
                if (cell == "0" || cell == "=") {
                    return false;
                }
            }
        }
        return true;
    }


    bool update_matrix_for_rectangle(vector<vector<string>>& matrix, const RectangleWrapper& rect) {
        Point tl = rect.rect.getTopLeft();
        Point br = rect.rect.getBottomRight();
        
        // First check if update would cause any negative numbers
        for (int y = tl.y; y <= br.y; ++y) {
            for (int x = tl.x; x <= br.x; ++x) {
                string& cell = matrix[y-1][x-1];
                if (cell != "-" && cell != "0" && cell != "=") {
                    int num = stoi(cell);
                    if (num - rect.value < 0) {
                        return false;
                    }
                }
            }
        }
        
        // Apply the update
        for (int y = tl.y; y <= br.y; ++y) {
            for (int x = tl.x; x <= br.x; ++x) {
                string& cell = matrix[y-1][x-1];
                if (cell != "-" && cell != "0" && cell != "=") {
                    int num = stoi(cell);
                    cell = to_string(num - rect.value);
                }
            }
        }
        return true;
    } 




bool should_stop_search() {


    if (solution_attempts >= max_attempts) {

        cout << "Max attempts reached. Stopping search\n";
        return true;
    }
    if (backtrack_calls >= max_backtrack_calls) {
        cout << "Max backtrack calls reached, stopping search\n";
        return true;
    }

    return false;
}
    bool isSolutionValid(const Solution& solution) {
        solution_attempts++;
        
        // Check rectangles don't touch
        for (size_t i = 0; i < solution.rectangles.size(); ++i) {
            for (size_t j = i + 1; j < solution.rectangles.size(); ++j) {
                if (hasCommonSideOrCorner(solution.rectangles[i].rect, solution.rectangles[j].rect)) {
                    return false;
                }
            }
        }
        
        // Check all numbers are zero
        for (const auto& row : solution.current_matrix) {
            for (const auto& cell : row) {
                if (cell != "-" && cell != "0" && cell != "=") {
                    if (stoi(cell) != 0) return false;
                }
            }
        }
        
        return true;
    }

vector<RectangleWrapper> generate_possible_rectangles(const vector<vector<string>>& matrix, int num, int x, int y, bool product_only) {
        vector<RectangleWrapper> configs;
        
        if (product_only) {
            // Only consider rectangles where area is exactly the number (product decomposition)
            for (int w = 1; w <= num; ++w) {
                if (num % w == 0) {
                    int h = num / w;
                    if (w <= width && h <= height) {
                        // Generate all possible rectangles with these dimensions containing (x,y)
                        for (int startY = max(1, y - h + 1); startY <= min(height - h + 1, y); ++startY) {
                            for (int startX = max(1, x - w + 1); startX <= min(width - w + 1, x); ++startX) {
                                int endX = startX + w - 1;
                                int endY = startY + h - 1;
                                
                                RectangleWrapper rect(num, startX, startY, endX, endY);
                                if (can_place_rectangle(matrix, rect)) {
                                    configs.push_back(rect);
                                }
                            }
                        }
                    }
                }
            }
        } else {
            // Consider all possible rectangle values that could be subtracted (guessing approach)
            for (int value = 1; value <= num; ++value) {
                if (isPrime(value) && value != num) continue; // Skip primes (except when value == num)
                
                // Find all possible rectangle dimensions for this value
                for (int w = 1; w <= value; ++w) {
                    if (value % w == 0) {
                        int h = value / w;
                        if (w <= width && h <= height) {
                            // Generate all possible rectangles with these dimensions containing (x,y)
                            for (int startY = max(1, y - h + 1); startY <= min(height - h + 1, y); ++startY) {
                                for (int startX = max(1, x - w + 1); startX <= min(width - w + 1, x); ++startX) {
                                    int endX = startX + w - 1;
                                    int endY = startY + h - 1;
                                    
                                    RectangleWrapper rect(value, startX, startY, endX, endY);
                                    if (can_place_rectangle(matrix, rect)) {
                                        configs.push_back(rect);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return configs;
    }




    void backtrack(Solution& current, bool process_primes) {
        // Find the next number to process
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                string cell = current.current_matrix[y][x];
                if (cell != "-" && cell != "0" && cell != "=") {
                    int num = stoi(cell);
                    if (num == 0) continue;
                    
                    // Skip primes in first pass
                    if (!process_primes && isPrime(num)) {
                        continue;
                    }
                }
            }
        }

        // If no numbers found in first pass, try again with primes
        if (!process_primes) {
            backtrack(current, true);
        }
    }

    void backtrack_with_guessing(Solution& current) {
        // Find the first number to try guessing approach on
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                string cell = current.current_matrix[y][x];
                if (cell != "-" && cell != "0" && cell != "=") {
                    int num = stoi(cell);
                    if (num == 0) continue;
                }
            }
        }
    }
}; // PuzzleSolver end

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