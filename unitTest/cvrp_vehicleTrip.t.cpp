#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/cvrp_vehicleTrip.h"
#include "../src/cvrp_dataModel.h"

using ::testing::ContainerEq;
using namespace cvrp;

TEST(VehicleTrip, testCanAccommodate) {
    std::stringstream jsonData;
    jsonData << "{\"vehicleCapacity\": 20,\"depot\": {\"x\": 40, \"y\": 40},\"nodes\": [{\"x\": 22, \"y\": 22, \"demand\": 18},{\"x\": 36, \"y\": 26, \"demand\": 26},{\"x\": 21, \"y\": 45, \"demand\": 11},{\"x\": 45, \"y\": 35, \"demand\": 30}]}";
    DataModel model(jsonData);
    VehicleTrip trip(&model);

    EXPECT_TRUE(trip.canAccommodate(1));
    EXPECT_FALSE(trip.canAccommodate(2));

    trip.addClientToTrip(1);
    EXPECT_EQ(trip.demandCovered(), 18);
}

TEST(VehicleTrip, testOptimiseTrip) {
    std::stringstream jsonData;
    jsonData << "{\"vehicleCapacity\": 200,\"depot\": {\"x\": 40, \"y\": 40},\"nodes\": [{\"x\": 22, \"y\": 22, \"demand\": 18},{\"x\": 36, \"y\": 26, \"demand\": 26},{\"x\": 21, \"y\": 45, \"demand\": 11},{\"x\": 45, \"y\": 35, \"demand\": 30}]}";
    DataModel model(jsonData);
    VehicleTrip trip(&model);

    std::vector<int> expected;
    expected.push_back(4);
    expected.push_back(2);
    expected.push_back(1);
    expected.push_back(3);

    trip.addClientToTrip(1);
    trip.addClientToTrip(2);
    trip.addClientToTrip(3);
    trip.addClientToTrip(4);
    
    trip.optimiseCost();
    ASSERT_THAT(trip.clientSequence(), ContainerEq(expected));
    EXPECT_NEAR(trip.cost(), 77.0276, 0.001);
}

