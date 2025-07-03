#pragma once
#define MY_NEW_CLASS_H

class MyNewClass
{
public:
	MyNewClass(int, int, int*);
	int sum();
	int getIndex(int);
private:
	int a;
	int b;
	int* mas;
};

