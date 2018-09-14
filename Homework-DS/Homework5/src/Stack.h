//
// Created by yiner on 11/11/2017.
//

#ifndef DS_EX3_STACK_H
#define DS_EX3_STACK_H

#include <cassert>
#include "BTNode.h"

//Sequential Stack
template<class Type>
class Stack {
public:
    Stack(int= 15);

    Stack(Stack<Type> const &stack); //Copy Constructor----deep copy!
    ~Stack() { delete[]elements; }

    void push(Type & item);

    Type pop();

    Type getTop();

    void clear() { top = -1; }

    int isEmpty() const { return top == -1; }

    int isFull() const { return top == maxSize - 1; }

    //top from 0, but size frome 1
    int getSize() const { return top + 1; }

private:
    int top;
    Type *elements;
    int maxSize;
};

template<class Type>
Stack<Type>::Stack(int size):top(-1), maxSize(size) {
    elements = new Type[maxSize];
    //assert的作用是计算表达式 expression ，如果其值为假（即为0）,
    //那么它先向stderr打印一条出错信息，然后通过调用 abort 来终止程序运行.
    assert(elements != 0);
}


template<class Type>
void Stack<Type>::push(Type &item) {
    assert(!isFull());
    //top先++再赋值
    elements[++top] = item;
}

//获得栈顶元素，并出栈
template<class Type>
Type Stack<Type>::pop() {
    assert(!isEmpty());
    //top先输出再--
    return elements[top--];
}

//获得栈顶元素，但不出栈
template<class Type>
Type Stack<Type>::getTop() {
    assert(!isEmpty());
    return elements[top];
}

//Copy Constructor----deep copy!
template<class Type>
Stack<Type>::Stack(Stack<Type> const &stack) {
    this->maxSize = stack.maxSize;
    this->top = stack.top;
    this->elements = new Type[maxSize];
    assert(this->elements != 0);
    for (int i = 0; i < top; ++i) {
        this->elements[i] = stack.elements[i];
    }
}


#endif //DS_EX3_STACK_H
