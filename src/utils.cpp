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

Gout& Gout::operator<<(const string& data) {
    betterPrint(data);
    return *this;
}

Gout& Gout::operator<<(int data) {
    stringstream ss;
    ss << data;
    betterPrint(ss.str());
    return *this;
}


Gout& Gout::operator<<(ostream& (*func)(ostream&)) {
    func(cout); 
    return *this;
}

Gout gout;
