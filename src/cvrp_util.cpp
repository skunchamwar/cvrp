#include "cvrp_util.h"

#include <math.h>

namespace cvrp
{

double Util::distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

void Util::swapElements(std::vector<int>& arr, int index1, int index2)
{
    int temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}

}//cvrp namespace