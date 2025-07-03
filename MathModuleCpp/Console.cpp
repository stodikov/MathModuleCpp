#include "Console.h"
#include "Node.h"
#include "TypesNode.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

string Console::ConsoleNode(Node* node, vector<string> parameters)
{
	string formula = "";
	if (node->type == TypesNode::CONSTANT) {
		formula += ConsoleConstant(node);
	}
	if (node->type == TypesNode::PARAMETER || node->type == TypesNode::CONJUNCTION) {
		formula += ConsoleConjunction(node, parameters);
	}
	if (node->type == TypesNode::DISJUNCTION) {
		vector<Node*> variables = node->variables;
		for (Node* variable : variables) {
			formula += ConsoleNode(variable, parameters) + "V";
		}
		formula.pop_back();
	}
	return formula;
}

string Console::ConsoleConstant(Node* constant) {
	int c = constant->parametersVector[0] == 0 ? 0 : 1;
	return "(" + to_string(c) + ")";
}

string Console::ConsoleConjunction(Node* conjunction, vector<string> parameters) {
	string formula = "(";
	vector<int> vectorParameters = conjunction->parametersVector;
	for (int i = 0; i < vectorParameters.size(); i++) {
		if (vectorParameters[i]) {
			formula += parameters[i] + "&";
		}
	}
	formula.pop_back();
	formula += ")";
	return formula;
}
