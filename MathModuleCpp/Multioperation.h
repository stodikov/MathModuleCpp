#include "Node.h"
#include <vector>

using namespace std;

#pragma once
class Multioperation
{
public:
	Multioperation(int, vector<int>);
	vector<vector<Node*>> getMatrix();
private:
	int rang;
	vector<vector<Node*>> matrix;
	vector<vector<Node*>> createMatrix(vector<int>);
};

