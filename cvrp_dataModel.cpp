#include "cvrp_dataModel.h"
#include "json/json.h"

#include <iostream>
#include <assert.h>

namespace cvrp
{

DataModel::DataModel(std::stringstream& jsonData) 
{
    Json::Value root;
    jsonData >> root;
    std::cout << root << std::endl;
    m_vehicleCpacity = root.get("vehicleCapacity", -1).asInt();
    assert(m_vehicleCpacity > 0 && "Invalid data OR failed to read ");
}

}//cvrp namespace