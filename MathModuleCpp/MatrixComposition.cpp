#include "MatrixComposition.h"
#include "Metaoperations.h"
#include "Multioperation.h"
#include "TypesNode.h"
#include "ParametersBF.h"
#include "ParametersMO.h"
#include "NodeOperations.h"
#include "Console.h"
#include "ConstantVectors.h"
#include <iostream>

using namespace std;

int rang = 3;
ParametersBF* _PBF;
ParametersMO* _PMO;
Metaoperations _meta;

void MatrixComposition::getMatrixComposition(Node* formula, ParametersMO* PMO, ParametersBF* PBF)
{
	_PBF = PBF;
	_PMO = PMO;
	vector<Multioperation*> metaoperations = _meta.getMetaoperations();
	vector<Node*> variables = formula->variables;

	for (Node* variable : variables) {
		if (variable->type == 0 || variable->type == 1 || variable->type == 2)
			getMatrixComposition(variable, PMO, PBF);
	}
	vector<Node*> spaceMatrix = calculateMatrix(metaoperations[formula->type], formula);
	formula->spaceMatrix = spaceMatrix;
	//std::system("cls");
}

vector<Node*> MatrixComposition::calculateMatrix(Multioperation* metaoperation, Node* formula)
{
	vector<Node*> variables = formula->variables;
	vector<vector<Node*>> tempMatrix;
	for (auto iter{variables.rbegin()}; iter != variables.rend(); iter++) {
		if (tempMatrix.empty())
			tempMatrix = stepMatrixComposition(metaoperation->getMatrix(), *iter);
		else
			tempMatrix = stepMatrixComposition(tempMatrix, *iter);
		//cout << "\n";
	}
	vector<Node*> spaceMatrix;
	for (int i = 0; i < rang; i++)
		spaceMatrix.push_back(tempMatrix[i][0]);
	return spaceMatrix;
}

vector<vector<Node*>> MatrixComposition::stepMatrixComposition(vector<vector<Node*>> matrix, Node* variable)
{
	int lenght = matrix[0].size() / rang;
	vector<vector<Node*>> newMatrix;
	for (int i = 0; i < rang; i++) {
		vector<Node*> newMatrixRow;
		for (int j = 0; j < matrix[i].size(); j += rang) {
			Node* element = calculateElement(j, matrix[i], variable);
			//cout << Console::ConsoleNode(element, _PBF->getListParameters()) << "\n";
			int index = j == 0 ? j : j / rang;
			newMatrixRow.push_back(element);
		}
		newMatrix.push_back(newMatrixRow);
	}
	return newMatrix;
}

Node* MatrixComposition::calculateElement(int index, vector<Node*> matrix, Node* variable)
{
	Node* result = nullptr;
	Node* node = nullptr;
	Node* currentVariable = nullptr;
	NodeOperations NO;
	int j = 1; //index переменной в BF
	for (int i = index; i < index + rang; i++) {
		if (variable->type == TypesNode::PARAMETER && variable->parametersVector.size() == 16) {
			string designation = _PMO->getDesignation(variable->parametersVector);
			vector<int> vector = _PBF->getVectorParameters(designation + to_string(j));
			currentVariable = new Node(TypesNode::PARAMETER, vector);
		}
		else {
			currentVariable = variable->spaceMatrix[i % rang];
		}
		node = NO.calculateNode(matrix[i], currentVariable);

		if ((node->type == TypesNode::CONSTANT && node->parametersVector[0] != 0) || node->type != TypesNode::CONSTANT) {
			if (result == nullptr) result = node;
			else result = NO.unionNodes(result, node);
		}
		j++;
	}
	if (result == nullptr) result = new Node(TypesNode::CONSTANT, ConstantVectors::getZeroVector(48));
	return result;
}