// Lab 3 Calculator
// Ava Gerami
// Lily Tang

#include "CALCULATOR.h"
#include <string>
#include <iostream>

using namespace std;

int main(){
	Calculator<string> calc;
	string s = "";

	cout << "Enter expression separating numbers and operators by spaces: " << endl;
	getline(cin, s);
	cout << "Postfix expression: " << calc.infixToPostfix(s)<<endl;
	cout << "Prefix expression: " << calc.infixToPrefix(s) << endl;
	cout << "Postfix evaluation: " << calc.evalPostfix(calc.infixToPostfix(s)) << endl;
	cout << "Prefix evaluation: " << calc.evalPrefix(calc.infixToPrefix(s)) << endl;
	system("pause");
	return 0;
}