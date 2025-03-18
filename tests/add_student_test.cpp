#include <gtest/gtest.h>
#include <database.h>
#include <students.h>
#include <string>

TEST(AddStudentTest, PreventsDuplicateID) 
{
    register_database(":memory:");
    setup_tables();

    
    EXPECT_NO_THROW(register_student("TestStudent", 1234));
    EXPECT_THROW(register_student("TestStudent2", 1234), std::exception);
}