#include "Node.h"

#pragma once
class NodeOperations
{
public:
	static Node* calculateNode(Node*, Node*);
	static Node* unionNodes(Node*, Node*);
private:
	static Node* constantAndNode(Node*, Node*);
	static Node* unionVectors(Node*, Node*);
	static Node* unionDisjunctionAndNode(Node*, Node*);
	static Node* disjunctionAndDisjunction(Node*, Node*);
};

