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
        GoPressEnter();
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

void show_borrowings() {
    int count;
    *db << "SELECT COUNT(*) FROM borrowings;" >> count;

    if (count == 0) {
        gout << "{{.Red}}[!]{{.Yellow}} There are no borrowings to display!{{.Reset}}" << endl;
        GoPressEnter();
        return;
    }

    vector<tuple<int, string, int, string, string, int, int>> borrowings;


    for (auto &&row : *db << "SELECT borrowings._id, students.name, students.student_id, books.title, books.author, books.available_copies, books.year FROM borrowings JOIN students ON borrowings.borrower_id = students._id JOIN books ON borrowings.book_id = books._id;") {
        int borrowing_id, student_id, available_copies, year;
        string student_name, book_title, book_author;

        row >> borrowing_id >> student_name >> student_id >> book_title >> book_author >> available_copies >> year;

        borrowings.emplace_back(borrowing_id, student_name, student_id, book_title, book_author, available_copies, year);
    }

    // Thanks chatgpt for this
    for (size_t i = 0; i < borrowings.size(); i++) {
        int borrowing_id, student_id, available_copies, year;
        string student_name, book_title, book_author;
        tie(borrowing_id, student_name, student_id, book_title, book_author, available_copies, year) = borrowings[i];

        gout << "{{.Green}}Borrowing ID: " << borrowing_id << "{{.Reset}}\n";

        gout << "├── {{.Yellow}}By:{{.Reset}}\n";
        gout << "│   ├── Name: {{.Cyan}}" << student_name << "{{.Reset}}\n";
        gout << "│   └── Student ID: {{.Cyan}}" << student_id << "{{.Reset}}\n";

        gout << "└── {{.Yellow}}Book:{{.Reset}}\n";
        gout << "    ├── Title: {{.Cyan}}" << book_title << "{{.Reset}}\n";
        gout << "    ├── Author: {{.Cyan}}" << book_author << "{{.Reset}}\n";
        gout << "    ├── Copies: {{.Cyan}}" << available_copies << "{{.Reset}}\n";
        gout << "    └── Year: {{.Cyan}}" << year << "{{.Reset}}\n";
    }

    GoPressEnter();
}

void return_borrowed_book() {
    int borrowing_id = GoDisplayBorrowingSelector();

    if (borrowing_id == -1) {
        return;
    }

    *db << "DELETE FROM borrowings WHERE _id = ?" 
        << borrowing_id;
    
    gout << "{{.Green}}[✓]{{.Reset}} Borrowing record with ID " << borrowing_id << " has been successfully returned!\n";
    GoPressEnter();
}