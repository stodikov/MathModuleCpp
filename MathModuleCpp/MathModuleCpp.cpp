#include <iostream>
#include "ParametersMO.h"
#include "ParametersBF.h"
#include "InitialValues.h"
#include "Node.h"
#include "MatrixComposition.h"
#include "Console.h"

int main()
{
    std::cout << "Hello World!\n";
    InitialValues IA;
    vector<string> coefficients = IA.getCoefficientsMO();
    vector<string> unknowns = IA.getUnknownsMO();
    ParametersMO* PMO = new ParametersMO(coefficients, unknowns);
    ParametersBF* PBF = new ParametersBF(coefficients, unknowns);
    vector<int> indexesUnknowns = PBF->getIndexesUnknowns();
    vector<string> parameters = PBF->getListParameters();
    vector<Node*> system = IA.getSystemInclusions(PMO);
    for (Node* formula : system) {
        MatrixComposition::getMatrixComposition(formula, PMO, PBF);
        for (Node* subFormula : formula->spaceMatrix) {
            cout << Console::ConsoleNode(subFormula, PBF->getListParameters()) << "\n" << "\n";
        }
    }
    return 1;
}
