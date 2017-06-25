#ifndef CVRP_VEHICLE_TRIP
#define CVRP_VEHICLE_TRIP

#include "cvrp_idataModel.h"

namespace cvrp
{
class VehicleTrip
{
    public:
        VehicleTrip(IDataModel* model);

        const double cost() const { return m_cost; }
        int demandCovered() const { return m_demandCovered; }

        bool canAccommodate(int clientId);
        void addClientToTrip(int clientId);
        void optimiseCost();
        void reEvaluateDemandAndCost();
        bool isValidTrip() const;
        const std::vector<int>& clientSeqConst() const { return m_clientSequence; }
        std::vector<int>& clientSequence() { return m_clientSequence; }
        std::string getTripStr() const;

    private:
        std::vector<int> m_clientSequence;
        double m_cost;
        int m_demandCovered;
        IDataModel* m_model;
};

}//cvrp namespace
#endif