#ifndef BOOKS_H
#define BOOKS_H

#include <string>
#include <sqlite_modern_cpp.h>


struct Book {
    std::string title;
    std::string author;
    int year;
    int available_copies;
    int id;
};

Book registerBook(
    const std::string& title,
    const std::string& author,
    sqlite::database& db,
    int year,
    int available_copies
);


#endif // BOOKS_H