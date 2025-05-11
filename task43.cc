#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <cmath>
#include "checking.h"
#include "visualizer.h"

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
            for (int value = 1; value <= num; ++value) {  // Changed from value < num to value <= num
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
        // if (should_stop_search() || !all_solutions.empty()) {
        //     return;
        // }
        // backtrack_calls++;
        
        
        // Check if current solution is complete and valid
        if (isSolutionValid(current)) {
            all_solutions.push_back(current);
            return;
        }
        
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
                    
                    auto configs = generate_possible_rectangles(current.current_matrix, num, x+1, y+1, true);
                    
                    for (const auto& rect : configs) {
                        Solution new_state = current;
                        
                        if (update_matrix_for_rectangle(new_state.current_matrix, rect)) {
                            new_state.rectangles.push_back(rect);
                            backtrack(new_state, process_primes);
                            
                            if (!all_solutions.empty()) {
                                return;
                            }
                        }
                    }
                    return;
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
                    
                    auto configs = generate_possible_rectangles(current.current_matrix, num, x+1, y+1, false);
                    
                    for (const auto& rect : configs) {
                        Solution new_state = current;
                        
                        if (update_matrix_for_rectangle(new_state.current_matrix, rect)) {
                            new_state.rectangles.push_back(rect);
                            backtrack(new_state, false);
                            
                            if (!all_solutions.empty()) {
                                return;
                            }
                        }
                    }
                    return;
                }
            }
        }
    }
};

vector<vector<string>> input_matrix_manually() {
    int width, height;
    cout << "Enter matrix width: ";
    cin >> width;
    cout << "Enter matrix height: ";
    cin >> height;
    
    vector<vector<string>> matrix(height, vector<string>(width));
    
    cout << "Enter matrix elements (use '-' for empty, '0' for zero, '=' for wall):\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << "Element [" << i+1 << "][" << j+1 << "]: ";
            cin >> matrix[i][j];
        }
    }
    
    return matrix;
}

void solve_puzzle_programmatically(const vector<vector<string>>& matrix) {
    PuzzleSolver solver(matrix);
    solver.solve();
    solver.print_solutions();

    if (!solver.get_solutions().empty()) {
        const Solution& solution = solver.get_solutions()[0];
        vector<Rectangle> rectangles;
        for (const auto& wrapper : solution.rectangles) {
            rectangles.push_back(wrapper.rect);
        }

        Visualizer viz(matrix);
        viz.visualize(rectangles);
    }
}

void solve_puzzle_manually(const vector<vector<string>>& matrix) {
    cout << "Manual solving is not implemented yet. Please choose programmatic solving.\n";
}

void show_menu() {
    cout << "=== Puzzle Solver Menu ===\n";
    cout << "1. Select puzzle to solve\n";
    cout << "2. Exit\n";
    cout << "Choose an option: ";
}

void show_puzzle_selection() {
    cout << "\nAvailable puzzles:\n";
    cout << "1. Puzzle 1 (6x7)\n";
    cout << "2. Puzzle 2 (8x8)\n";
    cout << "3. Puzzle 3 (9x8)\n";
    cout << "Choose a puzzle (1-3): ";
}

void show_solving_method() {
    cout << "\nSelect solving method:\n";
    cout << "1. Solve programmatically\n";
    cout << "2. Solve manually (not implemented yet)\n";
    cout << "Choose a method (1-2): ";
}






int main() {

    vector<vector<string>> matrix = {
        {"-", "-", "-", "-", "6", "-", "-"},
        {"-", "-", "-", "24", "-", "-", "-"},
        {"-", "-", "41", "-", "-", "-", "-"},
        {"-", "-", "-", "-", "-", "32", "-"},
        {"-", "-", "-", "-", "30", "-", "-"},
        {"-", "-", "-", "0", "-", "-", "-"}
     };


    vector<vector<string>> matrix2 = {
        { "-", "-", "-", "-", "-", "-", "-", "-"  },
        { "-", "-", "-", "-", "-", "-", "-", "-"  },
        { "-", "-", "43","-", "46" , "-", "-", "-"},
        { "-", "-", "-",  "-" , "-", "-", "-", "-"  },
        { "-", "-", "46", "-", "50" , "-", "-", "-"  },
        { "-", "-" , "-", "-", "-",  "-" , "-", "-"  },
        { "-", "-" , "-", "-", "-",  "-" , "-", "-"  },
        { "-", "-", "-", "-", "-" , "-", "-", "-" }
    };

    vector<vector<string>> matrix3 = {
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

while (true) {
        show_menu();
        int choice;
        cin >> choice;

        if (choice == 3) {
            cout << "Exiting program...\n";
            break;
        } else if (choice == 1) {
            show_puzzle_selection();
            int puzzle_choice;
            cin >> puzzle_choice;

            vector<vector<string>> selected_matrix;
            switch (puzzle_choice) {
                case 1:
                    selected_matrix = matrix;
                    break;
                case 2:
                    selected_matrix = matrix2;
                    break;
                case 3:
                    selected_matrix = matrix3;
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    continue;
            }

            show_solving_method();
            int method_choice;
            cin >> method_choice;

            if (method_choice == 1) {
                solve_puzzle_programmatically(selected_matrix);
            } else if (method_choice == 2) {
                solve_puzzle_manually(selected_matrix);
            } else {
                cout << "Invalid choice. Please try again.\n";
            }
        } else if (choice == 2) {
            vector<vector<string>> manual_matrix = input_matrix_manually();
            
            show_solving_method();
            int method_choice;
            cin >> method_choice;

            if (method_choice == 1) {
                solve_puzzle_programmatically(manual_matrix);
            } else if (method_choice == 2) {
                solve_puzzle_manually(manual_matrix);
            } else {
                cout << "Invalid choice. Please try again.\n";
            }
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
    

    return 0;
}