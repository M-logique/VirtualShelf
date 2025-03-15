#ifndef UTILS_H
#define UTILS_H

#include <sqlite_modern_cpp.h>
#include <string>

void Clear();
void setupDatabase(sqlite::database& db);
std::string getString(const std::string& text);
int getNum(const std::string& text);
void typeText(const std::string& text);

class Printer {
public:
    Printer& operator<<(const std::string& data);
    Printer& operator<<(int data);
    Printer& operator<<(std::ostream& (*func)(std::ostream&));
};

extern Printer prnt;

void betterPrint(const std::string& text);

extern Printer printer;

#endif // UTILS_H