#include "NodeOperations.h"
#include "TypesNode.h"
#include "ConstantVectors.h"
#include "NodeMinimization.h"
#include "NodeCopy.h"
#include <iostream>

using namespace std;

NodeMinimization NM;

Node* NodeOperations::calculateNode(Node* first, Node* second)
{
    if (first->type == TypesNode::CONSTANT) {
        return constantAndNode(first, second);
    }
    if (second->type == TypesNode::CONSTANT) {
        return constantAndNode(second, first);
    }
    if (first->type == TypesNode::PARAMETER || first->type == TypesNode::CONJUNCTION) {
        if (second->type == TypesNode::PARAMETER || second->type == TypesNode::CONJUNCTION)
            return unionVectors(first, second);

        return unionDisjunctionAndNode(second, first);
    }
    if (first->type == TypesNode::DISJUNCTION) {
        if (second->type == TypesNode::PARAMETER || second->type == TypesNode::CONJUNCTION)
            return unionDisjunctionAndNode(first, second);

        return disjunctionAndDisjunction(first, second);
    }
    return nullptr;
}

Node* NodeOperations::constantAndNode(Node* constant, Node* node)
{
    if (constant->parametersVector[0] == 0) {
        return constant;
    }
    return NodeCopy::copyNode(node);
}

Node* NodeOperations::unionVectors(Node* first, Node* second)
{
    vector<int> firstVector = first->parametersVector;
    vector<int> secondVector = second->parametersVector;
    vector<int> newVector;
    int countParameters = 0, element;
    for (int i = 0; i < firstVector.size(); i++) {
        element = firstVector[i] | secondVector[i];
        countParameters += element;
        newVector.push_back(element);
        if (i % 2 != 0 && newVector[newVector.size() - 1] == newVector[newVector.size() - 2] && newVector[newVector.size() - 1] == 1) {
            return new Node(TypesNode::CONSTANT, ConstantVectors::getZeroVector(66));
        }
    }
    if (countParameters == newVector.size()) {
        return new Node(TypesNode::CONSTANT, newVector);
    }
    return new Node(TypesNode::CONJUNCTION, newVector);
}

Node* NodeOperations::unionDisjunctionAndNode(Node* disjunction, Node* node)
{
    vector<Node*> variables = disjunction->variables;
    vector<Node*> newVariables;
    Node* newNode;
    for (Node* variable : variables) {
        newNode = unionVectors(node, variable);
        if (newNode->type == TypesNode::CONSTANT && newNode->parametersVector[0] == 1) {
            return newNode;
        }
        if (newNode->type != TypesNode::CONSTANT) {
            newVariables.push_back(newNode);
        }
    }
    newVariables = NM.minimizationVariablesInDisjunction(newVariables);
    if (newVariables.size() > 1) return new Node(TypesNode::DISJUNCTION, newVariables);
    return newVariables[0];
}

Node* NodeOperations::disjunctionAndDisjunction(Node* first, Node* second)
{
    vector<Node*> firstVariables = first->variables;
    vector<Node*> newVariables;
    Node* stepNode;
    for (Node* variable : firstVariables) {
        stepNode = unionDisjunctionAndNode(second, variable);
        if (stepNode->type == TypesNode::CONSTANT && stepNode->parametersVector[0] == 1) {
            return stepNode;
        }
        if (stepNode->type == TypesNode::PARAMETER || stepNode->type == TypesNode::CONJUNCTION) {
            newVariables.push_back(stepNode);
        }
        if (stepNode->type == TypesNode::DISJUNCTION) {
            newVariables.insert(newVariables.end(), stepNode->variables.begin(), stepNode->variables.end());
        }
    }
    newVariables = NM.minimizationVariablesInDisjunction(newVariables);
    if (newVariables.size() > 1) return new Node(TypesNode::DISJUNCTION, newVariables);
    return newVariables[0];
}

Node* NodeOperations::unionNodes(Node* first, Node* second)
{
    vector<Node*> firstVariables = first->variables;
    vector<Node*> secondVariables = second->variables;
    vector<Node*> newVariables;
    if (first->type == TypesNode::PARAMETER || first->type == TypesNode::CONJUNCTION) {
        if (second->type == TypesNode::PARAMETER || second->type == TypesNode::CONJUNCTION) {
            newVariables.push_back(first);
            newVariables.push_back(second);
        }
        else {
            for (Node* variable : secondVariables) newVariables.push_back(variable);
            newVariables.push_back(first);
        }
    }
    else if (second->type == TypesNode::PARAMETER || second->type == TypesNode::CONJUNCTION) {
        for (Node* variable : firstVariables) newVariables.push_back(variable);
        newVariables.push_back(second);
    }
    else {
        for (Node* variable : firstVariables) newVariables.push_back(variable);
        for (Node* variable : secondVariables) newVariables.push_back(variable);
        //variablesFirst.insert(variablesFirst.end(), variablesSecond.begin(), variablesSecond.end());
    }
    newVariables = NM.minimizationVariablesInDisjunction(newVariables);
    if (newVariables.size() > 1) return new Node(TypesNode::DISJUNCTION, newVariables);
    return newVariables[0];
}