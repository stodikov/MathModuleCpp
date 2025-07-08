#include <string>
#include <vector>

using namespace std;

#pragma once
class ParametersMO
{
public:
	ParametersMO(vector<string>, vector<string>);
	vector<string> getListParameters();
	vector<int> getVectorParameters(string);
	string getDesignation(vector<int>);
private:
	vector<string> coefficients;
	vector<string> unknowns;
	vector<string> parameters;
	vector<string> unionParameters(vector<string>, vector<string>);
};

