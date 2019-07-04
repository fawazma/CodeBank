#ifndef SYNTAXCHECKER_H
#define SYNTAXCHECKER_H


#include <string>


class SyntaxChecker {
private :
    bool arePair(char opening,char closing) ;
    char closing(char opening) ;
public :
    bool areParanthesesBalanced(std::string &filename,std::string &errorMessage) ;

} ;


#endif
