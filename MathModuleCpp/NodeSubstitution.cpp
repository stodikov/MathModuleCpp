#include "NodeSubstitution.h"
#include "Node.h"
#include "TypesNode.h"
#include "NodeOperations.h"
#include "NodeNegative.h"
#include <vector>

using namespace std;

Node* NodeSubstitution::calculateNode(Node* inequality, Node* element, int index)
{
	if (inequality->type == TypesNode::DISJUNCTION) {
		return substitutionDisjunction(inequality, element, index);
	}
	return substitutionNode(inequality, element, index);
}

Node* NodeSubstitution::substitutionNode(Node* node, Node* element, int index)
{
	if (node->parametersVector[index] == 0 && node->parametersVector[index + 1] == 0) {
		return node;
	}
	if (node->parametersVector[index] == 1) {
		node->parametersVector[index] = 0;
		return NodeOperations::calculateNode(node, element);
	}
	node->parametersVector[index + 1] = 0;
	Node* negElement = NodeNegative::calculateNode(element);
	return NodeOperations::calculateNode(node, negElement);
}

Node* NodeSubstitution::substitutionDisjunction(Node* node, Node* element, int index)
{
	vector<Node*> variables = node->variables;
	vector<Node*> newVariables;
	for (Node* variable : variables) {
		Node* newNode = substitutionNode(variable, element, index);
		if (newNode->type == TypesNode::CONJUNCTION) {
			newVariables.push_back(newNode);
			continue;
		}
		for (Node* newVariable : newNode->variables) {
			newVariables.push_back(newVariable);
		}
	}
	return new Node(TypesNode::DISJUNCTION, newVariables);
}