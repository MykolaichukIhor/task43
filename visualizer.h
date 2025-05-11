#ifndef VISUALIZER_H
#define VISUALIZER_H
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "checking.h"

#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"

class Visualizer {
private:
    std::vector<std::vector<std::string>> grid;
    std::vector<std::vector<std::string>> original_values;
    int cell_width = 5;
    int cell_height = 3;
    int width, height;
    int padding = 1; // Додаткові поля навколо
    std::vector<std::string> colors = {
        COLOR_RED, COLOR_GREEN, COLOR_YELLOW,
        COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN
    };



};




#endif