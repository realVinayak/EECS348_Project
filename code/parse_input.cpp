#include <iostream>
#include <stack>
#include <vector>

bool isOperator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%';
};

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


bool isComputable(char c){
    return c == '.' || isdigit(c) || c == '(';
}

void validate_parsed_vector(std::vector<std::string>&vector){
    // set bits on what to look for. NUMBER OPERATOR
    // don't need to set an extra bit for parenthesis since it is always semantically
    // same as a number
    bool searching_for[2] = {true, true};
    int idx = 0;
    while (idx < vector.size() - 1){
        char current = vector[idx][0];
        if (isOperator(current)){
            if (isComputable(vector[idx+1][0]) == true){
                idx += 2;
                continue;
            }
            if ((vector[idx+1][0] == '+' || vector[idx+1][0] == '-') && isComputable(vector[idx+2][0]) == true){
                idx += 2;
                continue;
            }
            std :: cerr << "Error: Input is invalid\n";
            exit(1);
        }
        else if (current == '(') {
            if(isComputable(vector[idx + 1][0]) ||
                vector[idx+1][0] == '+' ||
                vector[idx+1][0] == '-'
                ){
                idx += 1;
                continue;
            }
            std::cerr << "Error: Input is invalid\n";
            exit(1);
        }
        else if (isComputable(current)) {
            //  std :: cout << idx << std :: endl;
            if (!isOperator(vector[idx + 1][0]) && !(vector[idx+1][0] == ')')) {
                std::cerr << "Error: Input is invalid\n";
                exit(1);
            }else{
                idx += 2;
                continue;
            }
        }
            idx++;
        }
    }

void tokenize(const std::string &raw_expression, std::vector<std::string>&vector_to_use){

    //std::cout << "Original Expression: " << raw_expression << std::endl;       //This prints the originial user expression

    if (!isValidExpression(raw_expression)) {      //This line checks if the expression has valid parentheses
    std::cerr << "Error: Mismatched parentheses in the expression.\n";      //This line displays the error message if it does not have matching parentheses
    exit(1);       //Returns non-zero value to show that there was an error in the expression
    }
    for (int i = 0; i < raw_expression.size(); ++i){
        if (raw_expression[i] == '*' && i < raw_expression.size() - 1 && raw_expression[i + 1] == '*') {        //This line checks if two corresponding characters are both **
            vector_to_use.push_back("^");      //If so it makes the result ^
            ++i;        //It also skips the second * when correcting so that it doesn't make ^^
            continue;
        }
        // Handle pi
        if (raw_expression[i] == 'p' && i < raw_expression.size() - 1 && raw_expression[i + 1] == 'i'){
            vector_to_use.push_back("3.14");
            ++i;
            continue;
        }
        // Handle i
        if (raw_expression[i] == 'e'){
            vector_to_use.push_back("3.14");
            continue;
        }
        if (raw_expression[i] == '\t' || raw_expression[i] == '\n' || raw_expression[i] == ' ') continue;
        if (raw_expression[i] == '\0'){
            std::cout << "Received EOF. Terminating";
            exit(0);
        }

        if (raw_expression[i] == '(' || raw_expression[i] == ')' || isOperator(raw_expression[i]) == true){
            std::string temp_str = "";
            temp_str += raw_expression[i];
            vector_to_use.push_back(temp_str);
            continue;
        }
        // Will attempt to add a number here
        std::string number_to_add = "";
        bool period_added = false;
        while (isdigit(raw_expression[i])
        || (raw_expression[i] == '.' && !period_added)){
            number_to_add += raw_expression[i];
            period_added = period_added || raw_expression[i] == '.';
            ++i;
        }
        i--;
        if (number_to_add == ""){
            std::cerr << "Error: Input is invalid\n";
            exit(1);
        }
        vector_to_use.push_back(number_to_add);
    }
    validate_parsed_vector(vector_to_use);
}

