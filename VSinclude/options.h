#ifndef OPTIONS_H
#define OPTIONS_H

#include <sqlite_modern_cpp.h>

void addBook(sqlite::database& db);
void showAllBooks(sqlite::database& db);

#endif // OPTIONS_H