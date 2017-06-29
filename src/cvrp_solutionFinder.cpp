#include "cvrp_solutionFinder.h"
#include "cvrp_util.h"

namespace cvrp
{

SolutionFinder::SolutionFinder(IDataModel* model) : m_model(model)
{
    model->getClients(m_dnaSequence);
}

void SolutionFinder::getSolution(SolutionModel& solution)
{
    solution.chromosomes().push_back(VehicleTrip(m_model));
    for (auto clientId : m_dnaSequence)
    {
        bool clinetOnTrip = false;
        for (auto &chromosome : solution.chromosomes())
        {
            if((const)chromosome.canAccommodate(clientId))
            {
                chromosome.addClientToTrip(clientId);
                clinetOnTrip = true;
                break;
            }
        }
        if (!clinetOnTrip)
        {
            solution.chromosomes().push_back(VehicleTrip(m_model));
            solution.chromosomes().back().addClientToTrip(clientId);
        }
    }
    for (auto &chromosome : solution.chromosomes())
    {
        chromosome.optimiseCost();
    }
}

bool SolutionFinder::validateSolution(SolutionModel& solution) const
{
    std::vector<int> check(m_model->numberOfClients()+1, false);
    check[0] = true;
    for (auto const &chromosome : solution.chromosomesConst())
    {
        if (!chromosome.isValidTrip())
        {
            return false;
        }
        for (auto clientId : chromosome.clientSeqConst())
        {
            if (check[clientId])
            {
                return false;
            }
            check[clientId] = true;
        }
    }
    for (auto flag : check)
    {
        if (!flag)
        {
            return false;
        }
    }
    return true;
}

double SolutionFinder::solutionCost(SolutionModel& solution) const
{
    double totalCost = 0.0;
    for (auto const &chromosome : solution.chromosomesConst())
    {
        totalCost += chromosome.cost();
    }
    return totalCost;
}

void SolutionFinder::crossover(SolutionModel& solution)
{

    int crossoverSubject1 = Util::generateRandomNumberInRange(1,solution.chromosomes().size()-1);
    int crossoverSubject2 = Util::generateRandomNumberInRange(1,solution.chromosomes().size()-1);
    while (crossoverSubject2 == crossoverSubject1)
    {
        crossoverSubject2 = Util::generateRandomNumberInRange(1,solution.chromosomes().size()-1);
    }

    int smallChromosomeSize = solution.chromosomes()[crossoverSubject1].clientSeqConst().size() < solution.chromosomes()[crossoverSubject2].clientSeqConst().size()
                                ? solution.chromosomes()[crossoverSubject1].clientSeqConst().size()
                                : solution.chromosomes()[crossoverSubject2].clientSeqConst().size();
    
    int crossoverPoint = Util::generateRandomNumberInRange(1,smallChromosomeSize-1);

    std::vector<int>& subject1 = solution.chromosomes()[crossoverSubject1].clientSequence();
    std::vector<int>& subject2 = solution.chromosomes()[crossoverSubject2].clientSequence();

    int randomNum = Util::generateRandomNumberInRange(1,10);
    if (randomNum < 8)
    {
        Util::splitAndCascade(subject1, subject2, crossoverPoint);
    }
    else //if (randomNum < 9)
    {
        Util::splitAndFlipCascade(subject1, subject2, crossoverPoint);
    }
    // else
    // {
    //     int crossoverPoint2 = Util::generateRandomNumberInRange(1,smallChromosomeSize-2);
    //     while (crossoverPoint == crossoverPoint2)
    //     {
    //         crossoverPoint2 = Util::generateRandomNumberInRange(1,smallChromosomeSize-2);
    //     }
    //     if (crossoverPoint2 < crossoverPoint)
    //     {
    //         Util::spliceAndCascade(subject1, subject2, crossoverPoint2, crossoverPoint);
    //     }
    //     else
    //     {
    //         Util::spliceAndCascade(subject1, subject2, crossoverPoint, crossoverPoint2);
    //     }
    // }

    for (auto &chromosome : solution.chromosomes())
    {
        chromosome.reEvaluateDemandAndCost();
    }
}

SolutionModel SolutionFinder::solutionWithEvolution()
{
    SolutionModel solution;
    getSolution(solution);

    std::vector<SolutionModel> generation;
    std::vector<SolutionModel> solutions;
    solutions.push_back(solution);
    double leastCost = solutionCost(solution);
    int x = 0;
    while (x < 100)
    {
        bool foundBetterGeneration = false;
        for(auto &sol : solutions)
        {
            double startingCost = solutionCost(sol);
            for (int i = 0; i < 50; i++)
            {
                SolutionModel newSol(sol);
                crossover(newSol);
                double currSolCost = solutionCost(newSol);
                if (validateSolution(newSol) && currSolCost < startingCost)
                {
                    if (currSolCost < leastCost)
                    {
                        generation.push_back(newSol);
                        leastCost = currSolCost;
                        foundBetterGeneration = true;
                    }
                }
            }
        }
        if (foundBetterGeneration)
        {
            solutions.clear();
            solutions = generation;
            generation.clear();
        }
        ++x;
    }

    return *solutions.begin();
}

}//cvrp namespace