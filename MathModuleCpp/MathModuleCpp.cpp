#include <iostream>
#include "ParametersMO.h"
#include "ParametersBF.h"
#include "InitialValues.h"
#include "Node.h"
#include "MatrixComposition.h"
#include "Console.h"
#include "MinimizationNode.h"

int main()
{
    std::cout << "Hello World!\n";
    InitialValues IA;
    vector<string> parameters = IA.getParametersMO();
    ParametersMO* PMO = new ParametersMO(parameters);
    ParametersBF* PBF = new ParametersBF(parameters);
    vector<Node*> system = IA.getSystemInclusions(PMO);
    for (Node* formula : system) {
        MatrixComposition::getMatrixComposition(formula, PMO, PBF);
        for (Node* subFormula : formula->spaceMatrix) {
            cout << Console::ConsoleNode(subFormula, PBF->getListParameters()) << "\n" << "\n";
        }
    }
    return 1;
}
