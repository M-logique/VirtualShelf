#include <gtest/gtest.h>
#include <sqlite_modern_cpp.h>
#include "utils.h"

using namespace sqlite;

TEST(DatabaseSetupTest, CreatesTablesWithoutError) {
    database db(":memory:");

    EXPECT_NO_THROW(setupDatabase(db));

    int count = 0;

    db << "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='books';" >> count;
    EXPECT_EQ(count, 1);

    db << "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='borrowings';" >> count;
    EXPECT_EQ(count, 1);

    db << "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='users';" >> count;
    EXPECT_EQ(count, 1);
}
