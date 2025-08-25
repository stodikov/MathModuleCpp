#include "Node.h"
#include <stdlib.h>
#include <vector>
#include <cmath>

using namespace std;

Node::Node(int type, vector<int> parametersVector, vector<Node*> variables) {
	this->type = type;
	this->parametersVector = parametersVector;
	this->variables = variables;
	this->key = createKey();
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
	this->key = createKey();
}

Node::Node() {
	this->type = 0;
	this->parametersVector = vector<int>();
	this->variables = vector<Node*>();
}

Node::~Node() {
	this->parametersVector.clear();
	this->variables.clear();
	this->spaceMatrix.clear();
	this->key.clear();
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

vector<unsigned int> Node::createKey() {
	int size = (int)ceil((double)this->parametersVector.size() / 32);
	vector<unsigned int> key(size);
	for (int i = 0; i < this->parametersVector.size(); i++) {
		int partIndex = i / 32;
		int bitIndex = i % 32;
		if (this->parametersVector[i] == 1) {
			key[partIndex] |= (1U << bitIndex);
		}
	}
	return key;
}
