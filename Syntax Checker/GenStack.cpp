#include "GenStack.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <cstring>
using namespace std;

template<class Type>
GenStack<Type>::GenStack() {

    maxSize = 10;
    topIndex = -1;
    stackArray = new Type[maxSize];

}

template<class Type>
GenStack<Type>::GenStack(int stackSize) {

    maxSize = stackSize;
    topIndex = -1;
    stackArray = new Type[maxSize];

}
//copy constructor

template<class Type>
GenStack<Type>::GenStack(const GenStack<Type>& other) {

    maxSize = other.maxSize;
    topIndex = other.topIndex;
    stackArray = new Type[maxSize];

    for (int i = 0; i <= topIndex; i++) {
        stackArray[i] = other.stackArray[i];
    }

}

//overloading operator

template<class Type>
const GenStack<Type>& GenStack<Type>::operator=(const GenStack<Type>&other) {
    if (this != &other) {

        maxSize = (maxSize > other.maxSize ? maxSize : other.maxSize);

        delete [] stackArray; // delete dynamic array
        stackArray = new Type[maxSize];

        for (int i = 0; i <= topIndex; i++) {
            stackArray[i] = other.stackArray[i];
        }



    }
    return *this;
}
//destructor

template<class Type>
GenStack<Type>::~GenStack() {
    delete [] stackArray; // delete dynamic array
}

// this method will double the size of the STACK

template<class Type>
void GenStack<Type>::extendStack() {

    int newSize = maxSize * 2;
    Type* newStackArray = new Type[newSize];
    for (int i = 0; i <= topIndex; i++) {
        newStackArray[i] = stackArray[i];
    }

    delete[] stackArray;
    maxSize = newSize;
    stackArray = newStackArray;

}

template<class Type>
void GenStack<Type>::push(const Type& data) {

    if (isFull())
        extendStack();

    stackArray[++topIndex] = data;
}

template<class Type>
Type& GenStack<Type>::pop() {
    //check if it is not empty
    //remove and return top element
    if (isEmpty()) {
        throw overflow_error("Error : Stack is Empty");

    } else
        return stackArray[topIndex--];
}

template<class Type>
int GenStack<Type>::size() {
    //return the size of the stack
    return maxSize;
}

template<class Type>
bool GenStack<Type>::isEmpty() {
    //return true if topIndex == -1, false otherwise
    if (topIndex == -1) {
        return true;
    } else
        return false;
}

template<class Type>
bool GenStack<Type>::isFull() {
    //return true if topIndex+1 == full stack, false otherwise
    if (topIndex + 1 == maxSize) {
        return true;
    } else
        return false;
}

template<class Type>
void GenStack<Type>::dump() {


    cout << " | " << "maxSize : " << maxSize << " | " << "topIndex: " << topIndex <<endl ;
    // For easy readability , printing '|' to surround elements
    cout << " | ";
    for (int i = 0; i <= topIndex; i++)
        cout << stackArray[i] << " | ";

    cout << "\n---------------------------\n" << endl;


}
