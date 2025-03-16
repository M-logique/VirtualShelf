#include <sqlite_modern_cpp.h>
#include <string>
#include <utils.h>
#include <books.h>
#include <options.h>
#include <sstream>
#include <libtui.h>
#include <students.h>

using namespace std;
using namespace sqlite;

void addBook(database& db) 
{
    string title = getString("Enter the title of the book: ");
    string author = getString("Enter the author's name: ");
    int year = getNum("Enter the publication year of the book: ");
    int avCps = getNum("How many available copies does it have? : ");

    Book book = registerBook(
        title,
        author,
        db,
        year,
        avCps
    );

    
    Clear();
    GoPrintLogo();

    cout << endl;
    typeText("Book Created!");
    goout 
        << endl 
        << "{{.Cyan}}Title: {{.Magenta}}" << book.title << endl
        << "{{.Cyan}}Author: {{.Magenta}}" << book.author << endl
        << "{{.Cyan}}Publication Year: {{.Magenta}}" << book.year << endl
        << "{{.Cyan}}Available Copies: {{.Magenta}}" << book.available_copies << endl
        << "{{.Reset}}"
        << endl;

    GoPressEnter();
}

void showAllBooks(database& db) 
{

    int count = 0;
    db << "SELECT COUNT(*) FROM books;" >> count;

    if (count == 0) 
    {
        goout << "{{.Red}}There is no book in the shelf"
        << endl;
        GoPressEnter();
        return;
    }

    goout << "{{.Blue}}[!]{{.Cyan}} Found " << count << " Books" 
    << "{{.Reset}}"
    << endl; 

    for (auto &&row : db << "SELECT title,year,author,available_copies FROM books;") {
        string title, author;
        int year, avCps;

        row >> title >> year >> author >> avCps;

        goout 
            << endl 
            << "{{.Cyan}}Title: {{.Magenta}}" << title << endl
            << "{{.Cyan}}Author: {{.Magenta}}" << author << endl
            << "{{.Cyan}}Publication Year: {{.Magenta}}" << year << endl
            << "{{.Cyan}}Available Copies: {{.Magenta}}" << avCps << endl
            << "{{.Reset}}"
            << endl;
    } 

    GoPressEnter();

}

void addStudent(database& db) 
{
    string name = getString("Enter the name of the student: ");
    int student_id = getNum("Enter the id of the student: ");

    Student student = registerStudent(
        name,
        student_id,
        db
    );

    Clear();
    GoPrintLogo();


    cout << endl;
    typeText("Student Registration was successfull!");
    goout 
        << endl 
        << "{{.Cyan}}Name: {{.Magenta}}" << student.name << endl
        << "{{.Cyan}}ID: {{.Magenta}}" << student.student_id << endl
        << "{{.Reset}}"
        << endl;

    GoPressEnter();

}