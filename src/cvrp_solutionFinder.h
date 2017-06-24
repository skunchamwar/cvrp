#ifndef CVRP_SOLUTION_FINDER
#define CVRP_SOLUTION_FINDER

#include "cvrp_idataModel.h"
#include "cvrp_solutionModel.h"

namespace cvrp
{
class SolutionFinder
{
    public:
        SolutionFinder(IDataModel* model);

        void getSolution(SolutionModel& solution);
        bool validateSolution(SolutionModel& solution) const;
        double solutionCost(SolutionModel& solution) const;
        std::vector<int>& getDNASequence() { return m_dnaSequence; }

    private:
        std::vector<int> m_dnaSequence;
        IDataModel* m_model;
};

}//cvrp namespace
#endif