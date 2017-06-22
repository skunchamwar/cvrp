#ifndef CVRP_DATA_MODEL
#define CVRP_DATA_MODEL

#include <map>
#include <sstream>

namespace cvrp
{
typedef std::pair<unsigned int, unsigned int> coord;
class DataModel
{
    public:
        DataModel(std::stringstream& jsonData);

    private:
        std::map<coord, int> m_demand;
        int m_vehicleCpacity;
};

}//cvrp namespace
#endif