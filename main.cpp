#include <iostream>
#include <libtui.h>
#include <Utils.h>
#include <sqlite_modern_cpp.h>
#include <string>

using namespace std;
using namespace sqlite;


int main() 
{
    database db("dbfile.db");

    cout << "Setting up the database" << endl;
    setupDatabase(db);
    Clear();
    PrintLogo();
    int choice = GetMenuChoice();


    string n;
    switch (choice)
    {
    case 0:
        n = getString("Enter the name of the book: ");
        cout << 
            "Name of the book: "
            << n 
            << endl;
        break;
    case 6:
        exit(0);
        break;
    
    default:
        break;
    }

    return 0;
}