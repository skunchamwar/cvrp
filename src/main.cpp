#include <iostream>
#include <sstream>
#include <fstream>
#include "cvrp_dataModel.h"
#include "cvrp_solutionFinder.h"

using namespace cvrp;

int main(int argc, char *argv[])
{
    std::ifstream dataFile(argv[1], std::ifstream::binary);
    std::stringstream jsonStream;
    jsonStream << dataFile.rdbuf();
    DataModel model(jsonStream);
    SolutionFinder solution(&model);

    std::vector<VehicleTrip> chromosomes;
    solution.getChromosomes(chromosomes);

    for (std::vector<VehicleTrip>::const_iterator it = chromosomes.begin();
                it != chromosomes.end(); ++it)
    {
        std::cout << it->getTripStr() << std::endl;
    }

    return 0;
}