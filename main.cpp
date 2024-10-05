#include <cstring>
#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main() {
	const int maxLSize = 250;
	string line;
	getline(cin, line);
	char* erLine = new char[line.size()];

	stack<char> stack1;
	stack<char> stack2;
	int index = 0;
	while(line[index] != ';') {
		if(line[index] == '{' || line[index] == '[' || line[index] == '(') {
			stack1.push(line[index]);
		}
		if(line[index] == '}' || line[index] == ']' || line[index] == ')') {
			if(stack1.top() == '(') {
				if(stack1.top() + 1 == line[index]) {
					stack1.pop();
				} else {
					cout << "line isn't correct" << endl;
					cout << erLine << endl;
					delete[] erLine;
					return 0;
				}
			} else {
				if(stack1.top() + 2 == line[index]) {
					stack1.pop();
				} else {
					cout << "line isn't correct" << endl;
					cout << erLine << endl;
					delete[] erLine;
					return 0;
				}
			}
		}
		erLine[index] += line[index];
		index++;
	}
	cout << "line is correct" << endl;
	cout << erLine << endl;
	delete[] erLine;

	return 0;
}
