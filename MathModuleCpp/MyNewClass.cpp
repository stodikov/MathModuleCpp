#include "MyNewClass.h"

MyNewClass::MyNewClass(int a, int b, int* mas)
{
	this->a = a;
	this->b = b;
	this->mas = mas;
}
int MyNewClass::sum() {
	return this->a + this->b;
}

int MyNewClass::getIndex(int index) {
	return this->mas[index];
}