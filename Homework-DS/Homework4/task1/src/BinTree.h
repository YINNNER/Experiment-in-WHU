//
// Created by yiner on 26/11/2017.
//

#ifndef DS_EX4_BINTREE_H
#define DS_EX4_BINTREE_H

#include <iostream>
#include "Stack.h"
using namespace std;

template <class Type>class BinTreeNode;

template <class Type>
class BinTree{
    BinTreeNode<Type> *root;
public:
    //constructor
    BinTree():root(nullptr){}
    BinTree(BinTreeNode<Type> *root):root(root){}
    void InOrderTraverse(){InOrderTraverse(root);}
    void InOrderTraverse(BinTreeNode<Type> *t) {
        //!!注意：stack里面的元素类型是BinTreeNode<Type>*
        Stack<BinTreeNode<Type>*> stack;
        BinTreeNode<Type> *p=t;
        do{
            //访问左子树
            while (p){
                //入栈
                stack.Push(p);
                //访问左孩子
                p=p->leftChild;
            }
            if(!stack.IsEmpty()){
                //得到栈顶元素并出栈
                p=stack.GetTop();
                stack.Pop();
                //访问自己/栈顶元素
                cout<<p->data<<" ";
                //访问右子树
                p=p->rightChild;
            }

        }while (p||!stack.IsEmpty());
    }

};

template <class Type>
class BinTreeNode{
    friend class BinTree<Type>;
private:
    BinTreeNode *leftChild, *rightChild;
    Type data;
public:
    BinTreeNode():leftChild(nullptr), rightChild(nullptr){}
    BinTreeNode(Type data,BinTreeNode *leftChild= nullptr, BinTreeNode *rightChild= nullptr)
            :leftChild(leftChild), rightChild(rightChild), data(data) {}
    //setter
    void setLeft(BinTreeNode<Type> *L){ leftChild=L;}
    void setRight(BinTreeNode<Type> *R){ rightChild=R;}
    void setData(const Type& item){ data=item;}


};

#endif //DS_EX4_BINTREE_H
