/* ----------------------------------------------------------------<Header>-
 Name: task43.cc
 Title: Fill the fild with rectangles
 Group: ТВ-41
 Student: Mykolaichuk I.O.
 Written: 2025-05-16
 Revised: 
 Description: On the playing field,
              draw rectangles along the given lines so that no two rectangles have a common angle or side,
              and each number represents the total area of ​​all rectangles containing that number.
              The rectangles can intersect.
 ------------------------------------------------------------------</Header>-*/



#include <iostream>
#include <vector>
#include <string>
#include "ui_functions.h"
#include "puzzle_solver_methods.h"

using namespace std;

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
        int choice = show_menu();

        if (choice == 3) {
            cout << "Exiting program...\n";
            break;
        } else if (choice == 1) {
            int puzzle_choice = show_puzzle_selection();

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

            int method_choice = show_solving_method();

            if (method_choice == 1) {
                solve_puzzle_programmatically(selected_matrix);
            } else if (method_choice == 2) {
                solve_puzzle_manually(selected_matrix);
            }
        } else if (choice == 2) {
            vector<vector<string>> manual_matrix = input_matrix_manually();
            int method_choice = show_solving_method();

            if (method_choice == 1) {
                solve_puzzle_programmatically(manual_matrix);
            } else if (method_choice == 2) {
                solve_puzzle_manually(manual_matrix);
            }
        }
    }
    
    return 0;
}
