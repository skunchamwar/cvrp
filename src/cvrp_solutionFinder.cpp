#include "cvrp_solutionFinder.h"

namespace cvrp
{

SolutionFinder::SolutionFinder(IDataModel* model) : m_model(model)
{
    model->getClients(m_dnaSequence);
}

void SolutionFinder::getSolution(SolutionModel& solution)
{
    solution.chromosomes().push_back(VehicleTrip(m_model));
    for (unsigned int i = 0; i < m_dnaSequence.size(); i++)
    {
        bool clinetOnTrip = false;
        for (SolutionIter it = solution.chromosomes().begin(); it != solution.chromosomes().end(); ++it)
        {
            if(it->canAccommodate(m_dnaSequence[i]))
            {
                it->addClientToTrip(m_dnaSequence[i]);
                clinetOnTrip = true;
                break;
            }
        }
        if (!clinetOnTrip)
        {
            solution.chromosomes().push_back(VehicleTrip(m_model));
            solution.chromosomes().back().addClientToTrip(m_dnaSequence[i]);
        }
    }
    for (SolutionIter it = solution.chromosomes().begin(); it != solution.chromosomes().end(); ++it)
    {
        it->optimiseCost();
    }
}

bool SolutionFinder::validateSolution(SolutionModel& solution) const
{
    std::vector<int> check(m_model->numberOfClients()+1, false);
    for (ConstSolIter it = solution.chromosomesConst().begin(); it != solution.chromosomesConst().end(); ++it)
    {
        if (it->demandCovered() > m_model->vehicleCapacity())
        {
            return false;
        }
        for (std::vector<int>::const_iterator ite = it->clientSequence().begin(); ite != it->clientSequence().end(); ++ite)
        {
            if (check[*ite])
            {
                return false;
            }
            check[*ite] = true;
        }
    }
    for (unsigned int i = 1; i < check.size(); i++)
    {
        if (!check[i])
        {
            return false;
        }
    }
    return true;
}

double SolutionFinder::solutionCost(SolutionModel& solution) const
{
    double totalCost = 0.0;
    for (ConstSolIter it = solution.chromosomesConst().begin(); it != solution.chromosomesConst().end(); ++it)
    {
        totalCost += it->cost();
    }
    return totalCost;
}

}//cvrp namespace