#include "cvrp_dataModel.h"

#include <assert.h>

#include "cvrp_util.h"

namespace cvrp
{

DataModel::DataModel(std::stringstream& jsonData) 
{
    Json::Value root;
    jsonData >> root;
    populateData(root);
}


double DataModel::distanceBetweenClients(int client1Id, int client2Id)
{
    assert(m_clientDemands.find(client1Id) != m_clientDemands.end() 
            && m_clientDemands.find(client2Id) != m_clientDemands.end()
            && "Invalid Clinet IDs");
    Client c1 = m_clientDemands[client1Id];
    Client c2 = m_clientDemands[client2Id];
    return Util::distance(c1.position.first, c1.position.second, c2.position.first, c2.position.second);
}

int DataModel::getCapacityOfClient(int clientId)
{
    assert(m_clientDemands.find(clientId) != m_clientDemands.end());
    return m_clientDemands[clientId].demand;
}

Coord DataModel::getClientLocation(int clientId)
{
    assert(m_clientDemands.find(clientId) != m_clientDemands.end());
    return m_clientDemands[clientId].position;
}

void DataModel::populateData(Json::Value& jsonObj)
{
    m_vehicleCpacity = jsonObj.get("vehicleCapacity", -1).asInt();
    assert(m_vehicleCpacity > 0 && "Invalid data OR failed to read ");

    int dx = jsonObj["depot"].get("x", -1).asInt();
    int dy = jsonObj["depot"].get("y", -1).asInt();
    assert(dx >= 0 && dy >= 0 && "Invalid Data OR error parsing json for 'depot'");
    m_depot = std::pair<int, int>(dx, dy);

    Json::Value& clients = jsonObj["nodes"];
    for (unsigned int i = 0; i < clients.size(); i++)
    {
        Client currClient;
        int x = clients[i].get("x", -1).asInt();
        int y = clients[i].get("y", -1).asInt();
        int demand = clients[i].get("demand", -1).asInt();
        assert(x >= 0 && y >= 0 && demand > 0 && "Invalid Data OR error parsing json");

        currClient.position = std::pair<int, int>(x, y);
        currClient.demand = demand;

        m_clientDemands.insert(std::make_pair(i+1, currClient));
    }
}

}//cvrp namespace