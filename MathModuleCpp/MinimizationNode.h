#include "Node.h"
#include <vector>

using namespace std;

#pragma once
class MinimizationNode
{
public:
	static void sortVariablesInDisjunction(Node*);
	static bool isEqualNodes(Node*, Node*);
	static vector<Node*> minimizationVariablesInDisjunction(vector<Node*>);
	static vector<Node*> deleteRepeatVariables(vector<Node*>);
	static vector<Node*> reducingVariables(vector<Node*>);
private:
	static bool compareVectors(Node*, Node*);
	static int getMinIndex(vector<Node*>, vector<int>);
	static bool isInclude(Node*, Node*);
};
