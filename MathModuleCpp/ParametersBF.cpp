#include "ParametersBF.h"
#include <iostream>

using namespace std;

ParametersBF::ParametersBF(vector<string> parametersMO)
{
    this->parameters = this->createListParameters(parametersMO);
}

vector<string> ParametersBF::getListParameters()
{
    return this->parameters;
}

vector<int> ParametersBF::getVectorParameters(string parameter)
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

vector<string> ParametersBF::createListParameters(vector<string> parametersMO) {
    vector<string> list;
    for (int i = 0; i < 16; i += 2) {
        for (int j = 0; j < 3; j++) {
            list.push_back(parametersMO[i] + to_string(j + 1));
            list.push_back("~" + parametersMO[i] + to_string(j + 1));
        }
    }
    return list;
}

void ParametersBF::printParameters()
{
    vector<string> list = this->parameters;
    for (int i = 0; i < list.size(); i++) {
        cout << list[i] << " ";
    }
    cout << "\n";
}