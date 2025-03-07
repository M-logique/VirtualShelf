#include <cstdlib>
#include <sqlite_modern_cpp.h>
#include <Utils.h>
#include <libtui.h>


using namespace std;
using namespace sqlite;



void Clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void setupDatabase(database& db)
{
    db << 
        "CREATE TABLE IF NOT EXISTS books("
        "   _id integer primary key autoincrement not null,"
        "   year int,"
        "   title text,"
        "   author text,"
        "   available_copies int"
        ");";

    db << 
        "CREATE TABLE IF NOT EXISTS borrowings("
        "   _id integer primary key autoincrement not null,"
        "   borrower_id integer,"
        "   book_id integer"
        ");";

    db << 
        "CREATE TABLE IF NOT EXISTS users("
        "   _id integer primary key autoincrement not null,"
        "   name text"
        ");";
} 

string getString(const string& text) 
{
    while (true) {
        string input;

        TypeText(const_cast<char*>(text.c_str()));

        getline(cin, input);

        if (input.empty()) {
            TypeText(const_cast<char*>("Invalid input. Please enter a non-empty string.\n"));
            continue;
        }

        return input;
    }
}