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
    register_database("dbfile.db");
    setup_tables();
    /*
        "0. Add a new book",
        "1. Show all books",
        "2. Add a new student",
        "3. Borrow a book",
        "4. Search for a book by title or author",
        "5. Display a list of borrowed books and their borrowers",
        "6. Return a borrowed book",
        "7. Exit",
    */

    while (true) {
        Clear();
        GoPrintLogo();
        int choice = GoGetMenuChoice();

        cout << endl;
        switch (choice)
        {
        case 0:
            add_book();
            break;
        case 1:
            show_all_books();
            break;
        case 2:
            add_student();
            break;
        case 3:
            borrow_a_book();
            break;
        case 4:
            search_books();
            break;
        case 5:
            show_borrowings();
            break;
        case 6:
            return_borrowed_book();
            break;
        default:
            exit(0);
            break;
        }

        
    }
    return 0;
}