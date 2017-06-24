#include "cvrp_solutionModel.h"
#include <iostream>

namespace cvrp
{

SolutionModel::SolutionModel()
{
}

void SolutionModel::printSolution()
{
    for (std::vector<VehicleTrip>::const_iterator it = m_solution.begin();
                it != m_solution.end(); ++it)
    {
        std::cout << it->getTripStr() << std::endl;
    }
}

}//cvrp namespace