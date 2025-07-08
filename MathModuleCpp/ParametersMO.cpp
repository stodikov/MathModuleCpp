#include "ParametersMO.h"
#include <iostream>

using namespace std;

ParametersMO::ParametersMO(vector<string> coefficients, vector<string> unknowns)
{
    this->coefficients = coefficients;
    this->unknowns = unknowns;
    this->parameters = unionParameters(coefficients, unknowns);
}

vector<string> ParametersMO::unionParameters(vector<string> coefficients, vector<string> unknowns)
{
    vector<string> parameters;
    for (string coefficient : coefficients) parameters.push_back(coefficient);
    for (string unknow : unknowns) parameters.push_back(unknow);
    return parameters;
}

vector<string> ParametersMO::getListParameters()
{
    return this->parameters;
}

vector<int> ParametersMO::getVectorParameters(string parameter)
{
    vector<string> list = this->parameters;
    vector<int> vector;
    for (int i = 0; i < list.size(); i++) {
        if (list[i].find(parameter) == string::npos || list[i].find("~") != string::npos)
            vector.push_back(0);
        else
            vector.push_back(1);
    }
    return vector;
}

string ParametersMO::getDesignation(vector<int> vector)
{
    int size = vector.size();
    for (int i = 0; i < size; i++) {
        if (vector[i] == 1)
            return this->parameters[i];
    }
}

