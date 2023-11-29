#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <vector>
#include <utility>

std::string infixToPostfix(const std::string& infix) {
    std::stack<char> stack;  // stack to hold operators and parentheses
    std::string postfix;     // string to store the resulting postfix expression

    // lambda to check if a character is an operator
    auto isOperator = [](char c) -> bool {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%';
    };

    // lambda to determine the precedence of operators
    auto precedence = [](char c) -> int {
        if (c == '+' || c == '-') return 1;
        if (c == '*' || c == '/' || c == '%') return 2;
        if (c == '^') return 3;
        return 0;
    };

    for (size_t i = 0; i < infix.length(); ++i) {
        char c = infix[i];

        // handling numbers (including multi-digit and floating-point)
        if (isdigit(c) || (c == '.' && i + 1 < infix.length() && isdigit(infix[i + 1]))) {
            if (!postfix.empty() && postfix.back() != ' ') {
                postfix += ' '; // Add a space before number
            }
            postfix += c;
            // append following digits or a single decimal point to form a complete number
            while (i + 1 < infix.length() && (isdigit(infix[i + 1]) || infix[i + 1] == '.')) {
                i++;
                postfix += infix[i];
            }
        }
        // handle operators
        else if (isOperator(c)) {
            while (!stack.empty() && precedence(stack.top()) >= precedence(c)) {
                postfix += ' ';
                postfix += stack.top();
                stack.pop();
            }
            stack.push(c);
        }
        // handle parentheses
        else if (c == '(') {
            stack.push(c);
        }
        else if (c == ')') {
            while (!stack.empty() && stack.top() != '(') {
                postfix += ' ';
                postfix += stack.top();
                stack.pop();
            }
            stack.pop(); // pop the '('
        }
    }

    // pop any remaining operators from the stack
    while (!stack.empty()) {
        postfix += ' ';
        postfix += stack.top();
        stack.pop();
    }

    return postfix;
}

// example for using the function
int main() {
    std::string infix;
    std::cout << "Enter infix expression: ";
    std::getline(std::cin, infix);
    std::string postfix = infixToPostfix(infix);
    std::cout << "Postfix expression: " << postfix << std::endl;
    return 0;
}
