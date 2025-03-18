#ifndef BOOKS_H
#define BOOKS_H

#include <string>


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
    int year,
    int available_copies
);


#endif // BOOKS_H