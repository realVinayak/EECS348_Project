#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <vector>
#include <utility>

void infixToPostfix(std::vector<std::string> &infix_array, std::vector<std::string> &postfix) {
    std::stack<std::string> stack;  // stack to hold operators and parentheses

    // lambda to check if it is valid number or not by checking first digit.
    auto isValidNumber = [](std::string token)->bool{
        return isdigit(token[0]) || token[0] == '.';
    };

    // lambda to check if a character is an operator
    auto isOperator = [](std::string c) -> bool {
        return c == "+" || c == "-" || c == "*" || c == "/" || c == "^" || c == "%" || c == "u" || c == "p";
    };

    // lambda to determine the precedence of operators
    auto precedence = [](std::string c) -> int {
        if (c == "+" || c == "-") return 1;
        if (c == "*" || c == "/" || c == "%") return 2;
        if (c == "^") return 3;
        if (c == "u" || c == "p") return 4;
        return 0;
    };

    // lambda to determine the associativity of operators
    auto associativity = [](std::string op)->bool{
        if (op == "+" || op == "-" || op =="*" || op == "/" || op == "%") return true;
        return false;
    };

    // handles a given token
    auto handleToken = [isValidNumber, isOperator, precedence, &postfix, associativity, &stack](std::string token) -> int {
        // if it is a valid number, push back on stack
        if (isValidNumber(token)){
            postfix.push_back(token);
            return 0;
        }
        // if an operator, further processing is needed
        if (isOperator(token)){
            std::string current_op = token;
            while (!stack.empty() && token != "(" && (
                    precedence(stack.top()) > precedence(token) ||
                    (precedence(stack.top()) == precedence(token)
                    && (associativity(token))
                    ))) {
                postfix.push_back(stack.top());
                stack.pop();
            }
            stack.push(token);
            return 0;
        }
        if (token == "(")
        {
            // push opening parenthesis
            stack.push(token);
            return 0;
        }
        if (token == ")"){
            // pop till matching ( is not found
            while (!stack.empty() && stack.top() != "(") {
                postfix.push_back(stack.top());
                stack.pop();
            }
            // assert that stack is not empty
            if (stack.empty()) return 1;
            stack.pop();
            return 0;
        }
        return 1;

    };

    std::string prevToken = "\0";
    for (size_t i = 0; i < infix_array.size(); ++i) {
        std::string token = infix_array.at(i);
        int response;
        // check if it is unary -
        if (token == "-" && (prevToken == "\0" || prevToken == "(" || isOperator(prevToken))){
            response = handleToken("u");
        // check if it is unary +
        } else if (token == "+" && (prevToken == "\0" || prevToken == "(" || isOperator(prevToken))){
            response = handleToken("p");
        }
        else {
            response = handleToken(token);
        }
        if (response != 0){
            // if any handling token failed, return error
            std::cerr << "Error: Input is invalid\n";
            exit(1);
        }
        prevToken = token;
    }

    // pop any remaining operators from the stack
    while (!stack.empty()) {
        if (stack.top() == "(")
        {
            // assert that ( is not found in stack anymore
            std::cerr << "Error: Input is invalid\n";
            exit(1);
        }
        postfix.push_back(stack.top());
        stack.pop();
    }
}