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

Book registerBook(
    const string& title,
    const string& author,
    int year,
    int available_copies
)
{
    int recordID;
    *db << 
        "INSERT INTO books (year,title,author,available_copies) values (?,?,?,?) RETURNING _id;"
        << year 
        << title 
        << author 
        << available_copies
        >> recordID;


    return Book{title, author, year, available_copies, recordID};
}