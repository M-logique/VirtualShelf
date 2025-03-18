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

void add_book() 
{
    string title = get_string("Enter the title of the book: ");
    string author = get_string("Enter the author's name: ");
    int year = get_num("Enter the publication year of the book: ");
    int av_cps = get_num("How many available copies does it have? : ");

    Book book = register_book(
        title,
        author,
        year,
        av_cps
    );

    
    Clear();
    GoPrintLogo();

    cout << endl;
    type_text("Book Created!");
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

void show_all_books() 
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

void add_student() 
{
    int student_id;
    string name = get_string("Enter the name of the student: ");
    while (true) {
        student_id = get_num("Enter the id of the student: ");
        int count = 0;

        *db << "SELECT count(*) FROM students WHERE student_id = ?;" << student_id >> count;
        if (count == 0) {
            break;
        }

        gout << "{{.Red}}[!]{{.Yellow}} Student ID already exists. Please enter a new one.{{.Reset}}" << endl;

    }

    Student student = register_student(
        name,
        student_id
    );

    Clear();
    GoPrintLogo();


    cout << endl;
    type_text("Student Registration was successfull!");
    gout 
        << endl 
        << "{{.Cyan}}Name: {{.Magenta}}" << student.name << endl
        << "{{.Cyan}}ID: {{.Magenta}}" << student.student_id << endl
        << "{{.Reset}}"
        << endl;

    GoPressEnter();

}

void borrow_a_book() 
{
    int book_id = GoDisplayBookSelector(1);
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


void search_books() 
{
    int count;
    *db << "SELECT COUNT(*) FROM books;" 
        >> count;

    if (count == 0) {
        gout << "{{.Red}}[!]{{.Yellow}} There is no book in the shelf!{{.Reset}}" << endl;
        return;
    }     

    int book_id = GoDisplayBookSelector(0);
    
    string title, author;
    int year, av_cps, _id, borrow_count;

    bool book_found = false;
    *db << "SELECT _id, title, year, author, available_copies FROM books WHERE _id = ?;"
        << book_id
        >> [&](int id, string t, int y, string a, int av) {
            _id = id;
            title = t;
            year = y;
            author = a;
            av_cps = av;
        };



    *db << "SELECT COUNT(*) FROM borrowings WHERE book_id = ?;" 
        << _id
        >> borrow_count;


    gout 
        << "{{.Green}}Title: {{.Magenta}}" << title << endl
        << "{{.Green}}Author: {{.Magenta}}" << author << endl
        << "{{.Green}}Year: {{.Magenta}}" << year << endl 
        << "{{.Green}}Current Copies: {{.Magenta}}" << av_cps << endl
        << "{{.Blue}} Borrowed: {{.LightMagenta}}" << borrow_count << endl
        << "{{.Blue}} Total: {{.LightMagenta}}" << borrow_count + av_cps << endl;

        
    
    GoPressEnter();
}
