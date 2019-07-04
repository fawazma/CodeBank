#ifndef GENSTACK_H
#define GENSTACK_H

template<class Type>
class GenStack {
private:
    int maxSize; // total # of elements stack can hold
    int topIndex; // recently added element index
    Type* stackArray; // pointer to dynamically allocated array for buffer
    void extendStack(); // this method will double the size of the STACK

public:

    GenStack(); // default constructor , default the size = 10
    GenStack(int stackSize); //parameterized constructor
    GenStack(const GenStack<Type>& other); //copy constructor
    const GenStack<Type>& operator=(const GenStack<Type>&other); //assignment operator
    ~GenStack(); //destructor
    void push(const Type& data); //add item in the stack
    Type& pop(); //pop an item and return top element
    int size(); //return the size of the stack
    bool isEmpty(); //check if stack is empty
    bool isFull(); //check if stack is full
    void dump(); // this method will prin the contents of STACK
};

#endif
