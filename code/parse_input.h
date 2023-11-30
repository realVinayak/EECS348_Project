#include <iostream>
#include <stack>
#include <vector>
#ifndef EECS348_PROJECT_PARSE_INPUT_H
#define EECS348_PROJECT_PARSE_INPUT_H

bool isValidExpression(const std::string& expression);
std::string convertPowerOperator(const std::string& expression);
void tokenize(const std::string &raw_expression, std::vector<std::string>&vector_to_use);
#endif //EECS348_PROJECT_PARSE_INPUT_H
