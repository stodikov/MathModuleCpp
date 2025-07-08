#include "Node.h"
#include <vector>

using namespace std;

#pragma once
class NodeMinimization
{
public:
	static vector<Node*> sortVariablesInDisjunction(vector<Node*>);
	static bool isEqualNodes(Node*, Node*);
	static vector<Node*> minimizationVariablesInDisjunction(vector<Node*>);
private:
	static vector<Node*> deleteRepeatVariables(vector<Node*>);
	static vector<Node*> reducingVariables(vector<Node*>);
	static bool compareVectors(Node*, Node*);
	static int getMinIndex(vector<Node*>, vector<int>);
	static bool isInclude(Node*, Node*);
};
