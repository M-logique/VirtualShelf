#include <iostream>
#include <libtui.h>
#include <utils.h>
#include <sqlite_modern_cpp.h>
#include <string>
#include <options.h>

using namespace std;
using namespace sqlite;


int main() 
{
    database db("dbfile.db");

    cout << "Setting up the database" << endl;
    setupDatabase(db);

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
            addBook(db);
            break;
        case 1:
            showAllBooks(db);
            break;
        case 2:
            addStudent(db);
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