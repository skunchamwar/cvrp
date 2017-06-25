#include <iostream>
#include <sstream>
#include <fstream>
#include "cvrp_dataModel.h"
#include "cvrp_solutionModel.h"
#include "cvrp_solutionFinder.h"
#include "cvrp_util.h"

using namespace cvrp;

int main(int argc, char *argv[])
{
    std::ifstream dataFile(argv[1], std::ifstream::binary);
    std::stringstream jsonStream;
    jsonStream << dataFile.rdbuf();
    DataModel model(jsonStream);
    SolutionFinder solutionFinder(&model);

    SolutionModel solution;
    solutionFinder.getSolution(solution);

    if (solutionFinder.validateSolution(solution))
    {
        solution.printSolution();
        std::cout << "Total Cost: " << solutionFinder.solutionCost(solution) << std::endl;
        std::cout << "##################################################################" << std::endl;
    }

    std::vector<SolutionModel> generation;
    std::vector<SolutionModel> solutions;
    solutions.push_back(solution);
    double leastCost = solutionFinder.solutionCost(solution);
    int x = 0;
    while (x < 100)
    {
        bool foundBetterGeneration = false;
        for(std::vector<SolutionModel>::iterator ite = solutions.begin(); ite != solutions.end(); ++ite)
        {
            double startingCost = solutionFinder.solutionCost(*ite);
            for (int i = 0; i < 50; i++)
            {
                SolutionModel newSol(*ite);
                // int numberOfCrossovers = Util::generateRandomNumberInRange(1, 5);
                // for (int j = 0; j < numberOfCrossovers; j++)
                // {
                    solutionFinder.crossover(newSol);
                // }
                double currSolCost = solutionFinder.solutionCost(newSol);
                if (solutionFinder.validateSolution(newSol) && currSolCost < startingCost)
                {
                    if (currSolCost < leastCost)
                    {
                        generation.push_back(newSol);
                        leastCost = currSolCost;
                        newSol.printSolution();
                        std::cout << "Total Cost: " << currSolCost << std::endl;
                        std::cout << "##################################################################" << std::endl;
                        foundBetterGeneration = true;
                    }
                }
            }
        }
        if (foundBetterGeneration)
        {
            std::cout << "new generation: " << generation.size() << std::endl;
            solutions.clear();
            solutions = generation;
            generation.clear();
        }
        ++x;
    }
    return 0;
}