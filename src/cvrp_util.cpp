#include "cvrp_util.h"

#include <math.h>
#include <random>

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

int Util::generateRandomNumberInRange(int min, int max)
{   
    static std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

void Util::splitAndCascade(std::vector<int>& first, std::vector<int>& second, int splitPoint)
{
    std::vector<int> firstSplit(first.begin() + splitPoint, first.end());
    std::vector<int> secondSplit(second.begin() + splitPoint, second.end());

    first.erase(first.begin() + splitPoint, first.end());
    second.erase(second.begin() + splitPoint, second.end());

    first.insert(first.end(), secondSplit.begin(), secondSplit.end());
    second.insert(second.end(), firstSplit.begin(), firstSplit.end());
}

}//cvrp namespace