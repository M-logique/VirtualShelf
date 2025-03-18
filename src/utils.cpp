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





string get_string(const string& text) 
{
    while (true) {
        string input;

        type_text(text);

        getline(cin, input);

        if (input.empty()) {
            type_text("Invalid input. Please enter a non-empty string.\n");
            continue;
        }

        return input;
    }
}

int get_num(const string& text) 
{
    while (true) {
        string input;
        int inputMsg;

        type_text(text);
        getline(cin, input);

        stringstream ss(input);
        if (!(ss >> inputMsg)) {
            type_text("Invalid input. Please enter a number.\n");
            continue;
        }

        return inputMsg;
    }
}

void type_text(const string& text) 
{
    GoTypeText(const_cast<char*>(text.c_str()));
}

void better_print(const string& text) {
    GoBetterPrint(const_cast<char*>(text.c_str()));
}

Gout& Gout::operator<<(const string& data) {
    better_print(data);
    return *this;
}

Gout& Gout::operator<<(int data) {
    stringstream ss;
    ss << data;
    better_print(ss.str());
    return *this;
}


Gout& Gout::operator<<(ostream& (*func)(ostream&)) {
    func(cout); 
    return *this;
}

Gout gout;
