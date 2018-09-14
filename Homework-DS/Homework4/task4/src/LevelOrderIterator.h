//
// Created by yiner on 28/11/2017.
//

#ifndef DS_EX4_3_LEVELORDERITERATOR_H
#define DS_EX4_3_LEVELORDERITERATOR_H

#include <iostream>
#include "BinTree.h"
#include "Queue.h"
using namespace std;

template <class Type>
class LevelOrderIterator{
private:
    const BinTree <Type> & tree; //Binary tree
    const BinTreeNode <Type> *current; //current pointer
    Queue<const BinTreeNode<Type> *> qu;
public:
    LevelOrderIterator(const BinTree<Type> &tree, const BinTreeNode<Type> *current) : tree(tree), current(current) {
        qu.EnQueue(tree.GetRoot());
    }
    //!!key step
    void First(int level);
    void increase();
    void TraverseByLevel(int level,int height);
    void Destroy(BinTreeNode<Type> *q);

};

//!!key step
template<class Type>
void LevelOrderIterator<Type>::First(int level) {
    qu.MakeEmpty();
    if(current) qu.EnQueue(current);
    while (qu.GetFront()->GetLevel()!=level){
        increase();

    }

}

template<class Type>
void LevelOrderIterator<Type>::increase() {
    //判断队列是否为空
    if (qu.IsEmpty()){
        if (current== nullptr){
            cout<<"End of traversal!"<<endl;
            exit(1);
        }
        current= nullptr;
        return;
    }
    //DeQueue
    current=qu.DeQueue();
    //print out the data of current
    //cout<<current->GetData()<<endl;
    //Left child EnQueue
    if (current->GetLeft())
        qu.EnQueue(current->GetLeft());
    //Right child EnQueue
    if (current->GetRight())
        qu.EnQueue(current->GetRight());

}

template<class Type>
void LevelOrderIterator<Type>::TraverseByLevel(int level,int height) {
    if(level>height){
        cout<<"The level is bigger than the height of the tree!"<<endl;
        exit(1);
    }
    First(level);
    while (!qu.IsEmpty()&&qu.GetFront()->GetLevel()==level){
        increase();
        //print out the data of current
        cout<<current->GetData()<<" ";
    }
    cout<<endl;
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
