#include <iostream>
#include <sstream>
#include <fstream>
#include <omp.h>
#include "cvrp_dataModel.h"
#include "cvrp_solutionModel.h"
#include "cvrp_solutionFinder.h"
#include "cvrp_util.h"

using namespace cvrp;

int main(int argc, char *argv[])
{
    int id;
    std::cout << "\n";
    std::cout << "  Number of processors available = " << omp_get_num_procs ( ) << "\n";
    std::cout << "  Number of threads =              " << omp_get_max_threads ( ) << "\n";

    std::ifstream dataFile(argv[1], std::ifstream::binary);
    std::stringstream jsonStream;
    jsonStream << dataFile.rdbuf();

    # pragma omp parallel \
    private ( id ) \
    shared ( jsonStream )
    {
        DataModel model(jsonStream.str());

        id = omp_get_thread_num ( );
        SolutionFinder solutionFinder(&model);
        
        SolutionModel solution = solutionFinder.solutionWithEvolution();
        std::cout << "Processor ID: " << id << std::endl;
        solution.printSolution();
        std::cout << "Total Cost: " << solutionFinder.solutionCost(solution) << std::endl;
        std::cout << "##################################################################" << std::endl;
        
    }
    return 0;
}