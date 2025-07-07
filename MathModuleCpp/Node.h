#include <vector>

using namespace std;

#pragma once
class Node
{
public:
	Node(int, vector<int>, vector<Node*>);
	Node(int, vector<Node*>);
	Node(int, vector<int>);
	Node();
	int type;
	vector<int> parametersVector;
	vector<Node*> variables;
	vector<Node*> spaceMatrix;
	int getCountParameters();
};

