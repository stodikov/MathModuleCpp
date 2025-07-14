#include <string>
#include <vector>
#include "Node.h"

using namespace std;

#pragma once
class ParametersBF
{
public:
	ParametersBF(vector<string>, vector<string>);
	vector<string> getListParameters();
	vector<int> getVectorParameters(string);
	void printParameters();
	vector<int> getIndexesUnknowns();
	vector<Node*> getNodesArbitraries();
	vector<Node*> getNodesUnknowns();
private:
	vector<string> coefficients;
	vector<string> unknowns;
	vector<string> parameters;
	vector<string> arbitraries;
	vector<string> createListParameters(vector<string>, bool);
	vector<string> createListArbitraries(int, bool);
	vector<string> unionParameters(vector<string>, vector<string>, vector<string>);
};

