#include "ConstantVectors.h"
#include <vector>

using namespace std;

vector<int> ConstantVectors::getZeroVector(int size)
{
    vector<int> vector;
    for (int i = 0; i < size; i++)
        vector.push_back(0);
    return vector;
}

vector<int> ConstantVectors::getUnitVector(int size)
{
    vector<int> vector;
    for (int i = 0; i < size; i++)
        vector.push_back(1);
    return vector;
}
