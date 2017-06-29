#include "cvrp_solutionModel.h"
#include <iostream>

namespace cvrp
{

SolutionModel::SolutionModel()
{
}

void SolutionModel::printSolution()
{
    for (auto const &trip : m_solution)
    {
        std::cout << trip.getTripStr() << std::endl;
    }
}

}//cvrp namespace