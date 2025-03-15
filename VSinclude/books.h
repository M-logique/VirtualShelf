#ifndef BOOKS_H
#define BOOKS_H

#include <string>
#include <sqlite_modern_cpp.h>

using namespace std;

struct Book {
    string title;
    string author;
    int year;
    int available_copies;
    int id;
};

Book registerBook(
    const string& title,
    const string& author,
    sqlite::database& db,
    int year,
    int available_copies
);


#endif // BOOKS_H