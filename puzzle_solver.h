#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include "solution.h"
#include "visualizer.h"

using namespace std;



/* ---------------------------------------------------------------------[<]-
Class: PuzzleSolver
Synopsis: Solves rectangle-based puzzles by finding valid configurations of 
           rectangles that cover specified numbers in a matrix. Uses backtracking
           with various optimization strategies.
---------------------------------------------------------------------[>]-*/
class PuzzleSolver {
    int max_attempts = 10000;         // max 10,000 attempts
    int max_backtrack_calls = 10000;  // max 10,000 attempts
    vector<vector<string>> initial_matrix;
    int width, height;
    vector<Solution> all_solutions;
    int backtrack_calls = 0;
    int solution_attempts = 0;
    
    /* ---------------------------------------------------------------------[<]-
    Function: isPrime
    Synopsis: Checks if a number is prime using optimized trial division method.
    ---------------------------------------------------------------------[>]-*/
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
    
    /* ---------------------------------------------------------------------[<]-
    Function: PuzzleSolver (constructor)
    Synopsis: Initializes solver with puzzle matrix and validates cell contents.
    ---------------------------------------------------------------------[>]-*/
    PuzzleSolver(const vector<vector<string>>& m) : initial_matrix(m) {
        for (const auto& row : m) {
            for (const auto& cell : row) {
                if (cell != "-" && cell != "0") {
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
    
    void solve();
    void print_solutions();

private:
    bool should_stop_search();
    bool isSolutionValid(const Solution& solution);
    bool can_place_rectangle(const vector<vector<string>>& matrix, const RectangleWrapper& rect);
    bool update_matrix_for_rectangle(vector<vector<string>>& matrix, const RectangleWrapper& rect);
    vector<RectangleWrapper> generate_possible_rectangles(const vector<vector<string>>& matrix, int num, int x, int y, bool product_only);
    void backtrack(Solution& current, bool process_primes);
    void backtrack_with_guessing(Solution& current);
};