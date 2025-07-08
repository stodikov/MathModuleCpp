#include "NodeOperations.h"
#include "TypesNode.h"
#include "ConstantVectors.h"
#include "NodeMinimization.h"

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
    vector<int> variablesFirst = constant->parametersVector;
    if (variablesFirst[0] == 0) return constant;
    return node;
}

Node* NodeOperations::unionVectors(Node* first, Node* second)
{
    vector<int> firstVector = first->parametersVector;
    vector<int> secondVector = second->parametersVector;
    vector<int> newVector;
    for (int i = 0; i < firstVector.size(); i++)
        newVector.push_back(firstVector[i] | secondVector[i]);
    return new Node(TypesNode::CONJUNCTION, newVector);
}

Node* NodeOperations::unionDisjunctionAndNode(Node* disjunction, Node* node)
{
    vector<Node*> variables = disjunction->variables;
    vector<Node*> newVariables;
    for (Node* variable : variables) {
        newVariables.push_back(unionVectors(node, variable));
    }
    newVariables = NM.minimizationVariablesInDisjunction(newVariables);
    return new Node(TypesNode::DISJUNCTION, newVariables);
}

Node* NodeOperations::disjunctionAndDisjunction(Node* first, Node* second)
{
    vector<Node*> firstVariables = first->variables;
    vector<Node*> secondVariables = second->variables;
    vector<Node*> newVariables;
    Node* stepNode;
    for (Node* variable : firstVariables) {
        stepNode = unionDisjunctionAndNode(second, variable);
        newVariables.insert(newVariables.end(), stepNode->variables.begin(), stepNode->variables.end());
    }
    newVariables = NM.minimizationVariablesInDisjunction(newVariables);
    return new Node(TypesNode::DISJUNCTION, newVariables);
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
    return new Node(TypesNode::DISJUNCTION, newVariables);
}