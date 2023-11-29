#include <iostream>
#include <stack>  // easy as pie
#include <string> // store post-fix expressions as strings
#include <array>
#include <bits/stdc++.h> //For pow

using namespace std;

bool is_operator(string item) {
	//Checks to see if item is in operators array
	
	string operators[] = {"^", "*", "/", "+", "-", "%"};
	int operators_size = sizeof(operators)/sizeof(operators[0]);

	for (int i = 0; i < operators_size; i++) {
		if (operators[i] == item) {
			return true;
		}
	}
	return false;
}

int do_operation(string the_operator, int num1, int num2) {
	//Does simple arithmetic operation on two numbers, given the operator. If the operator is not listed, this function returns 0.
	if (the_operator == "*")
		return (num2 * num1);
	if (the_operator == "/")
		return (num2 / num1);
	if (the_operator == "+")
		return (num2 + num1);
	if (the_operator == "-")
		return (num2 - num1);
	if (the_operator == "%")
		return (num2 % num1);
	if (the_operator == "^")
		return (pow(num2, num1));
	cout << "Operator missing from function" << endl;	
	return 0;
}

int evaluate_stack(stack<string> postfix_stack) {

	stack<string> reversed_stack;
	//We have to reverse the stack because I think it might be backwards coming from stack_loading
	do {
		reversed_stack.push(postfix_stack.top());
		postfix_stack.pop();
	} while (postfix_stack.size() > 0);

	//When we pop numbers off the stack to work on, we put them in here.
	int num1;
	int num2;

	//Value stack and "current" variables to make things hopefully more readable
	stack<string> value_stack;
	string current_item;
	string current_operator;
	int result;

	while (reversed_stack.size() > 0) {
		
		current_item = reversed_stack.top(); //Reading from our reversed "input" stack, just like we're reading in tokens from a string

		if (!is_operator(current_item)) { 
			value_stack.push(current_item); //Then it's a number
		} else { 
			//Then it's an operator
			//Just to make things more readable, if we're in this else clause then it is implied that the current item is an operator.
			current_operator = current_item;

			//Pop top two numbers
			num1 = stoi(value_stack.top());
			value_stack.pop();

			num2 = stoi(value_stack.top());
			value_stack.pop();

			//We do the operation with the two numbers and the operator and get the result
			result = do_operation(current_operator, num1, num2);

			//Push the simplified result to the value stack for next operation
			value_stack.push(to_string(result));

		}
		//We read one token at a time, we've read this token so we get rid of it.
		reversed_stack.pop();

	}

	//If the reverse stack size is zero, then there are no operators left and we must be left with the answer in the value stack assuming the expression is valid
	return stoi(value_stack.top());
}

int main() {

	stack<string> new_stack;

//Some like this get the wrong output because we're using ints and not floats (I think we were told this is fine though?)
//	new_stack.push("2");
//	new_stack.push("4");
//	new_stack.push("5");
//	new_stack.push("/");
//	new_stack.push("5");
//	new_stack.push("3");
//	new_stack.push("-");
//	new_stack.push("5");
//	new_stack.push("^");
//	new_stack.push("4");
//	new_stack.push("^");
//	new_stack.push("*");
//	new_stack.push("+");

//	new_stack.push("2");
//	new_stack.push("3");
//	new_stack.push("4");
//	new_stack.push("*");
//	new_stack.push("+");

	new_stack.push("3");
	new_stack.push("4");
	new_stack.push("*");
	new_stack.push("2");
	new_stack.push("5");
	new_stack.push("*");
	new_stack.push("-");


	cout << evaluate_stack(new_stack) << endl;

	return 0;
}