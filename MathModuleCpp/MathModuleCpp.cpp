#include <iostream>
#include "ParametersMO.h"
#include "ParametersBF.h"
#include "InitialValues.h"
#include "Node.h"
#include "MatrixComposition.h"
#include "NodeNegative.h"
#include "NodeOperations.h"
#include "NodeMinimization.h"
#include "TypesNode.h"
#include "Console.h"
#include "Analytical.h"
#include <map>

Node* createElementSystem(Node* left, Node* right)
{
    Node* negRight = NodeNegative::calculateNode(right);
    return NodeOperations::calculateNode(left, negRight);
}

Node* createInequality(vector<Node*> system, ParametersBF* PBF)
{
    vector<Node*> inequalitySystem;
    vector<Node*> unknowns = PBF->getNodesUnknowns();
    vector<Node*> newVariables;
    int unknownsCount = 0;
    for (int i = 0; i < system.size(); i++) {
        for (int j = 0; j < system[i]->spaceMatrix.size(); j++) {
            Node* elementSystem = createElementSystem(system[i]->spaceMatrix[j], unknowns[unknownsCount]);
            inequalitySystem.push_back(elementSystem);
            unknownsCount++;
        }
    }
    for (Node* inequality : inequalitySystem) {
        if (inequality->type == TypesNode::DISJUNCTION) {
            vector<Node*> variables = inequality->variables;
            for (Node* variable : variables) newVariables.push_back(variable);
        }
        else {
            newVariables.push_back(inequality);
        }
    }
    return new Node(TypesNode::DISJUNCTION, newVariables);
}

int main()
{
    std::cout << "Hello World!\n";
    InitialValues IA;
    vector<string> coefficients = IA.getCoefficientsMO();
    vector<string> unknowns = IA.getUnknownsMO();
    ParametersMO* PMO = new ParametersMO(coefficients, unknowns);
    ParametersBF* PBF = new ParametersBF(coefficients, unknowns);
    vector<Node*> system = IA.getSystemInclusions(PMO);
    for (Node* formula : system) {
        MatrixComposition::getMatrixComposition(formula, PMO, PBF);
        /*for (Node* subFormula : formula->spaceMatrix) {
            cout << Console::ConsoleNode(subFormula, PBF->getListParameters()) << "\n" << "\n";
        }*/
    }
    Node* inequality = createInequality(system, PBF);
    //cout << Console::ConsoleNode(inequality, PBF->getListParameters()) << "\n" << "\n";
    map<int, Node*> result = Analytical::getSolution(inequality, PBF);
    for (const auto& pair : result) {
        cout << Console::ConsoleNode(pair.second, PBF->getListParameters()) << "\n" << "\n";
    }
    return 1;
}
