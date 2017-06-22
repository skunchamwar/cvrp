#ifndef CVRP_DATA_MODEL
#define CVRP_DATA_MODEL

#include <map>
#include <sstream>

#include "json/json.h"

namespace cvrp
{
typedef std::pair<unsigned int, unsigned int> Coord;
struct Client
{
    Coord position;
    int demand;
};

class DataModel
{
    public:
        DataModel(std::stringstream& jsonData);

        double distanceBetweenClients(int client1Id, int client2Id);
        int vehicleCapacity() { return m_vehicleCpacity; }
        Coord& depot() { return m_depot; }
        int getCapacityOfClient(int clientId);
        Coord getClientLocation(int clientId);

    private:
        std::map<int, Client> m_clientDemands;
        int m_vehicleCpacity;
        Coord m_depot;
        void populateData(Json::Value& jsonObj);
};

}//cvrp namespace
#endif