#include "ParametersBF.h"
#include "GeneralFunctions.h"
#include <iostream>

using namespace std;

GeneralFunctions GF;

ParametersBF::ParametersBF(vector<string> coefficientsMO, vector<string> unknownsMO)
{
    this->coefficients = this->createListParameters(coefficientsMO, false);
    this->unknowns = this->createListParameters(unknownsMO, false);
    this->arbitraries = this->createListArbitraries(unknownsMO.size(), false);
    vector<string> coefficientsWithNeg = this->createListParameters(coefficientsMO, true);
    vector<string> unknownsWithNeg = this->createListParameters(unknownsMO, true);
    vector<string> arbitraries = this->createListArbitraries(unknownsMO.size(), true);
    this->parameters = unionParameters(coefficientsWithNeg, unknownsWithNeg, arbitraries);
}

vector<string> ParametersBF::unionParameters(vector<string> coefficients, vector<string> unknowns, vector<string> arbitraries)
{
    vector<string> parameters;
    for (string coefficient : coefficients) parameters.push_back(coefficient);
    for (string unknow : unknowns) parameters.push_back(unknow);
    for (string arbitrary : arbitraries) parameters.push_back(arbitrary);
    return parameters;
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

vector<string> ParametersBF::createListParameters(vector<string> parameters, bool withNeg) {
    vector<string> list;
    for (int i = 0; i < parameters.size(); i++) {
        for (int j = 0; j < 3; j++) {
            list.push_back(parameters[i] + to_string(j + 1));
            if (withNeg) {
                list.push_back("~" + parameters[i] + to_string(j + 1));
            }
        }
    }
    return list;
}

vector<string> ParametersBF::createListArbitraries(int count, bool withNeg)
{
    string designation = "A";
    vector<string> arbitraries;
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < 3; j++) {
            arbitraries.push_back(designation + "_" + to_string(i + 1) + to_string(j + 1));
            if (withNeg) {
                arbitraries.push_back("~" + designation + " " + to_string(i + 1) + to_string(j + 1));
            }
        }
    }
    return arbitraries;
}

void ParametersBF::printParameters()
{
    vector<string> list = this->parameters;
    for (int i = 0; i < list.size(); i++) {
        cout << list[i] << " ";
    }
    cout << "\n";
}

vector<int> ParametersBF::getIndexesUnknowns() {
    vector<string> parameters = this->parameters;
    vector<string> unknowns = this->unknowns;
    vector<int> result;
    for (int i = 0; i < parameters.size(); i++) {
        if (GF.checkElementInVector(unknowns, parameters[i])) {
            result.push_back(i);
        }
    }
    return result;
}