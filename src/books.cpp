#include <string>
#include <database.h>

using namespace std;

struct Book {
    string title;
    string author;

    int year;
    int available_copies;
    int id;
};

Book register_book(
    const string& title,
    const string& author,
    int year,
    int available_copies
)
{
    int record_id;
    *db << 
        "INSERT INTO books (year,title,author,available_copies) values (?,?,?,?) RETURNING _id;"
        << year 
        << title 
        << author 
        << available_copies
        >> record_id;


    return Book{title, author, year, available_copies, record_id};
}