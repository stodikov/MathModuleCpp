#include "MinimizationNode.h"
#include "TypesNode.h"
#include "ConstantVectors.h"
#include <vector>
#include <algorithm>

using namespace std;

bool MinimizationNode::compareVectors(Node* first, Node* second) {
    vector<int> firstVector = first->parametersVector;
    vector<int> secondVector = second->parametersVector;
    for (int i = 0; i < firstVector.size(); i++) {
        if (firstVector[i] != secondVector[i]) {
            return !firstVector[i];
        }
    }
    return false;
}

void MinimizationNode::sortVariablesInDisjunction(Node* disjunction)
{
    vector<Node*> variables = disjunction->variables;
    sort(variables.begin(), variables.end(), compareVectors);
    disjunction->variables = variables;
}

bool MinimizationNode::isEqualNodes(Node* first, Node* second)
{
    if (first->type == second->type && (first->type == TypesNode::PARAMETER || first->type == TypesNode::CONJUNCTION)) {
        return first->parametersVector == second->parametersVector;
    }
    vector<Node*> firstVariables = first->variables;
    vector<Node*> secondVariables = second->variables;
    if (firstVariables.size() != secondVariables.size()) {
        return false;
    }
    for (int i = 0; i < firstVariables.size(); i++) {
        vector<int> firstVector = firstVariables[i]->parametersVector;
        vector<int> secondVector = secondVariables[i]->parametersVector;
        if (firstVector != secondVector) {
            return false;
        }
    }
    return true;
}

void MinimizationNode::minimizationVariablesInDisjunction(Node* disjunction)
{
    vector<Node*> newVariable = disjunction->variables;
    newVariable = deleteRepeatVariables(newVariable);
    newVariable = reducingVariables(newVariable);
    disjunction->variables = newVariable;
    return sortVariablesInDisjunction(disjunction);
}

vector<Node*> MinimizationNode::deleteRepeatVariables(vector<Node*> variables)
{
    ConstantVectors CV;
    vector<Node*> result;
    for (int i = 0; i < variables.size(); i++) {
        for (int j = 0; j < variables.size(); j++) {
            if (i != j && isEqualNodes(variables[i], variables[j])) {
                variables[i] = new Node(TypesNode::CONSTANT, CV.getZeroVector(48));
            }
        }
        if (variables[i]->type != TypesNode::CONSTANT || variables[i]->parametersVector[0] != 0) {
            result.push_back(variables[i]);
        }
    }
    return result;
}

vector<Node*> MinimizationNode::reducingVariables(vector<Node*> variables)
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
                variables[i] = new Node(TypesNode::CONSTANT, CV.getUnitVector(48));
            }
        }
    }
    for (Node* variable : variables) {
        if (variable->type != TypesNode::CONSTANT) {
            result.push_back(variable);
        }
    }
    return result;
}

int MinimizationNode::getMinIndex(vector<Node*> variables, vector<int> minIndexes)
{
    int minIndex = -1;
    for (int i = 0; i < variables.size(); i++) {
        if (variables[i]->type == TypesNode::CONSTANT) {
            continue;
        }
        if (minIndex == -1 && find(minIndexes.begin(), minIndexes.end(), i) == minIndexes.end()) {
            minIndex = i;
            continue;
        }
        if (variables[i]->type == TypesNode::PARAMETER && find(minIndexes.begin(), minIndexes.end(), i) == minIndexes.end()) {
            minIndex = i;
            break;
        }
        if (minIndex != -1 && variables[minIndex]->getCountParameters() < variables[i]->getCountParameters()) {
            minIndex = i;
        }
    }
    return minIndex;
}

bool MinimizationNode::isInclude(Node* first, Node* second)
{
    vector<int> firstVector = first->parametersVector;
    vector<int> secondVector = second->parametersVector;
    vector<int> result;
    for (int i = 0; i < first->parametersVector.size(); i++) {
        result.push_back(firstVector[i] | secondVector[i]);
    }
    return result == firstVector;
}
