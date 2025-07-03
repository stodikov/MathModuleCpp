#include <vector>
#include <string>
#include "Node.h"

using namespace std;

#pragma once
class Console
{
public:
	static string ConsoleNode(Node*, vector<string>);
	static string ConsoleConstant(Node*);
	static string ConsoleConjunction(Node*, vector<string>);
};

