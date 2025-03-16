#include <cstdlib>
#include <sqlite_modern_cpp.h>
#include <utils.h>
#include <libtui.h>
#include <sstream>

using namespace std;
using namespace sqlite;



void Clear() 
{
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
        "CREATE TABLE IF NOT EXISTS students("
        "   _id integer primary key autoincrement not null,"
        "   name text,"
        "   student_id integer"
        ");";
} 

string getString(const string& text) 
{
    while (true) {
        string input;

        typeText(text);

        getline(cin, input);

        if (input.empty()) {
            typeText("Invalid input. Please enter a non-empty string.\n");
            continue;
        }

        return input;
    }
}

int getNum(const string& text) 
{
    while (true) {
        string input;
        int inputMsg;

        typeText(text);
        getline(cin, input);

        stringstream ss(input);
        if (!(ss >> inputMsg)) {
            typeText("Invalid input. Please enter a number.\n");
            continue;
        }

        return inputMsg;
    }
}

void typeText(const string& text) 
{
    GoTypeText(const_cast<char*>(text.c_str()));
}

void betterPrint(const string& text) {
    GoBetterPrint(const_cast<char*>(text.c_str()));
}

Printer& Printer::operator<<(const std::string& data) {
    betterPrint(data);
    return *this;
}

Printer& Printer::operator<<(int data) {
    std::stringstream ss;
    ss << data;
    betterPrint(ss.str());
    return *this;
}


Printer& Printer::operator<<(std::ostream& (*func)(std::ostream&)) {
    func(std::cout); 
    return *this;
}

Printer goout;
