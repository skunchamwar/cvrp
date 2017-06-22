#include "cvrp_util.h"

#include <math.h>

namespace cvrp
{

double Util::distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

}//cvrp namespace