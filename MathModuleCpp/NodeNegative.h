#include "Node.h"

using namespace std;

#pragma once
class NodeNegative
{
public:
	static Node* calculateNode(Node*);
private:
	static Node* negativeConstant(Node*);
	static Node* negativeParameter(Node*);
	static Node* negativeConjunction(Node*);
	static Node* negativeDisjunction(Node*);
};

