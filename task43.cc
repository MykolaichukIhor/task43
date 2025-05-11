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