#include <iostream>
#include <string>
#include <vector>
#include "checking.h"

using namespace std;

class Visualizer {
private:
    vector<vector<string>> grid;
    vector<vector<string>> original_values;
    int width = 0;
    int height = 0;
    const int cell_width = 5;
    const int cell_height = 3;
    const int padding = 1;  // Additional space around the main grid
    
    // ANSI color codes for rectangles
    const vector<string> colors = {
        "\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m"
    };
    const string COLOR_RESET = "\033[0m";

    void prepareGrid(const vector<vector<string>>& matrix) {
        height = matrix.size();
        width = height > 0 ? matrix[0].size() : 0;
        
        original_values = matrix;
        
        // Calculate grid size including padding
        int grid_width = width * cell_width + 2 * padding * cell_width;
        int grid_height = height * cell_height + 2 * padding * cell_height;
        
        grid.resize(grid_height, vector<string>(grid_width, " "));

        // Fill main grid area (shifted by padding cells)
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                string val = matrix[y][x];
                int grid_y = (y + padding) * cell_height + cell_height / 2;
                int grid_x = (x + padding) * cell_width + (cell_width - val.length()) / 2;
                
                for (size_t i = 0; i < val.length(); i++) {
                    if (grid_y < grid.size() && grid_x + i < grid[grid_y].size()) {
                        grid[grid_y][grid_x + i] = val.substr(i, 1);
                    }
                }
            }
        }
    }

    void drawRectangle(const Rectangle& rect, const string& color) {
        Point tl = rect.getTopLeft();
        Point br = rect.getBottomRight();
        
        // Calculate coordinates including padding
        int left = (tl.x - 1 + padding) * cell_width;
        int right = (br.x - 1 + padding) * cell_width + (cell_width - 1);
        int top = (tl.y - 1 + padding) * cell_height;
        int bottom = (br.y - 1 + padding) * cell_height + (cell_height - 1);

        // Draw rectangle (may extend beyond main grid area)
        for (int x = left; x <= right; x++) {
            if (top >= 0 && top < grid.size() && x >= 0 && x < grid[top].size()) 
                grid[top][x] = color + "-" + COLOR_RESET;
            if (bottom >= 0 && bottom < grid.size() && x >= 0 && x < grid[bottom].size()) 
                grid[bottom][x] = color + "-" + COLOR_RESET;
        }

        for (int y = top; y <= bottom; y++) {
            if (y >= 0 && y < grid.size()) {
                if (left >= 0 && left < grid[y].size())
                    grid[y][left] = color + "|" + COLOR_RESET;
                if (right >= 0 && right < grid[y].size())
                    grid[y][right] = color + "|" + COLOR_RESET;
            }
        }

        // Draw corners
        if (top >= 0 && top < grid.size()) {
            if (left >= 0 && left < grid[top].size())
                grid[top][left] = color + "+" + COLOR_RESET;
            if (right >= 0 && right < grid[top].size())
                grid[top][right] = color + "+" + COLOR_RESET;
        }
        if (bottom >= 0 && bottom < grid.size()) {
            if (left >= 0 && left < grid[bottom].size())
                grid[bottom][left] = color + "+" + COLOR_RESET;
            if (right >= 0 && right < grid[bottom].size())
                grid[bottom][right] = color + "+" + COLOR_RESET;
        }
    }

    void addBorderAndCoordinates() {
        // Add border around entire grid (including padding)
        for (int x = 0; x < grid[0].size(); x++) {
            grid[0][x] = "-";
            grid[grid.size()-1][x] = "-";
        }
        for (int y = 0; y < grid.size(); y++) {
            grid[y][0] = "|";
            grid[y][grid[0].size()-1] = "|";
        }
        // Draw corners
        grid[0][0] = "+";
        grid[0][grid[0].size()-1] = "+";
        grid[grid.size()-1][0] = "+";
        grid[grid.size()-1][grid[0].size()-1] = "+";

        // Add coordinates for main grid
        for (int x = 0; x < width; x++) {
            string coord = to_string(x+1);
            int pos = (x + padding) * cell_width + (cell_width - coord.length()) / 2;
            if (pos >= 0 && pos + coord.length() < grid[0].size()) {
                for (size_t i = 0; i < coord.length(); i++) {
                    grid[0][pos + i] = coord.substr(i, 1);
                }
            }
        }

        for (int y = 0; y < height; y++) {
            string coord = to_string(y+1);
            int pos = (y + padding) * cell_height + cell_height / 2;
            if (pos >= 0 && pos < grid.size() && 0 < grid[pos].size()) {
                grid[pos][0] = coord;
            }
        }
    }

public:
    Visualizer(const vector<vector<string>>& matrix) {
        prepareGrid(matrix);
    }

    void visualize(const vector<Rectangle>& rectangles) {
        cout << "\nVisualization (with extended area):\n";
        
        // Draw all rectangles
        for (size_t i = 0; i < rectangles.size(); i++) {
            drawRectangle(rectangles[i], colors[i%colors.size()]);
        }

        // Add border and coordinates
        addBorderAndCoordinates();

        // Print the final grid
        for (const auto& row : grid) {
            for (const string& cell : row) {
                cout << cell;
            }
            cout << "\n";
        }
    }
};