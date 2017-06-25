#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/cvrp_util.h"

using ::testing::ContainerEq;
using namespace cvrp;

TEST(Util, euclideanDistances) 
{
    EXPECT_NEAR(Util::distance(2, 2, 20, 20), 25.4558, 0.0001);
    EXPECT_NEAR(Util::distance(0, 0, 33, 23), 40.2243, 0.0001);
    EXPECT_NEAR(Util::distance(2, 2, 2, 2), 0.0, 0.0001);
}

TEST(Util, swapArrayElements)
{
    std::vector<int> arr = {3, 5, 2, 1, 6};

    Util::swapElements(arr, 0, 3);

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[3], 3);
}

TEST(Util, testSplitAndCascade)
{
    std::vector<int> arr1 = {3, 5, 2, 1, 6};
    std::vector<int> arr2 = {4, 7, 9, 8};

    Util::splitAndCascade(arr1, arr2, 2);

    std::vector<int> exparr1 = {3, 5, 9, 8};
    std::vector<int> exparr2 = {4, 7, 2, 1, 6};

    ASSERT_THAT(arr1, ContainerEq(exparr1));
    ASSERT_THAT(arr2, ContainerEq(exparr2));
}

