#include "NodeResiadual.h"
#include "Node.h"
#include "ConstantVectors.h"
#include "TypesNode.h"
#include "NodeOperations.h"
#include "NodeCopy.h"
#include "Console.h"
#include <iostream>

Node* NodeResiadual::calculateGeneralResidual(Node* node, vector<int> indexes) {
	ConstantVectors CV;
	NodeOperations NO;
	vector<Node*> residuals;
	int limit = (int)pow(2, indexes.size());
	for (int i = 0; i < limit; i++) {
		vector<int> binarySet = getBinarySet(i, indexes.size());
		Node* residual = calculateResidual(node, indexes, binarySet);
		if (residual->type == TypesNode::CONSTANT && residual->parametersVector[0] == 0) {
			residuals.clear();
			return residual;
		}
		if (residual->type != TypesNode::CONSTANT) {
			residuals.push_back(residual);
		}
		binarySet.clear();
	}
	if (residuals.empty()) {
		return new Node(TypesNode::CONSTANT, CV.getUnitVector(66));
	}
	if (residuals.size() == 1) {
		return residuals[0];
	}
	Node* newNode = residuals[0];
	for (int i = 1; i < residuals.size(); i++) {
		cout << i << "\n";
		newNode = NO.calculateNode(newNode, residuals[i]);
	}
	residuals.clear();
	return newNode;
}

Node* NodeResiadual::calculateResidual(Node* node, vector<int> indexes, vector<int> binarySet)
{
	Node* copyNode = NodeCopy::copyNode(node);
	Node* newNode;
	if (node->type == TypesNode::PARAMETER || node->type == TypesNode::CONJUNCTION) {
		newNode = residualNode(copyNode, indexes, binarySet);
	}
	newNode = residualDisjunction(copyNode, indexes, binarySet);
	return newNode;
}

Node* NodeResiadual::residualNode(Node* node, vector<int> indexes, vector<int> binarySet)
{
	ConstantVectors CV;
	vector<int> parameters = node->parametersVector;
	int index = 0, bit = 0;
	for (int i = 0; i < indexes.size(); i++) {
		index = indexes[i];
		bit = binarySet[i];
		if (parameters[index] == 1) {
			if (bit == 1) {
				parameters[index] = 0;
			}
			else {
				return new Node(TypesNode::CONSTANT, CV.getZeroVector(66));
			}
		}
		if (parameters[index + 1] == 1) {
			if (bit == 0) {
				parameters[index + 1] = 0;
			}
			else {
				return new Node(TypesNode::CONSTANT, CV.getZeroVector(66));
			}
		}
	}
	return new Node(node->type, parameters);
}

Node* NodeResiadual::residualDisjunction(Node* node, vector<int> indexes, vector<int> binarySet)
{
	ConstantVectors CV;
	vector<Node*> variables = node->variables;
	vector<Node*> newVariables;
	for (Node* variable : variables) {
		Node* newNode = residualNode(variable, indexes, binarySet);
		if (newNode->type != TypesNode::CONSTANT) {
			newVariables.push_back(newNode);
		}
	}
	if (newVariables.empty()) {
		return new Node(TypesNode::CONSTANT, CV.getZeroVector(66));
	}
	return new Node(node->type, newVariables);
}

vector<int> NodeResiadual::getBinarySet(int value, int size)
{
	vector<int> binarySet;
	if (value == 0) {
		binarySet.insert(binarySet.begin(), 0);
	}
	while (value > 0) {
		int bit = value % 2 == 0 ? 0 : 1;
		binarySet.insert(binarySet.begin(), bit);
		value /= 2;
	}
	while (binarySet.size() < size) {
		binarySet.insert(binarySet.begin(), 0);
	}
	return binarySet;
}
