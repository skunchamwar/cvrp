#include "gtest/gtest.h"

#include "../cvrp_dataModel.h"

using namespace cvrp;

TEST(DataModel, distanceBetweenClients) 
{
    std::stringstream jsonData;
    jsonData << "{\"vehicleCapacity\": 220,\"depot\": {\"x\": 40, \"y\": 40},\"nodes\": [{\"x\": 22, \"y\": 22, \"demand\": 18},{\"x\": 36, \"y\": 26, \"demand\": 26},{\"x\": 21, \"y\": 45, \"demand\": 11},{\"x\": 45, \"y\": 35, \"demand\": 30}]}";
    DataModel model(jsonData);
    EXPECT_EQ(model.vehicleCapacity(), 220);
    EXPECT_EQ(model.depot(), Coord(40, 40));
    EXPECT_NEAR(model.distanceBetweenClients(1, 2), 14.5602, 0.0001);
    EXPECT_EQ(model.getCapacityOfClient(1), 18);
    EXPECT_EQ(model.getCapacityOfClient(4), 30);
    EXPECT_EQ(model.getClientLocation(3), Coord(21, 45));
}