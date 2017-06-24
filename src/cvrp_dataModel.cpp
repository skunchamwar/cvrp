#include "cvrp_dataModel.h"

#include <stdexcept>
#include "cvrp_util.h"

namespace cvrp
{

DataModel::DataModel(std::stringstream& jsonData) 
{
    Json::Value root;
    jsonData >> root;
    populateData(root);
}

double DataModel::getClientDistanceFromDepot(int clientId)
{
    Clients::const_iterator it = m_clientDemands.find(clientId);
    if(it == m_clientDemands.end())
    {
        std::stringstream error;
        error << "Invalid client ID provided: " << clientId;
        throw std::invalid_argument(error.str());
    }
    return Util::distance(m_depot.first, m_depot.second, it->second.position.first, it->second.position.second);
}

double DataModel::distanceBetweenClients(int client1Id, int client2Id)
{
    if(m_clientDemands.find(client1Id) == m_clientDemands.end() 
            || m_clientDemands.find(client2Id) == m_clientDemands.end())
    {
        std::stringstream error;
        error << "Invalid client IDs provided: " << client1Id << " and " << client2Id;
        throw std::invalid_argument(error.str());
    }
    Client c1 = m_clientDemands[client1Id];
    Client c2 = m_clientDemands[client2Id];
    return Util::distance(c1.position.first, c1.position.second, c2.position.first, c2.position.second);
}

int DataModel::getClientDemand(int clientId)
{
    if(m_clientDemands.find(clientId) == m_clientDemands.end())
    {
        std::stringstream error;
        error << "Invalid client ID provided: " << clientId;
        throw std::invalid_argument(error.str());
    }
    return m_clientDemands[clientId].demand;
}

Coord DataModel::getClientLocation(int clientId)
{
    if(m_clientDemands.find(clientId) == m_clientDemands.end())
    {
        std::stringstream error;
        error << "Invalid client ID provided: " << clientId;
        throw std::invalid_argument(error.str());
    }
    return m_clientDemands[clientId].position;
}

int DataModel::numberOfClients()
{
    return m_clientDemands.size();
}

void DataModel::getClients(std::vector<int>& clients)
{
    for (Clients::const_iterator it = m_clientDemands.begin();
            it != m_clientDemands.end(); ++it)
    {
        clients.push_back(it->first);
    }
}

void DataModel::populateData(Json::Value& jsonObj)
{
    m_vehicleCpacity = jsonObj.get("vehicleCapacity", -1).asInt();
    if (m_vehicleCpacity < 0)
    {
        std::stringstream error;
        error << "Invalid Vehicle Capacity: " << m_vehicleCpacity;
        throw std::invalid_argument(error.str());
    }

    int dx = jsonObj["depot"].get("x", -1).asInt();
    int dy = jsonObj["depot"].get("y", -1).asInt();
    if (dx < 0 || dy < 0)
    {
        std::stringstream error;
        error << "Invalid Data OR error parsing json for 'depot'" << jsonObj["depot"];
        throw std::invalid_argument(error.str());
    }
    m_depot = std::pair<int, int>(dx, dy);

    Json::Value& clients = jsonObj["nodes"];
    for (unsigned int i = 0; i < clients.size(); i++)
    {
        Client currClient;
        int x = clients[i].get("x", -1).asInt();
        int y = clients[i].get("y", -1).asInt();
        int demand = clients[i].get("demand", -1).asInt();
        if (x < 0 || y < 0 || demand < 0)
        {
            std::stringstream error;
            error << "Invalid Data OR error parsing json for client: " << clients[i];
            throw std::invalid_argument(error.str());
        }

        currClient.position = std::pair<int, int>(x, y);
        currClient.demand = demand;

        m_clientDemands.insert(std::make_pair(i+1, currClient));
    }
}

}//cvrp namespace