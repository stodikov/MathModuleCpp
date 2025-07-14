#include "NodeCopy.h"
#include "TypesNode.h"

Node* NodeCopy::copyNode(Node* node)
{
	Node* copyNode;
	if (node->type == TypesNode::DISJUNCTION) {
		vector<Node*> newVariables(node->variables);
		copyNode = new Node(node->type, newVariables);
		return copyNode;
	}
	vector<int> newParameters(node->parametersVector);
	copyNode = new Node(node->type, newParameters);
    return copyNode;
}
