#include <gtest/gtest.h>
#include <shared.h>
#include <libtui.h>

TEST(RGBToggleTest, ToggleRGBWithoutError) 
{
    EXPECT_EQ(rgb_enabled, 1);
    EXPECT_EQ(is_rgb_enabled(), 1);

    toggle_rgb();
    GoUpdateRGBState();

    EXPECT_EQ(rgb_enabled, 0);
    EXPECT_EQ(is_rgb_enabled(), 0);
}