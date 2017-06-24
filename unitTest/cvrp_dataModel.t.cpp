#include "gtest/gtest.h"
#include "../src/cvrp_dataModel.h"

using namespace cvrp;

TEST(DataModel, invalidVehicleCapacity) 
{
    std::stringstream jsonData;
    jsonData << "{\"vehicleCapacity\": -220,\"depot\": {\"x\": 40, \"y\": 40},\"nodes\": [{\"x\": 22, \"y\": 22, \"demand\": 18},{\"x\": 36, \"y\": 26, \"demand\": 26},{\"x\": 21, \"y\": 45, \"demand\": 11},{\"x\": 45, \"y\": 35, \"demand\": 30}]}";
    EXPECT_THROW(DataModel model(jsonData), std::invalid_argument);
}

TEST(DataModel, invalidDepotPosition) 
{
    std::stringstream jsonData;
    jsonData << "{\"vehicleCapacity\": 220,\"depot\": {\"x\": -40, \"y\": 40},\"nodes\": [{\"x\": 22, \"y\": 22, \"demand\": 18},{\"x\": 36, \"y\": 26, \"demand\": 26},{\"x\": 21, \"y\": 45, \"demand\": 11},{\"x\": 45, \"y\": 35, \"demand\": 30}]}";
    EXPECT_THROW(DataModel model(jsonData), std::invalid_argument);
}

TEST(DataModel, invalidClientData) 
{
    std::stringstream jsonData;
    jsonData << "{\"vehicleCapacity\": 220,\"depot\": {\"x\": 40, \"y\": 40},\"nodes\": [{\"x\": 22, \"y\": 22, \"demand\": 18},{\"x\": -36, \"y\": 26, \"demand\": 26},{\"x\": 21, \"y\": 45, \"demand\": -11},{\"x\": 45, \"y\": 35, \"demand\": 30}]}";
    EXPECT_THROW(DataModel model(jsonData), std::invalid_argument);
}

TEST(DataModel, distanceBetweenClients) 
{
    std::stringstream jsonData;
    jsonData << "{\"vehicleCapacity\": 220,\"depot\": {\"x\": 40, \"y\": 40},\"nodes\": [{\"x\": 22, \"y\": 22, \"demand\": 18},{\"x\": 36, \"y\": 26, \"demand\": 26},{\"x\": 21, \"y\": 45, \"demand\": 11},{\"x\": 45, \"y\": 35, \"demand\": 30}]}";
    DataModel model(jsonData);
    EXPECT_EQ(model.vehicleCapacity(), 220);
    EXPECT_EQ(model.depot(), Coord(40, 40));

    EXPECT_NEAR(model.distanceBetweenClients(1, 2), 14.5602, 0.001);
    EXPECT_THROW(model.distanceBetweenClients(1, 7), std::invalid_argument);

    EXPECT_EQ(model.getClientDemand(1), 18);
    EXPECT_EQ(model.getClientDemand(4), 30);
    EXPECT_THROW(model.getClientDemand(5), std::invalid_argument);

    EXPECT_EQ(model.getClientLocation(3), Coord(21, 45));
    EXPECT_THROW(model.getClientLocation(-3), std::invalid_argument);

    EXPECT_EQ(model.numberOfClients(), 4);

    EXPECT_NEAR(model.getClientDistanceFromDepot(1), 25.4558, 0.001);
    EXPECT_NEAR(model.getClientDistanceFromDepot(4), 7.0710, 0.001);
}

