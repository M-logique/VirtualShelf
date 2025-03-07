#include <sqlite_modern_cpp.h>
#include <string>
#include <Utils.h>
#include <Books.h>
#include <Options.h>
#include <sstream>
#include <libtui.h>

using namespace std;
using namespace sqlite;

void addBook(database& db) 
{
    string title = getString("Enter the title of the book: ");
    string author = getString("Enter the name of author of the book: ");
    int year = getNum("Enter the creation year of the book: ");
    int avCps = getNum("How many available copies it have?: ");
    Book book = registerBook(
        title,
        author,
        db,
        year,
        avCps
    );
    stringstream ss;
    ss << "Book created with ID: " 
       << book.id;
    typeText(ss.str());
    PressEnter();
}

