#include "cvrp_solutionFinder.h"
#include <iostream>

namespace cvrp
{

SolutionFinder::SolutionFinder(IDataModel* model) : m_model(model)
{
    model->getClients(m_dnaSequence);
}

void SolutionFinder::getChromosomes(std::vector<VehicleTrip>& chromosomes)
{
    // int vehicleCapacity = model->vehicleCapacity();
    // int currChomosomeCapacity = 0;
    // std::vector<int>* currChromosome;
    // for (int i = 0; i < m_dnaSequence.size(); i++)
    // {
    //     // We assume a sigle client does not have more demand than vehicle capacity
    //     if ((currChomosomeCapacity + model->getCapacityOfClient(m_dnaSequence[i])) > vehicleCapacity )
    //     {
    //         chromosomes.push_back(*currChromosome);
    //         currChromosome = new std::vector<int>();
    //         currChomosomeCapacity = 0;
    //     }
    //     else
    //     {
    //         currChromosome->push_back(m_dnaSequence[i]);
    //         currChomosomeCapacity += model->getCapacityOfClient(m_dnaSequence[i]);
    //     }
    // }

    chromosomes.push_back(VehicleTrip(m_model));
    for (unsigned int i = 0; i < m_dnaSequence.size(); i++)
    {
        bool clinetOnTrip = false;
        for (std::vector<VehicleTrip>::iterator it = chromosomes.begin(); it != chromosomes.end(); ++it)
        {
            if(it->canAccommodate(m_dnaSequence[i]))
            {
                it->addClientToTrip(m_dnaSequence[i]);
                clinetOnTrip = true;
            }
        }
        if (!clinetOnTrip)
        {
            chromosomes.push_back(VehicleTrip(m_model));
            chromosomes.back().addClientToTrip(m_dnaSequence[i]);
        }
    }
    for (std::vector<VehicleTrip>::iterator it = chromosomes.begin(); it != chromosomes.end(); ++it)
    {
        it->optimiseCost();
    }
}

}//cvrp namespace