#ifndef UTILS_H
#define UTILS_H

#include <sqlite_modern_cpp.h>
#include <string>

void Clear();
void setupDatabase(sqlite::database& db);
std::string getString(const std::string& text);

#endif // UTILS_H