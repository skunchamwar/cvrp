#include <iostream>
#include <sstream>
#include <fstream>
#include "cvrp_dataModel.h"

using namespace cvrp;

int main(int argc, char *argv[])
{
    std::cout << argv[1] << std::endl;
    std::ifstream dataFile(argv[1], std::ifstream::binary);
    std::stringstream jsonStream;
    
    jsonStream << dataFile.rdbuf();

    DataModel model(jsonStream);
    return 0;
}