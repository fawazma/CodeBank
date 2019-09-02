#include "Person.h"

using namespace std;

Person::Person() {
};

Person::~Person() {
};

int Person::getID() {
    return id;
}

void Person::setID(int v) {
    id = v;
}

std::string Person::getName() {
    return name;
}

std::string Person::getLevel() {
    return level;
}
