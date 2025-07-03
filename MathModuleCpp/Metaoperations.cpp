#include "Metaoperations.h"
#include "Multioperation.h"
#include <vector>

using namespace std;

vector<Multioperation*> Metaoperations::getMetaoperations()
{
    vector<Multioperation*> metaoperations{
        new Multioperation(3, vector<int> { 1, 1, 1, 1, 2, 4, 1, 4, 4 }),
        new Multioperation(3, vector<int> { 1, 2, 4, 2, 2, 2, 4, 2, 4 }),
        new Multioperation(3, vector<int> { 2, 1, 4 })
    };

    return metaoperations;
}
