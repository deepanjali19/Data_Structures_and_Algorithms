// Lab 4

#include "stack.h"
#include <string>
#include<iostream>

using namespace std;

bool bracketCheck(const std::string& s){

	bool  pairEqual(char first, char last);

	Stack<char> stack;
	
	string ss = (string)s;

	bool flag;

	for (int i = 0; i < s.length(); i++) {

		if (ss[i] == '(' || ss[i] == '[' || ss[i] == '{') 
			stack.push(ss[i]);
		else if (ss[i] == ')' || ss[i] == ']' || ss[i] == '}') {

			if (stack.empty() || !pairEqual(stack.top(),ss[i]))
				return false;
			else{
				flag = true;				
				stack.pop();
			}
		}
	}

	if(!stack.empty())
		flag = false;

	return flag;
}

// function to check if two brackets are opening and closing properly

bool pairEqual(char first, char last) {

	if (first == '(' && last == ')')
		return true;
	else if (first == '[' && last == ']')
		return true;
	else if (first == '{' && last == '}')
		return true;
	else return false;
}
