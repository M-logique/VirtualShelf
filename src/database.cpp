#include <sqlite_modern_cpp.h>
#include <database.h>

using namespace sqlite;


std::unique_ptr<sqlite::database> db = nullptr; 

void registerDatabase(const std::string& name) {
    db = std::make_unique<sqlite::database>(name);
}


void setupTables()
{


    *db << "PRAGMA foreign_keys = ON;"; 

    *db << 
        "CREATE TABLE IF NOT EXISTS books("
        "   _id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
        "   year INT,"
        "   title TEXT,"
        "   author TEXT,"
        "   available_copies INT"
        ");";

    *db << 
        "CREATE TABLE IF NOT EXISTS students("
        "   _id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
        "   name TEXT,"
        "   student_id INTEGER"
        ");";

    *db << 
        "CREATE TABLE IF NOT EXISTS borrowings("
        "   _id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
        "   borrower_id INTEGER,"
        "   book_id INTEGER,"
        "   FOREIGN KEY(borrower_id) REFERENCES students(_id) ON DELETE CASCADE,"
        "   FOREIGN KEY(book_id) REFERENCES books(_id) ON DELETE CASCADE"
        ");";

    *db << 
        "CREATE TRIGGER IF NOT EXISTS decrease_available_copies "
        "AFTER INSERT ON borrowings "
        "FOR EACH ROW "
        "BEGIN "
        "   UPDATE books SET available_copies = available_copies - 1 WHERE _id = NEW.book_id; "
        "END;";

    *db << 
        "CREATE TRIGGER IF NOT EXISTS increase_available_copies "
        "AFTER DELETE ON borrowings "
        "FOR EACH ROW "
        "BEGIN "
        "   UPDATE books SET available_copies = available_copies + 1 WHERE _id = OLD.book_id; "
        "END;";
}