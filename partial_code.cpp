#include <iostream>
#include <stack>

bool isValidExpression(const std::string& expression) {     //This line is a function checks for valid parentheses 
    std::stack<char> parentheses;       //This line is the stack that keeps track of the open parentheses 

    for (char ch : expression) {        //This line starts the for loop to iterate through each character in the expression
        if (ch == '(') {        //This line checks if the character is is an open parentheses 
            parentheses.push(ch);       //This line pushes it onto the stack
        } else if (ch == ')') {     //This line checks if the character is a closed parentheses
            if (parentheses.empty()) {      //This line checks if the stack is empty meaning it would be a mismatched parentheses 
                return false;       //It returns false if it is a mismatched parentheses 
            }           
            parentheses.pop();      //This pops the open parentheses from the stack
        }
    }

    return parentheses.empty();     //This line retuns if the the stack is empty meaning that there were no remaining open parentheses 
}

std::string convertPowerOperator(const std::string& expression) {       //This line is the function that converts the operator '**' to '^'
    std::string result;     //This line is the string expression after the conversion
    for (size_t i = 0; i < expression.size(); ++i) {        //This line is the for loop that iterates through each character in the expression
        if (expression[i] == '*' && i < expression.size() - 1 && expression[i + 1] == '*') {        //This line checks if two corresponding characters are both **
            result += '^';      //If so it makes the result ^ 
            ++i;        //It also skips the second * when correcting so that it doesn't make ^^
        } else {        //Else for if it does not match the two **
            result += expression[i];        //If so it keeps the character as it is 
        }
    }
    return result;      //Returns the resulting expression 
}

std::string handleDanglingMinus(const std::string& expression) {        //This line initializes function to check for dangling minus signs and prepend '0' if needed
    std::string result;     //Initialies result string variable for after it is handled 

    for (size_t i = 0; i < expression.size(); ++i) {        //This line contains a for loop to iterate through each character in the expression 
        if (expression[i] == '-' ) {        //This line checks if the current character is a minus 
            if (i == 0 || (i >0 && !isdigit(expression[i - 1])))  {   //This line checks if it is the first character in the line or not preeded by another digit 
                result += '0'; // Prepend '0' before a dangling minus sign
            }
        }
        result += expression[i];        //Appends the current character to the result string 
    }

    return result;      //Return resulting expression after handling 
}   

int main() {        //This line includes the main function for the execution of the code
    std::string inputExpression;        //This initializes the variable to hold the user expression

    std::cout << "Enter an arithmetic expression: ";        //This prompts the user to enter the expression
    std::getline(std::cin, inputExpression);        //This reads the expression from the user 

    if (!isValidExpression(inputExpression)) {      //This line checks if the expression has valid parentheses 
        std::cerr << "Error: Mismatched parentheses in the expression.\n";      //This line displays the error message if it does not have matching parentheses 
        return 1;       //Returns non-zero value to show that there was an error in the expression 
    }

    std::string modifiedExpression = convertPowerOperator(inputExpression);     //This line runs through the function to convert any ** in the expression into ^ 
    std::string finalExpression = handleDanglingMinus(modifiedExpression);      //This line runs through the function to check for any dangling minuses and prepend the 0 

    std::cout << "Original Expression: " << inputExpression << std::endl;       //This prints the originial user expression 
    std::cout << "Modified Expression: " << modifiedExpression << std::endl;        //And this line prints the updated expression 
    std::cout << "Final Expression: " << finalExpression << std::endl;      //This line prints the final expression after running it through all the conversions and checks

    return 0;       //Returns 0 to show successful execution of system 
}