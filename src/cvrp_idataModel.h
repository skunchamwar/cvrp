#ifndef CVRP_I_DATA_MODEL
#define CVRP_I_DATA_MODEL

#include <map>
#include <vector>
#include <sstream>

namespace cvrp
{
typedef std::pair<unsigned int, unsigned int> Coord;
struct Client
{
    Coord position;
    int demand;
};

typedef std::map<int, Client> Clients;

class IDataModel
{
    public:
        virtual ~IDataModel();

        virtual double distanceBetweenClients(int client1Id, int client2Id) = 0;
        virtual int vehicleCapacity() const = 0;
        virtual Coord& depot() = 0;
        virtual int getClientDemand(int clientId) = 0;
        virtual Coord getClientLocation(int clientId) = 0;
        virtual int numberOfClients() = 0;
        virtual void getClients(std::vector<int>& clients) = 0;
        virtual double getClientDistanceFromDepot(int clientId) = 0;
};

}//cvrp namespace
#endif