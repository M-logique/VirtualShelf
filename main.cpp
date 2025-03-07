#include <iostream>
#include <libtui.h>
#include <Utils.h>
#include <sqlite_modern_cpp.h>
#include <string>
#include <Options.h>

using namespace std;
using namespace sqlite;


int main() 
{
    database db("dbfile.db");

    cout << "Setting up the database" << endl;
    setupDatabase(db);

    while (true) {
        Clear();
        PrintLogo();
        int choice = GetMenuChoice();

        cout << endl;
        switch (choice)
        {
        case 0:
            addBook(db);
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