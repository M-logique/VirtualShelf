#include <gtest/gtest.h>
#include <database.h>

using namespace sqlite;

TEST(DatabaseSetupTest, CreatesTablesWithoutError) {
    registerDatabase(":memory:");

    EXPECT_NO_THROW(setupTables());

    ASSERT_TRUE(db) << "Database is not initialized!";

    int count = 0;

    *db << "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='books';" >> count;
    EXPECT_EQ(count, 1);

    *db << "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='borrowings';" >> count;
    EXPECT_EQ(count, 1);

    *db << "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='students';" >> count;
    EXPECT_EQ(count, 1);
}
