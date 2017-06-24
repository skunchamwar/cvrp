#ifndef CVRP_UTIL
#define CVRP_UTIL

#include <vector>

namespace cvrp
{
class Util
{
    public:
        static double distance(int x1, int y1, int x2, int y2);
        static void swapElements(std::vector<int>& arr, int index1, int index2);
};

}//cvrp namespace
#endif