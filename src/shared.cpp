#include <shared.h>
#include <sqlite_modern_cpp.h>
#include <vector>
#include <database.h>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;
using namespace sqlite;

int rgb_enabled = 1;

int is_rgb_enabled() {
    return rgb_enabled;
}

void toggle_rgb() {
    rgb_enabled = !rgb_enabled; 
}

const char** get_book_values(int* size, int check_av) 
{
    if (!db) return nullptr; 

    string query = "SELECT _id, year, author, title FROM books";

    if (check_av) {
        query+=" WHERE available_copies > 0";
    }

    query += ";";

    vector<string> values;
    for (auto &&row : *db << query) {
        stringstream ss;
        int _id, year;
        string author, title;
        row >> _id >> year >> author >> title;
        ss << "ID: " << _id << " | Title: " << title << " | Author: " << author;
        values.push_back(ss.str());
    }

    *size = values.size();
    if (*size == 0) return nullptr;

    const char** values_arr = (const char**)malloc(*size * sizeof(const char*));
    if (!values_arr) return nullptr;

    for (int i = 0; i < *size; i++) {
        values_arr[i] = strdup(values[i].c_str());
    }

    return values_arr; 
}

const char** get_student_values(int* size) 
{
    if (!db) return nullptr; 

    vector<string> values;
    for (auto &&row : *db << "SELECT _id, name, student_id FROM students") {
        stringstream ss;
        int _id, student_id;
        string name;
        row >> _id >> name >> student_id;
        ss << "ID: " << _id << " | Name: " << name << " | Student ID: " << student_id;
        values.push_back(ss.str());
    }

    *size = values.size();
    if (*size == 0) return nullptr;

    const char** values_arr = (const char**)malloc(*size * sizeof(const char*));
    if (!values_arr) return nullptr;

    for (int i = 0; i < *size; i++) {
        values_arr[i] = strdup(values[i].c_str());
    }

    return values_arr; 
}
const char** get_borrowing_values(int* size) 
{
    if (!db) return nullptr; 

    vector<string> values;
    for (auto &&row : *db << "SELECT borrowings._id, books.title, students.name "
                            "FROM borrowings "
                            "JOIN books ON borrowings.book_id = books._id "
                            "JOIN students ON borrowings.borrower_id = students._id") {
        stringstream ss;
        int borrowing_id;
        string book_title, borrower_name;
        
        row >> borrowing_id >> book_title >> borrower_name;
        ss << "ID: " << borrowing_id << " | Book: " << book_title << " | Borrower: " << borrower_name;
        values.push_back(ss.str());
    }

    *size = values.size();
    if (*size == 0) return nullptr;

    const char** values_arr = (const char**)malloc(*size * sizeof(const char*));
    if (!values_arr) return nullptr;

    for (int i = 0; i < *size; i++) {
        values_arr[i] = strdup(values[i].c_str());
    }

    return values_arr; 
}

void free_values(const char** values, int size) {
    for (int i = 0; i < size; i++) {
        free((void*)values[i]);
    }
    free(values);
}