#include "Node.h"

using namespace std;

#pragma once
class NodeSubstitution
{
public:
	static Node* calculateNode(Node*, Node*, int);
private:
	static Node* substitutionNode(Node*, Node*, int);
	static Node* substitutionDisjunction(Node*, Node*, int);
};

