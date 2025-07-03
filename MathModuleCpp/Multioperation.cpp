#include "Multioperation.h"
#include "TypesNode.h"
#include "ConstantVectors.h"
#include <math.h>

Multioperation::Multioperation(int rang, vector<int> multioperation)
{
	this->rang = rang;
	this->matrix = createMatrix(multioperation);
}

vector<vector<Node*>> Multioperation::getMatrix()
{
	return this->matrix;
}

vector<vector<Node*>> Multioperation::createMatrix(vector<int> multioperation)
{
	vector<vector<int>> elements{
		{1, 3, 5, 7},
		{2, 3, 6, 7},
		{4, 5, 6, 7},
	};
	int sizeMO = multioperation.size();
	ConstantVectors CV;
	vector<vector<Node*>> matrix;
	for (int i = 0; i < this->rang; i++) {
		vector<Node*> matrixRow;
		for (int j = 0; j < sizeMO; j++) {
			if (checkElement(elements[i], multioperation[j]))
				matrixRow.push_back(new Node(TypesNode::CONSTANT, CV.getUnitVector(48)));
			else
				matrixRow.push_back(new Node(TypesNode::CONSTANT, CV.getZeroVector(48)));
		}
		matrix.push_back(matrixRow);
	}
	return matrix;
}

bool Multioperation::checkElement(vector<int> elements, int element)
{
	return find(elements.begin(), elements.end(), element) != elements.end();
}