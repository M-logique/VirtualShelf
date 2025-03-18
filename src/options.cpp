#include <sqlite_modern_cpp.h>
#include <string>
#include <utils.h>
#include <books.h>
#include <options.h>
#include <sstream>
#include <libtui.h>
#include <students.h>
#include <database.h>

using namespace std;
using namespace sqlite;

void addBook() 
{
    string title = getString("Enter the title of the book: ");
    string author = getString("Enter the author's name: ");
    int year = getNum("Enter the publication year of the book: ");
    int avCps = getNum("How many available copies does it have? : ");

    Book book = registerBook(
        title,
        author,
        year,
        avCps
    );

    
    Clear();
    GoPrintLogo();

    cout << endl;
    typeText("Book Created!");
    gout 
        << endl 
        << "{{.Cyan}}Title: {{.Magenta}}" << book.title << endl
        << "{{.Cyan}}Author: {{.Magenta}}" << book.author << endl
        << "{{.Cyan}}Publication Year: {{.Magenta}}" << book.year << endl
        << "{{.Cyan}}Available Copies: {{.Magenta}}" << book.available_copies << endl
        << "{{.Reset}}"
        << endl;

    GoPressEnter();
}

void showAllBooks() 
{

    int count = 0;
    *db << "SELECT COUNT(*) FROM books;" >> count;

    if (count == 0) 
    {
        gout << "{{.Red}}There is no book in the shelf"
        << endl;
        GoPressEnter();
        return;
    }

    gout << "{{.Blue}}[!]{{.Cyan}} Found " << count << " Books" 
    << "{{.Reset}}"
    << endl; 

    for (auto &&row : *db << "SELECT title,year,author,available_copies FROM books;") {
        string title, author;
        int year, avCps;

        row >> title >> year >> author >> avCps;

        gout 
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

void addStudent() 
{
    int student_id;
    string name = getString("Enter the name of the student: ");
    while (true) {
        student_id = getNum("Enter the id of the student: ");
        int count = 0;

        *db << "SELECT count(*) FROM students WHERE student_id = ?;" << student_id >> count;
        if (count == 0) {
            break;
        }

        gout << "{{.Red}}[!]{{.Yellow}} Student ID already exists. Please enter a new one.{{.Reset}}" << endl;

    }

    Student student = registerStudent(
        name,
        student_id
    );

    Clear();
    GoPrintLogo();


    cout << endl;
    typeText("Student Registration was successfull!");
    gout 
        << endl 
        << "{{.Cyan}}Name: {{.Magenta}}" << student.name << endl
        << "{{.Cyan}}ID: {{.Magenta}}" << student.student_id << endl
        << "{{.Reset}}"
        << endl;

    GoPressEnter();

}

void borrowABook() 
{
    int book_id = GoDisplayBookSelector();
    if (book_id == -1) {
        return;
    }

    int student_id = GoDisplayStudentSelector();
    if (student_id == -1) {
        return;
    }
    
    *db << "INSERT INTO borrowings (borrower_id, book_id) VALUES (?, ?);" 
        << student_id 
        << book_id;

    gout << "{{.Green}}[✓]{{.Yellow}} Book borrowed successfully.{{.Reset}}" << endl;
    GoPressEnter();
}