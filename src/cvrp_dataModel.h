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

        double distanceBetweenClients(int client1Id, int client2Id) const;
        int vehicleCapacity() const { return m_vehicleCpacity; }
        Coord depot() const { return m_depot; }
        int getClientDemand(int clientId) const;
        Coord getClientLocation(int clientId) const;
        int numberOfClients() const;
        void getClients(std::vector<int>& clients) const;
        double getClientDistanceFromDepot(int clientId) const;

    private:
        Clients m_clientDemands;
        int m_vehicleCpacity;
        Coord m_depot;
        void populateData(Json::Value& jsonObj);
};

}//cvrp namespace
#endif