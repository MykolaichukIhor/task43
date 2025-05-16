#pragma once
#include "puzzle_solver.h"

/* ---------------------------------------------------------------------[<]-
Function: should_stop_search
Synopsis: Checks if search should stop based on maximum attempts or backtrack calls.
---------------------------------------------------------------------[>]-*/
bool PuzzleSolver::should_stop_search() {
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

/* ---------------------------------------------------------------------[<]-
Function: isSolutionValid
Synopsis: Validates if current solution is correct by checking rectangle 
           placements and matrix state.
---------------------------------------------------------------------[>]-*/
bool PuzzleSolver::isSolutionValid(const Solution& solution) {
    solution_attempts++;
    
    for (size_t i = 0; i < solution.rectangles.size(); ++i) {
        for (size_t j = i + 1; j < solution.rectangles.size(); ++j) {
            if (hasCommonSideOrCorner(solution.rectangles[i].rect, solution.rectangles[j].rect)) {
                return false;
            }
        }
    }
    
    for (const auto& row : solution.current_matrix) {
        for (const auto& cell : row) {
            if (cell != "-" && cell != "0" && cell != "=") {
                if (stoi(cell) != 0) return false;
            }
        }
    }
    
    return true;
}

/* ---------------------------------------------------------------------[<]-
Function: can_place_rectangle
Synopsis: Checks if rectangle can be placed at specified position without 
           overlapping invalid cells.
---------------------------------------------------------------------[>]-*/
bool PuzzleSolver::can_place_rectangle(const vector<vector<string>>& matrix, const RectangleWrapper& rect) {
    Point tl = rect.rect.getTopLeft();
    Point br = rect.rect.getBottomRight();
    
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

/* ---------------------------------------------------------------------[<]-
Function: update_matrix_for_rectangle
Synopsis: Updates matrix state by subtracting rectangle value from covered cells.
---------------------------------------------------------------------[>]-*/
bool PuzzleSolver::update_matrix_for_rectangle(vector<vector<string>>& matrix, const RectangleWrapper& rect) {
    Point tl = rect.rect.getTopLeft();
    Point br = rect.rect.getBottomRight();
    
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

/* ---------------------------------------------------------------------[<]-
Function: generate_possible_rectangles
Synopsis: Generates all valid rectangle configurations for given number and position.
---------------------------------------------------------------------[>]-*/
vector<RectangleWrapper> PuzzleSolver::generate_possible_rectangles(const vector<vector<string>>& matrix, int num, int x, int y, bool product_only) {
    vector<RectangleWrapper> configs;
    
    if (product_only) {
        for (int w = 1; w <= num; ++w) {
            if (num % w == 0) {
                int h = num / w;
                if (w <= width && h <= height) {
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
        for (int value = 1; value <= num; ++value) {
            if (isPrime(value) && value != num) continue;
            
            for (int w = 1; w <= value; ++w) {
                if (value % w == 0) {
                    int h = value / w;
                    if (w <= width && h <= height) {
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

/* ---------------------------------------------------------------------[<]-
Function: backtrack
Synopsis: Recursive backtracking algorithm to find valid rectangle placements.
---------------------------------------------------------------------[>]-*/
void PuzzleSolver::backtrack(Solution& current, bool process_primes) {
    if (should_stop_search() || !all_solutions.empty()) {
        return;
    }
    backtrack_calls++;
    
    if (isSolutionValid(current)) {
        all_solutions.push_back(current);
        return;
    }
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            string cell = current.current_matrix[y][x];
            if (cell != "-" && cell != "0" && cell != "=") {
                int num = stoi(cell);
                if (num == 0) continue;
                
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
    
    if (!process_primes) {
        backtrack(current, true);
    }
}

/* ---------------------------------------------------------------------[<]-
Function: backtrack_with_guessing
Synopsis: Alternative backtracking approach that tries more rectangle configurations.
---------------------------------------------------------------------[>]-*/
void PuzzleSolver::backtrack_with_guessing(Solution& current) {
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

/* ---------------------------------------------------------------------[<]-
Function: solve
Synopsis: Main solving method that initiates the backtracking process.
---------------------------------------------------------------------[>]-*/
void PuzzleSolver::solve() {
    Solution current;
    current.current_matrix = initial_matrix;
    backtrack(current, false);
    
    if (all_solutions.empty()) {
        backtrack_with_guessing(current);
    }
    
    cout << "Total backtrack calls: " << backtrack_calls << endl;
    cout << "Total solution attempts: " << solution_attempts << endl;
}

/* ---------------------------------------------------------------------[<]-
Function: print_solutions
Synopsis: Prints found solutions or message if no solutions were found.
---------------------------------------------------------------------[>]-*/
void PuzzleSolver::print_solutions() {
    if (all_solutions.empty()) {
        cout << "No solutions found\n";
        return;
    }
    
    cout << "\nFound solution:\n";
    all_solutions[0].print();
}