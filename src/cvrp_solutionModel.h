#ifndef CVRP_SOLUTION_MODEL
#define CVRP_SOLUTION_MODEL

#include <vector>
#include "cvrp_vehicleTrip.h"

namespace cvrp
{
typedef std::vector<VehicleTrip>::iterator SolutionIter;
typedef std::vector<VehicleTrip>::const_iterator ConstSolIter;
class SolutionModel
{
    public:
        SolutionModel();

        std::vector<VehicleTrip>& chromosomes()  { return m_solution; }
        const std::vector<VehicleTrip>& chromosomesConst()  { return m_solution; }
        void printSolution();

    private:
        std::vector<VehicleTrip> m_solution;
};

}//cvrp namespace
#endif