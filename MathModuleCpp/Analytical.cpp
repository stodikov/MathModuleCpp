#include "Analytical.h"
#include "NodeResiadual.h"
#include "NodeOperations.h"
#include "NodeNegative.h"
#include "NodeSubstitution.h"
#include "TypesNode.h"
#include "ParametersBF.h"
#include <iostream>

using namespace std;

ParametersBF* A_PBF;

map<int, Node*> Analytical::getSolution(Node* inequality, ParametersBF* PBF)
{
	A_PBF = PBF;
	Node* node = solvability(inequality);
	if (node->type == TypesNode::CONSTANT && node->parametersVector[0] == 1) {
		cout << "Решения нет" << "\n";
	}
	return Analytical::generalSolution(inequality);
}

Node* Analytical::solvability(Node* inequality)
{
	return NodeResiadual::calculateGeneralResidual(inequality, A_PBF->getIndexesUnknowns());
}

map<int, Node*> Analytical::generalSolution(Node* inequality)
{
	vector<int> indexes = A_PBF->getIndexesUnknowns();
	vector<Node*> arbitraries = A_PBF->getNodesArbitraries();
	Node* currentInequality = inequality;
	map<int, Node*> result;

	while (indexes.size() > 0) {
		int currentIndex = indexes[indexes.size() - 1];
		Node* arbitrary = arbitraries[arbitraries.size() - 1];
		indexes.pop_back();
		arbitraries.pop_back();

		Node* residualNode = indexes.size() != 0 ?
			NodeResiadual::calculateGeneralResidual(currentInequality, indexes) :
			currentInequality;
		Node* nodeWithZero = NodeResiadual::calculateResidual(residualNode, vector<int>{currentIndex}, vector<int>{0});
		Node* newNodeWithZero = NodeOperations::calculateNode(arbitrary, nodeWithZero);

		Node* nodeWithOne = NodeResiadual::calculateResidual(residualNode, vector<int>{currentIndex}, vector<int>{1});
		Node* negNodeWithOne = NodeNegative::calculateNode(nodeWithOne);
		Node* negArbitrary = NodeNegative::calculateNode(arbitrary);
		Node* newNodeWithOne = NodeOperations::calculateNode(negArbitrary, negNodeWithOne);

		result[currentIndex] = NodeOperations::unionNodes(newNodeWithZero, newNodeWithOne);
		currentInequality = NodeSubstitution::calculateNode(currentInequality, result[currentIndex], currentIndex);
	}
	return result;
}