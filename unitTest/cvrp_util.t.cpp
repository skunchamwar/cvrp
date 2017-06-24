#include "gtest/gtest.h"
#include "../src/cvrp_util.h"

using namespace cvrp;

TEST(Util, euclideanDistances) 
{
    EXPECT_NEAR(Util::distance(2, 2, 20, 20), 25.4558, 0.0001);
    EXPECT_NEAR(Util::distance(0, 0, 33, 23), 40.2243, 0.0001);
    EXPECT_NEAR(Util::distance(2, 2, 2, 2), 0.0, 0.0001);
}

TEST(Util, swapArrayElements)
{
    std::vector<int> arr;
    arr.push_back(3);
    arr.push_back(5);
    arr.push_back(2);
    arr.push_back(1);
    arr.push_back(6);

    Util::swapElements(arr, 0, 3);

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[3], 3);
}

