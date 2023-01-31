#include "gtest/gtest.h"
#include "fenwick.h"

TEST(fenwick, works) {
    Fenwick ft(5);
    EXPECT_EQ(ft.sum(0, 4), 0);
    ft.add(2, 5);
    EXPECT_EQ(ft.sum(0, 4), 5);
    EXPECT_EQ(ft.sum(0, 1), 0);
}
