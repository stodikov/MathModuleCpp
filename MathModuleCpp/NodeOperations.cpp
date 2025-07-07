#include "NodeOperations.h"
#include "TypesNode.h"
#include "ConstantVectors.h"

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
    vector<int> vectorFirst = first->parametersVector;
    vector<int> vectorSecond = second->parametersVector;
    vector<int> vectorNew;
    for (int i = 0; i < vectorFirst.size(); i++)
        vectorNew.push_back(vectorFirst[i] | vectorSecond[i]);
    return new Node(TypesNode::CONJUNCTION, vectorNew);
}

Node* NodeOperations::unionDisjunctionAndNode(Node* disjunction, Node* node)
{
    vector<Node*> variables = disjunction->variables;
    vector<Node*> newVariables;
    for (Node* variable : variables) {
        newVariables.push_back(unionVectors(node, variable));
    }
    return new Node(TypesNode::DISJUNCTION, newVariables);
}

Node* NodeOperations::disjunctionAndDisjunction(Node* first, Node* second)
{
    vector<Node*> variablesFirst = first->variables;
    vector<Node*> variablesSecond = second->variables;
    vector<Node*> newVariables;
    Node* stepNode;
    for (Node* variableFirst : variablesFirst) {
        stepNode = unionDisjunctionAndNode(second, variableFirst);
        newVariables.insert(newVariables.end(), stepNode->variables.begin(), stepNode->variables.end());
    }
    return new Node(TypesNode::DISJUNCTION, newVariables);
}

Node* NodeOperations::unionNodes(Node* first, Node* second)
{
    vector<Node*> variableNew;
    vector<Node*> variablesFirst = first->variables;
    vector<Node*> variablesSecond = second->variables;
    if (first->type == TypesNode::PARAMETER || first->type == TypesNode::CONJUNCTION) {
        if (second->type == TypesNode::PARAMETER || second->type == TypesNode::CONJUNCTION) {
            return new Node(TypesNode::DISJUNCTION, vector<Node*>{first, second});
        }
        for (Node* variable : variablesSecond) variableNew.push_back(variable);
        variableNew.push_back(first);
        return new Node(TypesNode::DISJUNCTION, variableNew);
    }
    if (second->type == TypesNode::PARAMETER || second->type == TypesNode::CONJUNCTION) {
        for (Node* variable : variablesFirst) variableNew.push_back(variable);
        variableNew.push_back(second);
        return new Node(TypesNode::DISJUNCTION, variableNew);
    }
    for (Node* variable : variablesFirst) variableNew.push_back(variable);
    for (Node* variable : variablesSecond) variableNew.push_back(variable);
    //variablesFirst.insert(variablesFirst.end(), variablesSecond.begin(), variablesSecond.end());
    return new Node(TypesNode::DISJUNCTION, variableNew);
}
