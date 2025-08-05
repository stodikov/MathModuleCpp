#include "NodeMinimization.h"
#include "TypesNode.h"
#include "ConstantVectors.h"
#include "GeneralFunctions.h"
#include <vector>
#include <algorithm>

using namespace std;

bool NodeMinimization::compareVectors(Node* first, Node* second) {
    vector<int> firstVector = first->parametersVector;
    vector<int> secondVector = second->parametersVector;
    for (int i = 0; i < firstVector.size(); i++) {
        if (firstVector[i] != secondVector[i]) {
            return secondVector[i];
        }
    }
    return false;
}

vector<Node*> NodeMinimization::sortVariablesInDisjunction(vector<Node*> variables)
{
    vector<Node*> newVariables = variables;
    sort(newVariables.begin(), newVariables.end(), compareVectors);
    return newVariables;
}

bool NodeMinimization::isEqualNodes(Node* first, Node* second)
{
    return first->type == second->type && first->key == second->key;
}

vector<Node*> NodeMinimization::minimizationVariablesInDisjunction(vector<Node*> variables)
{
    vector<Node*> newVariables = sortVariablesInDisjunction(variables);
    /*for (int i = 0; i < variables.size(); i++) {
        vector<int> vector = variables[i]->parametersVector;
        for (int j = 0; j < vector.size(); j++) {
            cout << vector[j];
        }
        cout << "\n";
    }*/
    newVariables = deleteRepeatVariables(newVariables);
    newVariables = reducingVariables(newVariables);
    //system("cls");
    return newVariables;
}

vector<Node*> NodeMinimization::deleteRepeatVariables(vector<Node*> variables)
{
    ConstantVectors CV;
    vector<Node*> result;
    for (int i = 0; i < variables.size(); i++) {
        if (variables[i]->type == TypesNode::CONSTANT) continue;
        else result.push_back(variables[i]);

        for (int j = i + 1; j < variables.size(); j++) {
            if (isEqualNodes(variables[i], variables[j])) {
                variables[j]->~Node();
                variables[j] = new Node(TypesNode::CONSTANT, CV.getZeroVector(66));
            }
        }
    }
    return result;
}

vector<Node*> NodeMinimization::reducingVariables(vector<Node*> variables)
{
    vector<Node*> result;
    ConstantVectors CV;
    for (int i = 0; i < variables.size(); i++) {
        if (variables[i]->type == TypesNode::CONSTANT) continue;
        else result.push_back(variables[i]);

        for (int j = i + 1; j < variables.size(); j++) {
            if (isInclude(variables[i], variables[j])) {
                variables[j]->~Node();
                variables[j] = new Node(TypesNode::CONSTANT, CV.getZeroVector(66));
            }
        }
    }
    return result;
}

bool NodeMinimization::isInclude(Node* first, Node* second)
{
    vector<unsigned int> firstKey = first->key;
    vector<unsigned int> secondKey = second->key;
    vector<unsigned int> result;

    for (int i = 0; i < firstKey.size(); i++) {
        result.push_back(firstKey[i] & secondKey[i]);
    }
    return result == firstKey;
}
