#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "puzzle_solver.h"

using namespace std;

int get_valid_int_input(const string& prompt, int min_val = INT_MIN, int max_val = INT_MAX) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid integer.\n";
        } else if (value < min_val || value > max_val) {
            cout << "Input out of range. Please enter a value between " 
                 << min_val << " and " << max_val << ".\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

vector<vector<string>> input_matrix_manually() {
    int width = get_valid_int_input("Enter matrix width (1-20): ", 1, 20);
    int height = get_valid_int_input("Enter matrix height (1-20): ", 1, 20);
    
    vector<vector<string>> matrix(height, vector<string>(width));
    
    cout << "Enter matrix elements (use -1 for empty, other numbers will be stored as is):\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            while (true) {
                cout << "Element [" << i+1 << "][" << j+1 << "]: ";
                string input;
                cin >> input;
                
                try {
                    int num = stoi(input);
                    if (num == -1) {
                        matrix[i][j] = "-";
                    } else {
                        matrix[i][j] = to_string(num);
                    }
                    break;
                } catch (const invalid_argument&) {
                    cout << "Invalid input. Please enter a valid integer (-1 for empty).\n";
                }
            }
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

int show_menu() {
    cout << "\n=== Puzzle Solver Menu ===\n";
    cout << "1. Select puzzle to solve\n";
    cout << "2. Input puzzle manually\n";
    cout << "3. Exit\n";
    return get_valid_int_input("Choose an option (1-3): ", 1, 3);
}

int show_puzzle_selection() {
    cout << "\n=== Available Puzzles ===\n";
    cout << "1. Puzzle 1 (6x7) - Contains numbers 6, 24, 41, 32, 30, 0\n";
    cout << "2. Puzzle 2 (8x8) - Contains numbers 43, 46, 46, 50\n";
    cout << "3. Puzzle 3 (9x8) - Contains numbers 27, 21, 0, 0, 19, 25, 25, 0, 16, 17\n";
    return get_valid_int_input("Choose a puzzle (1-3): ", 1, 3);
}

int show_solving_method() {
    cout << "\n=== Solving Methods ===\n";
    cout << "1. Solve programmatically (automatic solution)\n";
    cout << "2. Solve manually (not implemented yet)\n";
    return get_valid_int_input("Choose a method (1-2): ", 1, 2);
}