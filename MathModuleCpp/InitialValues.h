#include <string>
#include <vector>
#include "Node.h"
#include "ParametersMO.h"

using namespace std;

#pragma once
class InitialValues
{
public:
	vector<string> getCoefficientsMO();
	vector<string> getUnknownsMO();
	vector<Node*> getSystemInclusions(ParametersMO*);
};

