#include "gtest/gtest.h"
#include "mod_inverse.h"

TEST(mod_inverse, correct) {
    auto check = [](ll x, ll mod) {
        auto inv = mod_inverse(x, mod);
        return ((x * inv) % mod) == 1;
    };

    for(ll mod : {17, 1000000007, 1000000009}) {
        for(ll x : {2, 50, 1000000000}) {
            EXPECT_TRUE(check(x, mod));
        }
    }
}

TEST(mod_inverse, fails_if_not_coprime) {
    EXPECT_EQ(mod_inverse(5, 10), -1);
    EXPECT_EQ(mod_inverse(1000, 1000000), -1);
    EXPECT_EQ(mod_inverse(1000000000, 8000000000), -1);
}
