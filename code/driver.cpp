#include "parse_input.h"
#include "iostream"
#include "infix_to_postfix.h"
#include "evaluate_stack.h"
#include <stack>
#include <vector>

int main(){
    std :: string inputExpression;
    std::cout << "Enter an arithmetic expression: ";        //This prompts the user to enter the expression
    std::getline(std::cin, inputExpression);
    std::vector<std::string> input_vector;
    tokenize(inputExpression, input_vector);
    std::vector<std::string> postfix_vector; // Using a vector to allow easier debugging
    infixToPostfix(input_vector, postfix_vector);
    std::stack<std::string> postfix_stack;
    for (int i = 0; i < postfix_vector.size(); ++i){
        //std :: cout << "At " << i << " " << postfix_vector.at(i) << std::endl;
        postfix_stack.push(postfix_vector.at(i));
    }
    std::cout << "Result: " << evaluate_stack(postfix_stack) << std :: endl;

}