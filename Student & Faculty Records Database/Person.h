#ifndef PERSON_H
#define PERSON_H

#include<string>

class Person {
public:
    int id;
    std::string name;
    std::string level;

    Person();
    ~Person();

    int getID();
    void setID(int v);

    std::string getName();
    std::string getLevel();
};


#endif
