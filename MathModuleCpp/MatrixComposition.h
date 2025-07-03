#include "Node.h"
#include "Multioperation.h"
#include "ParametersMO.h"
#include "ParametersBF.h"
#include <vector>

using namespace std;

#pragma once
class MatrixComposition
{
public:
	static void getMatrixComposition(Node*, ParametersMO*, ParametersBF*);
private:
	static vector<Node*> calculateMatrix(Multioperation*, Node*);
	static vector<vector<Node*>> stepMatrixComposition(vector<vector<Node*>>, Node*);
	static Node* calculateElement(int, vector<Node*>, Node*);
};

