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

const char** get_book_values(int* size) {
    if (!db) return nullptr; 

    vector<string> values;
    for (auto &&row : *db << "SELECT _id, year, author, title FROM books WHERE available_copies > 0;") {
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

const char** get_book_values(int* size) {
    if (!db) return nullptr; 

    vector<string> values;
    for (auto &&row : *db << "SELECT _id, year, author, title FROM books WHERE available_copies > 0;") {
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


void free_values(const char** values, int size) {
    for (int i = 0; i < size; i++) {
        free((void*)values[i]);
    }
    free(values);
}