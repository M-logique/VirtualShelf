#include <gtest/gtest.h>
#include <database.h>

TEST(DatabaseSetupTest, CreatesTablesWithoutError) 
{
    register_database(":memory:");

    EXPECT_NO_THROW(setup_tables());

    ASSERT_TRUE(db) << "Database is not initialized!";

    int count = 0;

    *db << "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='books';" >> count;
    EXPECT_EQ(count, 1);

    *db << "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='borrowings';" >> count;
    EXPECT_EQ(count, 1);

    *db << "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='students';" >> count;
    EXPECT_EQ(count, 1);
}

