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

        virtual double distanceBetweenClients(int client1Id, int client2Id) const  = 0;
        virtual int vehicleCapacity() const = 0;
        virtual Coord depot() const = 0;
        virtual int getClientDemand(int clientId) const = 0;
        virtual Coord getClientLocation(int clientId) const = 0;
        virtual int numberOfClients() const = 0;
        virtual void getClients(std::vector<int>& clients) const = 0;
        virtual double getClientDistanceFromDepot(int clientId) const = 0;
};

}//cvrp namespace
#endif