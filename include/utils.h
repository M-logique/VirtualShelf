#ifndef UTILS_H
#define UTILS_H

#include <sqlite_modern_cpp.h>
#include <string>

void Clear();
std::string getString(const std::string& text);
int getNum(const std::string& text);
void typeText(const std::string& text);

class Gout {
public:
    Gout& operator<<(const std::string& data);
    Gout& operator<<(int data);
    Gout& operator<<(std::ostream& (*func)(std::ostream&));
};


void betterPrint(const std::string& text);

extern Gout gout;

#endif // UTILS_H