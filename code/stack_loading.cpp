#include <iostream>
#include <stack>  // easy as pie
#include <string> // store post-fix expressions as strings
#include <array>
using namespace std;

// stack should be able to handle numbers (i.e. 4, 6, -1), operators (specifically pemdas + modulus), and special characters (specifically "pi" and "e")
// this means that it will be an integer stack !!
// though, honestly, i think we should just make pi = 3 and e = 3.

// example in-fix and corresponding post-fix expressions:
// 2 + 9 --> 2 9 +
// 3 * 4 --> 3 4 *
// 9 % 3 --> 9 3 %
// 100 / 4 --> 1 4 /
// 2 ^ ( 3 + 4 ) --> 2 3 4 + ^
// 9 * ( 8 % 2 ) + 6 --> 9 8 2 % * 6 +
// 2 + 4 / 5 * ( 5 - 3 ) ^ 5 ^ 4 --> 2 4 5 / 5 3 - 5 ^ 4 ^ * +
// 1 + 9 - 7 * ( 4 / 2 ) --> 1 9 + 7 4 2 / * -

stack<string> make_postfix_stack_for_strings(string postfix_expr, bool test) // using strings
{
    stack<string> stack;

    int str_length = postfix_expr.length();

    for (int i = 0; i < str_length; i++) // a range-based loop,
    {
        if (postfix_expr[i] == ' ')
            continue;

        if (i >= str_length)
            break;

        if (isdigit(postfix_expr[i])) // sorry vinny, i know you wanted to have nice loops, they get out of hand so fast...
        {
            int tokenlength = 1; // length of the current token. i.e. 1 has a tokenlength of 1, 10 has a tokenlength of 2.
            if (postfix_expr[i + 1] != ' ')
            {
                for (int j = i + 1; j < str_length; j++) // this loop is for finding the length of the current token. the length of the current token is the difference between the start of the token and the next space.
                {
                    if (j >= str_length)
                        break;
                    if (postfix_expr[j] == ' ')
                        break;
                    tokenlength++; // this token has a length of <tokenlength>
                }
                stack.push(postfix_expr.substr(i, i + tokenlength)); // then we push the length of the token
                cout << endl
                     << endl
                     << endl
                     << postfix_expr.substr(i, i + tokenlength) << endl
                     << endl
                     << endl;
                i += tokenlength - 1;
            }
            else
            {
                stack.push(string(1, postfix_expr[i])); // otherwise we simply push the token, as it has a length of 1.
            }
        }
        else
        {
            stack.push(string(1, postfix_expr[i])); // pushing tokens that are operators
        }
        // for testing purposes
        if (test == true)
        {
            cout << stack.top() << " ";
        }
    }
    // for testing purposes.

    if (test == true)
    {
        cout << endl
             << "size = " << stack.size() << endl;
    }
    // comment out the tests if you're not testing.

    return stack;
}

int main()
{
    string postfix1 = "2 9 +";
    string postfix2 = "3 4 *";
    string postfix3 = "9 3 %";
    string postfix4 = "100 5 /";
    string postfix5 = "2 3 4 + ^";
    string postfix6 = "9 8 2 % * 6 +";
    string postfix7 = "2 4 5 / 5 3 - 5 ^ 4 ^ * +";
    string postfix8 = "1 9 + 7 4 2 / * -";

    // i'm not sure how to semantically represent '10' as '10' in a character array, because it would be '1','0', which would be seen as 1, and 0.
    // this is why i used strings. see the note below about converting characters to strings and strings to floats.
    // see note below about string stuff

    stack<string> a = make_postfix_stack_for_strings(postfix1, true);
    stack<string> b = make_postfix_stack_for_strings(postfix2, true);
    stack<string> c = make_postfix_stack_for_strings(postfix3, true);
    stack<string> d = make_postfix_stack_for_strings(postfix4, true);
    stack<string> e = make_postfix_stack_for_strings(postfix5, true);
    stack<string> f = make_postfix_stack_for_strings(postfix6, true);
    stack<string> g = make_postfix_stack_for_strings(postfix7, true);
    stack<string> h = make_postfix_stack_for_strings(postfix8, true);

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOTES
// 1. all numbers stored as characters in the stack, such as '5', can be converted to a float using the following commands (from the string header)
//
//   // std::string strNumber(1, charNumber);
//   // float floatNumber = std::stof(strNumber);
//   // this works by converting the character to a string first, then to a float.
//   // If you already have a string, you can directly convert it to a float using the second function.
//
// 2. No need for floats (as per the actual project description)
//
// 3. after further reviewing, it still doesn't really work with tokens that are longer than 1 character long.
//    i guess we should just restrict the user to only use digits (0-9)
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
