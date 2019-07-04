#include "SyntaxChecker.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("Please supply the file name as argument \n");
        exit(0);
    } else if (argc > 2) {
        printf("Too many arguments , only one argument is required  \n");
        exit(0);
    }

    string file = argv[1] , error;
    bool status  ;
//    cout<<"Enter the file name:" ;
//    cin>>file ;

    ifstream ifs;
    ifs.open(file.c_str(), ios_base::in);
    if (ifs.is_open())
    {

     SyntaxChecker sc ;
    status = sc.areParanthesesBalanced(file ,error) ;
     if (status)
           cout<<"The delimiter syntax is correct."<<endl ;
     else
         cout<<error<<endl ;
    }
    else
    {
        cout<<"Unable to open the file to read"<<endl ;
    }

    return 0;
}
