#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/cvrp_solutionFinder.h"
#include "../src/cvrp_dataModel.h"
#include "../src/cvrp_solutionModel.h"

using ::testing::ContainerEq;
using namespace cvrp;

TEST(SolutionFinder, basicSetup) {
    int e[] = {1, 2, 3, 4};
    std::vector<int> expectedDna(&e[0], &e[0]+4);

    std::stringstream jsonData;
    jsonData << "{\"vehicleCapacity\": 220,\"depot\": {\"x\": 40, \"y\": 40},\"nodes\": [{\"x\": 22, \"y\": 22, \"demand\": 18},{\"x\": 36, \"y\": 26, \"demand\": 26},{\"x\": 21, \"y\": 45, \"demand\": 11},{\"x\": 45, \"y\": 35, \"demand\": 30}]}";
    DataModel model(jsonData);
    
    SolutionFinder solution(&model);

    EXPECT_EQ(solution.getDNASequence().size(), 4);
    ASSERT_THAT(solution.getDNASequence(), ContainerEq(expectedDna));
}

TEST(SolutionFinder, testBasicSolution) {
    std::stringstream jsonData;
    jsonData << "{\"vehicleCapacity\": 45,\"depot\": {\"x\": 40, \"y\": 40},\"nodes\": [{\"x\": 22, \"y\": 22, \"demand\": 18},{\"x\": 36, \"y\": 26, \"demand\": 26},{\"x\": 21, \"y\": 45, \"demand\": 11},{\"x\": 45, \"y\": 35, \"demand\": 30}]}";
    DataModel model(jsonData);
    SolutionFinder solutionFinder(&model);

    SolutionModel solution;
    solutionFinder.getSolution(solution);

    EXPECT_EQ(solution.chromosomes().size(), 2);
    EXPECT_EQ(solution.chromosomes()[0].clientSeqConst().size(), 2);
    EXPECT_EQ(solution.chromosomes()[1].clientSeqConst().size(), 2);

    EXPECT_EQ(solution.chromosomes()[0].clientSeqConst()[0], 2);
    EXPECT_EQ(solution.chromosomes()[0].clientSeqConst()[1], 1);

    EXPECT_EQ(solution.chromosomes()[1].clientSeqConst()[0], 4);
    EXPECT_EQ(solution.chromosomes()[1].clientSeqConst()[1], 3);

    EXPECT_NEAR(solution.chromosomes()[0].cost(), 54.5762, 0.001);
    EXPECT_NEAR(solution.chromosomes()[1].cost(), 52.7178, 0.001);

    EXPECT_EQ(solution.chromosomes()[0].demandCovered(), 44);
    EXPECT_EQ(solution.chromosomes()[1].demandCovered(), 41);

    EXPECT_TRUE(solutionFinder.validateSolution(solution));
    EXPECT_NEAR(solutionFinder.solutionCost(solution), 54.5762+52.7178, 0.001);
}

TEST(SolutionFinder, testSolutionDemandValidation) {
    std::stringstream jsonData;
    jsonData << "{\"vehicleCapacity\": 45,\"depot\": {\"x\": 40, \"y\": 40},\"nodes\": [{\"x\": 22, \"y\": 22, \"demand\": 18},{\"x\": 36, \"y\": 26, \"demand\": 26},{\"x\": 21, \"y\": 45, \"demand\": 11},{\"x\": 45, \"y\": 35, \"demand\": 30}]}";
    DataModel model(jsonData);
    SolutionFinder solutionFinder(&model);

    SolutionModel solution;
    solution.chromosomes().push_back(VehicleTrip(&model));
    solution.chromosomes()[0].addClientToTrip(2);
    solution.chromosomes()[0].addClientToTrip(4);

    EXPECT_FALSE(solutionFinder.validateSolution(solution));
}

TEST(SolutionFinder, testSolutionRouteValidation) {
    std::stringstream jsonData;
    jsonData << "{\"vehicleCapacity\": 45,\"depot\": {\"x\": 40, \"y\": 40},\"nodes\": [{\"x\": 22, \"y\": 22, \"demand\": 18},{\"x\": 36, \"y\": 26, \"demand\": 26},{\"x\": 21, \"y\": 45, \"demand\": 11},{\"x\": 45, \"y\": 35, \"demand\": 30}]}";
    DataModel model(jsonData);
    SolutionFinder solutionFinder(&model);

    SolutionModel solution;
    solution.chromosomes().push_back(VehicleTrip(&model));
    solution.chromosomes().push_back(VehicleTrip(&model));
    solution.chromosomes()[0].addClientToTrip(1);
    solution.chromosomes()[0].addClientToTrip(2);
    solution.chromosomes()[1].addClientToTrip(3);

    EXPECT_FALSE(solutionFinder.validateSolution(solution));
}

