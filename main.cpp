#include <iostream>
#include <libtui.h>
#include <utils.h>
#include <sqlite_modern_cpp.h>
#include <string>
#include <options.h>
#include <shared.h>
#include <database.h>

using namespace std;


int main(int argc, char* argv[]) 
{


    for (int i = 1; i < argc; ++i) {
        if (string(argv[i]) == "-DISABLE_RGB") {
            toggle_rgb();
            break;  
        }
    }
    GoUpdateRGBState();


    cout << "Setting up the database" << endl;
    registerDatabase("dbfile.db");
    setupTables();
    /*
        "0. Add a new book",
		"1. Show all books",
		"2. Add a new student",
		"3. Borrowing a book",
		"4. Search by book title or author",
		"5. Display a list of borrowed books and the members who have them",
		"6. Exit",
    */

    while (true) {
        Clear();
        GoPrintLogo();
        int choice = GoGetMenuChoice();

        cout << endl;
        switch (choice)
        {
        case 0:
            addBook();
            break;
        case 1:
            showAllBooks();
            break;
        case 2:
            addStudent();
            break;
        case 3:
            borrowABook();
            break;
        case 6:
            exit(0);
            break;
        
        default:
            break;
        }

        
    }
    return 0;
}