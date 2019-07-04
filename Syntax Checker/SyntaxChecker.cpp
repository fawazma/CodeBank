#include "SyntaxChecker.h"
#include "GenStack.cpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>
using namespace std;

bool SyntaxChecker::areParanthesesBalanced(std::string &filename, std::string &errorMessage) {
    ifstream ifs;
    int line = 0;
    GenStack<char> S(10);
    bool status = true;
    stringstream msg;

    ifs.open(filename.c_str(), ios_base::in);
    string exp = "";
    while (getline(ifs, exp)) {
        line++;
        for (int i = 0; i < exp.length(); i++) {
            if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
                S.push(exp[i]);
            else if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']') {
                char recentBrace = S.pop();

                if (!arePair(recentBrace, exp[i])) {

                    status = false;
                    msg << "Line " << line << ": expected " << closing(recentBrace) << " and found " << exp[i];
                    errorMessage = msg.str();

                    break; // stop processing next characters
                }
            }
        }

        if (!status)
            break; // stop processing next lines
    }


    if (status && !S.isEmpty()) {
        status = false;
        errorMessage = "Reached end of file: missing }";
    }

    ifs.close();
    return status;
}

bool SyntaxChecker::arePair(char opening, char closing) {
    if (opening == '(' && closing == ')')
        return true;
    else if (opening == '{' && closing == '}')
        return true;
    else if (opening == '[' && closing == ']')
        return true;
    return false;
}

char SyntaxChecker::closing(char opening) {
    char closing;

    if (opening == '(')
        closing = ')';
    else if (opening == '[')
        closing = ']';
    else if (opening == '{')
        closing = '}';

    return closing;

}
