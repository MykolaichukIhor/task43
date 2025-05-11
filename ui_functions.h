#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "puzzle_solver.h"

using namespace std;

vector<vector<string>> input_matrix_manually() {
    int width, height;
    cout << "Enter matrix width: ";
    cin >> width;
    cout << "Enter matrix height: ";
    cin >> height;
    
    vector<vector<string>> matrix(height, vector<string>(width));
    
    cout << "Enter matrix elements (use '-' for empty, '0' for zero or wall):\n";      
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
    cout << "2. Input puzzle manually\n";
    cout << "3. Exit\n";
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