#ifndef UTILS_H
#define UTILS_H

#include <string>

void Clear();
std::string get_string(const std::string& text);
int get_num(const std::string& text);
void type_text(const std::string& text);

class Gout {
public:
    Gout& operator<<(const std::string& data);
    Gout& operator<<(int data);
    Gout& operator<<(std::ostream& (*func)(std::ostream&));
};


void better_print(const std::string& text);

extern Gout gout;

#endif // UTILS_H