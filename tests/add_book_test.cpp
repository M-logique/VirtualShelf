#include <gtest/gtest.h>
#include <database.h>
#include <books.h>
#include <string>

TEST(AddBookTest, AddsBookWithoutError) 
{

    register_database(":memory:");
    setup_tables();

    EXPECT_NO_THROW(register_book("TestBook", "Author", 1983, 10));

    int year, copies;
    std::string title, author;

    *db << "SELECT year, available_copies, title, author FROM books WHERE title = ? AND author = ? AND year = ? AND available_copies = ?;"
        << "TestBook" << "Author" << 1983 << 10
        >> [&](int y, int c, std::string t, std::string a) {
            year = y;
            copies = c;
            title = t;
            author = a;
        };

    EXPECT_EQ(title, "TestBook");
    EXPECT_EQ(author, "Author");
    EXPECT_EQ(year, 1983);
    EXPECT_EQ(copies, 10);
}