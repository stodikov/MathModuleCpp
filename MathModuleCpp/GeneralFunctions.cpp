#include "GeneralFunctions.h"
#include <iostream>

bool GeneralFunctions::checkElementInVector(vector<int> elements, int element)
{
	return find(elements.begin(), elements.end(), element) != elements.end();
}

bool GeneralFunctions::checkElementInVector(vector<string> elements, string element)
{
	return find(elements.begin(), elements.end(), element) != elements.end();
}