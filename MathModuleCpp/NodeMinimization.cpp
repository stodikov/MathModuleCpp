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
            return firstVector[i];
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
    if (first->type != second->type) {
        return false;
    }
    return first->key == second->key;
    /*if (first->type == TypesNode::PARAMETER || first->type == TypesNode::CONJUNCTION || first->type == TypesNode::CONSTANT) {
        return first->parametersVector == second->parametersVector;
    }
    if (first->getCountParameters() != second->getCountParameters()) {
        return false;
    }
    vector<Node*> firstVariables = first->variables;
    vector<Node*> secondVariables = second->variables;
    for (int i = 0; i < firstVariables.size(); i++) {
        vector<int> firstVector = firstVariables[i]->parametersVector;
        vector<int> secondVector = secondVariables[i]->parametersVector;
        if (firstVector != secondVector) {
            return false;
        }
    }
    return true;
    */
}

vector<Node*> NodeMinimization::minimizationVariablesInDisjunction(vector<Node*> variables)
{
    vector<Node*> newVariable = variables;
    newVariable = deleteRepeatVariables(newVariable);
    newVariable = reducingVariables(newVariable);
    return sortVariablesInDisjunction(newVariable);
}

vector<Node*> NodeMinimization::deleteRepeatVariables(vector<Node*> variables)
{
    ConstantVectors CV;
    vector<Node*> result;
    for (int i = 0; i < variables.size(); i++) {
        for (int j = 0; j < variables.size(); j++) {
            if (i != j && isEqualNodes(variables[i], variables[j])) {
                variables[i]->~Node();
                variables[i] = new Node(TypesNode::CONSTANT, CV.getZeroVector(66));
            }
        }
        if (variables[i]->type != TypesNode::CONSTANT || variables[i]->parametersVector[0] != 0) {
            result.push_back(variables[i]);
        }
    }
    return result;
}

vector<Node*> NodeMinimization::reducingVariables(vector<Node*> variables)
{
    vector<int> minIndexes;
    vector<Node*> result;
    ConstantVectors CV;
    bool running = true;
    while (running) {
        int minIndex = getMinIndex(variables, minIndexes);
        if (minIndex == -1) {
            running = false;
            continue;
        }
        minIndexes.push_back(minIndex);
        Node* minNode = variables[minIndex];
        for (int i = 0; i < variables.size(); i++) {
            if (i == minIndex) {
                continue;
            }
            if (isInclude(variables[minIndex], variables[i])) {
                variables[i]->~Node();
                variables[i] = new Node(TypesNode::CONSTANT, CV.getUnitVector(66));
            }
        }
    }
    for (Node* variable : variables) {
        if (variable->type != TypesNode::CONSTANT) {
            result.push_back(variable);
        }
    }
    minIndexes.clear();
    return result;
}

int NodeMinimization::getMinIndex(vector<Node*> variables, vector<int> minIndexes)
{
    GeneralFunctions GF;
    int minIndex = -1;
    for (int i = 0; i < variables.size(); i++) {
        if (variables[i]->type == TypesNode::CONSTANT) {
            continue;
        }
        if (minIndex == -1 && !GF.checkElementInVector(minIndexes, i)) {
            minIndex = i;
            continue;
        }
        if (minIndex != -1 && !GF.checkElementInVector(minIndexes, i)) {
            vector<unsigned int> keyI = variables[i]->key;
            vector<unsigned int> keyMin = variables[minIndex]->key;

            for (int j = 0; j < keyI.size(); j++) {
                if (keyMin[j] > keyI[j]) {
                    minIndex = i;
                    break;
                }
            }
        }
        /*if (variables[i]->type == TypesNode::PARAMETER && !GF.checkElementInVector(minIndexes, i)) {
            minIndex = i;
            break;
        }
        if (minIndex != -1 && variables[minIndex]->getCountParameters() > variables[i]->getCountParameters() && !GF.checkElementInVector(minIndexes, i)) {
            minIndex = i;
        }*/
    }
    return minIndex;
}

bool NodeMinimization::isInclude(Node* first, Node* second)
{
    /*vector<int> firstVector = first->parametersVector;
    vector<int> secondVector = second->parametersVector;*/

    vector<unsigned int> firstKey = first->key;
    vector<unsigned int> secondKey = second->key;
    vector<unsigned int> result;
    for (int i = 0; i < firstKey.size(); i++) {
        result.push_back(firstKey[i] & secondKey[i]);
    }
    return result == firstKey;
}
