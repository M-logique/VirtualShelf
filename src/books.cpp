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
)
{
    db << 
        "INSERT INTO books (year,title,author,available_copies) values (?,?,?,?);"
        << year 
        << title 
        << author 
        << available_copies;

    int recordID = static_cast<int>(db.last_insert_rowid());

    Book book;
    book.title = title;
    book.author = author;
    book.available_copies = available_copies;
    book.year = year;
    book.id = recordID;

    return book;
}