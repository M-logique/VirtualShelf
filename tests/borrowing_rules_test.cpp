#include <gtest/gtest.h>
#include <database.h>
#include <students.h>
#include <books.h>

TEST(BorrowingsTest, BorrowsBookSuccessfully) 
{
    register_database(":memory:");
    setup_tables();

    Book book = register_book("MyBook", "Author", 1985, 3);
    Student student = register_student("Student", 1234);

    *db << "INSERT INTO borrowings (borrower_id, book_id) VALUES (?, ?);" 
    << student.id 
    << book.id;

    *db << "SELECT available_copies FROM books WHERE title = ?;"
        << "MyBook"
        >> [&](int c) {
            EXPECT_EQ(c, 2);
        };
    
    *db << "DELETE FROM books WHERE title = ?;" 
        << "MyBook";
    
    *db << "SELECT COUNT(*) FROM borrowings;" 
        >> [&](int c) {
            EXPECT_EQ(c, 0);
        };

}