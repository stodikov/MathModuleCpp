#include "InitialValues.h"
#include "Node.h"
#include "ParametersMO.h"
#include "TypesNode.h"
#include <cstdlib>
#include <iostream>

using namespace std;

vector<string> InitialValues::getCoefficientsMO() {
    vector<string> coefficients{ "s_1", "s_2", "s_3", "s_4", "s_5" };
    return coefficients;
}

vector<string> InitialValues::getUnknownsMO() {
    vector<string> unknowns{ "d_1", "d_2", "d_3" };
    return unknowns;
}

vector<Node*> InitialValues::getSystemInclusions(ParametersMO* PMO) {
    vector<Node*> formulas{
        new Node(TypesNode::CONJUNCTION, vector<Node*>{
            new Node(TypesNode::PARAMETER, PMO->getVectorParameters("s_1")),
            new Node(TypesNode::DISJUNCTION, vector<Node*>{
                new Node(TypesNode::PARAMETER, PMO->getVectorParameters("s_5")),
                new Node(TypesNode::PARAMETER, PMO->getVectorParameters("s_2"))
            })
        }),
        new Node(TypesNode::CONJUNCTION, vector<Node*>{
            new Node(TypesNode::PARAMETER, PMO->getVectorParameters("s_3")),
            new Node(TypesNode::CONJUNCTION, vector<Node*>{
                new Node(TypesNode::PARAMETER, PMO->getVectorParameters("s_4")),
                new Node(TypesNode::NEGATIVE, vector<Node*>{
                    new Node(TypesNode::PARAMETER, PMO->getVectorParameters("s_5"))
                }),
            })
        }),
        new Node(TypesNode::CONJUNCTION, vector<Node*>{
            new Node(TypesNode::DISJUNCTION, vector<Node*>{
                new Node(TypesNode::PARAMETER, PMO->getVectorParameters("s_1")),
                new Node(TypesNode::PARAMETER, PMO->getVectorParameters("s_4")),
            }),
            new Node(TypesNode::DISJUNCTION, vector<Node*>{
                new Node(TypesNode::PARAMETER, PMO->getVectorParameters("s_3")),
                new Node(TypesNode::PARAMETER, PMO->getVectorParameters("s_5")),
            })
        }),
    };
	return formulas;
}