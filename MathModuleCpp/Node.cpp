#include "Node.h"
#include <stdlib.h>
#include <vector>

using namespace std;

Node::Node(int type, vector<int> parametersVector, vector<Node*> variables) {
	this->type = type;
	this->parametersVector = parametersVector;
	this->variables = variables;
}

Node::Node(int type, vector<Node*> variables) {
	this->type = type;
	this->parametersVector = vector<int>();
	this->variables = variables;
}

Node::Node(int type, vector<int> parametersVector) {
	this->type = type;
	this->parametersVector = parametersVector;
	this->variables = vector<Node*>();
}

Node::Node() {
	this->type = 0;
	this->parametersVector = vector<int>();
	this->variables = vector<Node*>();
}

int Node::getCountParameters()
{
	int count = 0;
	vector<int> parameters = this->parametersVector;
	for (int i : parameters) {
		count += i;
	}
	return count;
}
