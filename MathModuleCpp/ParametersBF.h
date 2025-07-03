#include <string>
#include <vector>

using namespace std;

#pragma once
class ParametersBF
{
public:
	ParametersBF(vector<string>);
	vector<string> getListParameters();
	vector<int> getVectorParameters(string);
	void printParameters();
private:
	vector<string> parameters;
	vector<string> createListParameters(vector<string>);
};

