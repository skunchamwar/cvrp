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
        if (!it->isValidTrip())
        {
            return false;
        }
        for (std::vector<int>::const_iterator ite = it->clientSeqConst().begin(); ite != it->clientSeqConst().end(); ++ite)
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

    for (SolutionIter it = solution.chromosomes().begin(); it != solution.chromosomes().end(); ++it)
    {
        it->reEvaluateDemandAndCost();
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
        for(std::vector<SolutionModel>::iterator ite = solutions.begin(); ite != solutions.end(); ++ite)
        {
            double startingCost = solutionCost(*ite);
            for (int i = 0; i < 50; i++)
            {
                SolutionModel newSol(*ite);
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