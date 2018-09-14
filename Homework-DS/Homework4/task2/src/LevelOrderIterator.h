//
// Created by yiner on 28/11/2017.
//

#ifndef DS_EX4_3_LEVELORDERITERATOR_H
#define DS_EX4_3_LEVELORDERITERATOR_H

#include <iostream>
#include "BinTree.h"
#include "Queue.h"

using namespace std;

template<class Type>
class LevelOrderIterator {
private:
    const BinTree <Type> &tree; //Binary tree
    const BinTreeNode <Type> *current; //current pointer
    Queue<const BinTreeNode <Type> *> qu;
public:
    //constructor
    LevelOrderIterator(const BinTree <Type> &tree, const BinTreeNode <Type> *current) : tree(tree), current(current) {
        qu.EnQueue(tree.GetRoot());
    }

    //!!key step
    void increase();

    void Destroy(BinTreeNode<Type> *q);
};

template<class Type>
void LevelOrderIterator<Type>::increase() {
    //判断队列是否为空
    if (qu.IsEmpty()) {
        if (current == nullptr) {
            cout << "End of traversal!" << endl;
            exit(1);
        }
        current = nullptr;
        return;
    }
    //DeQueue
    current = qu.DeQueue();
    //print out the data of current
    //cout<<current->GetData()<<endl;
    //Left child EnQueue
    if (current->GetLeftChild())
        qu.EnQueue(current->GetLeftChild());
    //Right child EnQueue
    if (current->GetRightChild())
        qu.EnQueue(current->GetRightChild());

}

//Destroy tree
template<class Type>
void LevelOrderIterator<Type>::Destroy(BinTreeNode<Type> *q) {
    qu.MakeEmpty();
    qu.EnQueue(q);
    while (!qu.IsEmpty() && current) {
        increase();
        const BinTreeNode<Type> *p = this->current;
        delete p;
    }

}


#endif //DS_EX4_3_LEVELORDERITERATOR_H
