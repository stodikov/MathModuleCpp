#include "Node.h"
#include <vector>

using namespace std;

#pragma once
class NodeResiadual
{
public:
	static Node* calculateGeneralResidual(Node*, vector<int>);
	static Node* calculateResidual(Node*, vector<int>, vector<int>);
private:
	static Node* residualNode(Node*, vector<int>, vector<int>);
	static Node* residualDisjunction(Node*, vector<int>, vector<int>);
	static vector<int> getBinarySet(int, int);
};

