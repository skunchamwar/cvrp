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

double DataModel::getClientDistanceFromDepot(int clientId) const
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

double DataModel::distanceBetweenClients(int client1Id, int client2Id) const
{
    const Clients::const_iterator c1 = m_clientDemands.find(client1Id);
    const Clients::const_iterator c2 = m_clientDemands.find(client2Id);
    if(c1 == m_clientDemands.end() || c2 == m_clientDemands.end())
    {
        std::stringstream error;
        error << "Invalid client IDs provided: " << client1Id << " and " << client2Id;
        throw std::invalid_argument(error.str());
    }
    return Util::distance(c1->second.position.first, c1->second.position.second, 
                            c2->second.position.first, c2->second.position.second);
}

int DataModel::getClientDemand(int clientId) const
{
    const Clients::const_iterator client = m_clientDemands.find(clientId);
    if(client == m_clientDemands.end())
    {
        std::stringstream error;
        error << "Invalid client ID provided: " << clientId;
        throw std::invalid_argument(error.str());
    }
    return client->second.demand;
}

Coord DataModel::getClientLocation(int clientId) const
{
    const Clients::const_iterator client = m_clientDemands.find(clientId);
    if(client == m_clientDemands.end())
    {
        std::stringstream error;
        error << "Invalid client ID provided: " << clientId;
        throw std::invalid_argument(error.str());
    }
    return client->second.position;
}

int DataModel::numberOfClients() const
{
    return m_clientDemands.size();
}

void DataModel::getClients(std::vector<int>& clients) const
{
    for (auto const &it : m_clientDemands)
    {
        clients.push_back(it.first);
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
    int id = 1;
    for (auto client : clients)
    {
        Client currClient;
        int x = client.get("x", -1).asInt();
        int y = client.get("y", -1).asInt();
        int demand = client.get("demand", -1).asInt();
        if (x < 0 || y < 0 || demand < 0)
        {
            std::stringstream error;
            error << "Invalid Data OR error parsing json for client: " << client;
            throw std::invalid_argument(error.str());
        }

        currClient.position = std::pair<int, int>(x, y);
        currClient.demand = demand;

        m_clientDemands.insert(std::make_pair(id++, currClient));
    }
}

}//cvrp namespace