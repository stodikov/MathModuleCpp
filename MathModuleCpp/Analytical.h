#include "Node.h"
#include "ParametersBF.h"
#include <map>

using namespace std;

#pragma once
class Analytical
{
public:
	static map<int, Node*> getSolution(Node*, ParametersBF*);
private:
	static Node* solvability(Node*);
	static map<int, Node*> generalSolution(Node*);
};

