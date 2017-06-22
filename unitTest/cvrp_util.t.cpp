#include "gtest/gtest.h"

#include "../cvrp_util.h"

using namespace cvrp;

TEST(Util, euclideanDistances) {
    EXPECT_NEAR(Util::distance(2, 2, 20, 20), 25.4558, 0.0001);
    EXPECT_NEAR(Util::distance(0, 0, 33, 23), 40.2243, 0.0001);
    EXPECT_NEAR(Util::distance(2, 2, 2, 2), 0.0, 0.0001);
}

