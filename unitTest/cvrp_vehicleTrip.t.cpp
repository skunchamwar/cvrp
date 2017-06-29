#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/cvrp_vehicleTrip.h"
#include "../src/cvrp_dataModel.h"

using ::testing::ContainerEq;
using namespace cvrp;

TEST(VehicleTrip, testCanAccommodate) 
{
    std::stringstream jsonData;
    jsonData << "{\"vehicleCapacity\": 20,\"depot\": {\"x\": 40, \"y\": 40},\"nodes\": [{\"x\": 22, \"y\": 22, \"demand\": 18},{\"x\": 36, \"y\": 26, \"demand\": 26},{\"x\": 21, \"y\": 45, \"demand\": 11},{\"x\": 45, \"y\": 35, \"demand\": 30}]}";
    DataModel model(jsonData);
    VehicleTrip trip(&model);

    EXPECT_TRUE((const)trip.canAccommodate(1));
    EXPECT_FALSE((const)trip.canAccommodate(2));

    trip.addClientToTrip(1);
    EXPECT_EQ(trip.demandCovered(), 18);
}

TEST(VehicleTrip, testOptimiseTrip) 
{
    std::stringstream jsonData;
    jsonData << "{\"vehicleCapacity\": 200,\"depot\": {\"x\": 40, \"y\": 40},\"nodes\": [{\"x\": 22, \"y\": 22, \"demand\": 18},{\"x\": 36, \"y\": 26, \"demand\": 26},{\"x\": 21, \"y\": 45, \"demand\": 11},{\"x\": 45, \"y\": 35, \"demand\": 30}]}";
    DataModel model(jsonData);
    VehicleTrip trip(&model);

    std::vector<int> expected = {4, 2, 1, 3};

    trip.addClientToTrip(1);
    trip.addClientToTrip(2);
    trip.addClientToTrip(3);
    trip.addClientToTrip(4);
    
    trip.optimiseCost();
    ASSERT_THAT(trip.clientSeqConst(), ContainerEq(expected));
    EXPECT_NEAR(trip.cost(), 77.0276, 0.001);
}


TEST(VehicleTrip, testReEvaluateDemandAndCost) 
{
    std::stringstream jsonData;
    jsonData << "{\"vehicleCapacity\": 200,\"depot\": {\"x\": 40, \"y\": 40},\"nodes\": [{\"x\": 22, \"y\": 22, \"demand\": 18},{\"x\": 36, \"y\": 26, \"demand\": 26},{\"x\": 21, \"y\": 45, \"demand\": 11},{\"x\": 45, \"y\": 35, \"demand\": 300}]}";
    DataModel model(jsonData);
    VehicleTrip trip(&model);

    std::vector<int> expected = {4, 2, 1};

    trip.addClientToTrip(1);
    trip.addClientToTrip(2);

    EXPECT_EQ(trip.demandCovered(), 44);
    trip.clientSequence().push_back(4);
    EXPECT_EQ(trip.demandCovered(), 44);
    trip.reEvaluateDemandAndCost();
    EXPECT_EQ(trip.demandCovered(), 344);
    ASSERT_THAT(trip.clientSeqConst(), ContainerEq(expected));
    EXPECT_NEAR(trip.cost(), 59.8149, 0.001);
    EXPECT_FALSE(trip.isValidTrip());
}

