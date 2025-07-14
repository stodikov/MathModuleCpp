#include "NodeNegative.h"
#include "ConstantVectors.h"
#include "TypesNode.h"
#include "NodeOperations.h"
#include "NodeMinimization.h"

Node* NodeNegative::calculateNode(Node* node)
{
	switch (node->type) {
		case TypesNode::CONSTANT:
			return negativeConstant(node);
		case TypesNode::PARAMETER:
			return negativeParameter(node);
		case TypesNode::CONJUNCTION:
			return negativeConjunction(node);
		case TypesNode::DISJUNCTION:
			return negativeDisjunction(node);
	}
}

Node* NodeNegative::negativeConstant(Node* constant)
{
	vector<int> newVector;
	if (constant->parametersVector[0] == 0) {
		newVector = ConstantVectors::getUnitVector(66);
	}
	newVector = ConstantVectors::getZeroVector(66);
	return new Node(TypesNode::CONSTANT, newVector);
}

Node* NodeNegative::negativeParameter(Node* parameter)
{
	vector<int> currentVector = parameter->parametersVector;
	vector<int> newVector;
	for (int i = 0; i < currentVector.size(); i += 2) {
		if (currentVector[i] == currentVector[i + 1]) {
			newVector.push_back(currentVector[i]);
			newVector.push_back(currentVector[i + 1]);
			continue;
		}
		newVector.push_back(currentVector[i + 1]);
		newVector.push_back(currentVector[i]);
	}
	currentVector.clear();
	return new Node(parameter->type, newVector);
}

Node* NodeNegative::negativeConjunction(Node* conjunction)
{
	vector<int> currentVector = conjunction->parametersVector;
	vector<Node*> newVariables;
	for (int i = 0; i < currentVector.size(); i += 2) {
		if (currentVector[i] == currentVector[i + 1]) {
			continue;
		}
		vector<int> newVector = ConstantVectors::getZeroVector(66);
		newVector[i] = currentVector[i];
		newVector[i + 1] = currentVector[i + 1];
		Node* newParameter = new Node(TypesNode::PARAMETER, newVector);
		newVariables.push_back(negativeParameter(newParameter));
	}
	currentVector.clear();
	newVariables = NodeMinimization::minimizationVariablesInDisjunction(newVariables);
	if (newVariables.size() > 1) return new Node(TypesNode::DISJUNCTION, newVariables);
	return newVariables[0];
}

Node* NodeNegative::negativeDisjunction(Node* disjunction)
{
	vector<Node*> currentVariables = disjunction->variables;
	vector<Node*> newVariables;
	for (Node* variable : currentVariables) {
		newVariables.push_back(calculateNode(variable));
	}
	Node* newNode = nullptr;
	for (Node* variable : newVariables) {
		if (newNode == nullptr) {
			newNode = variable;
		}
		else {
			newNode = NodeOperations::calculateNode(newNode, variable);
		}
	}
	currentVariables.clear();
	return newNode;
}