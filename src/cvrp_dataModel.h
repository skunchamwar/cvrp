#ifndef CVRP_DATA_MODEL
#define CVRP_DATA_MODEL

#include "cvrp_idataModel.h"
#include "json/json.h"

namespace cvrp
{
class DataModel : public IDataModel
{
    public:
        DataModel(std::stringstream& jsonData);

        double distanceBetweenClients(int client1Id, int client2Id);
        int vehicleCapacity() { return m_vehicleCpacity; }
        Coord& depot() { return m_depot; }
        int getClientDemand(int clientId);
        Coord getClientLocation(int clientId);
        int numberOfClients();
        void getClients(std::vector<int>& clients);
        double getClientDistanceFromDepot(int clientId);

    private:
        Clients m_clientDemands;
        int m_vehicleCpacity;
        Coord m_depot;
        void populateData(Json::Value& jsonObj);
};

}//cvrp namespace
#endif