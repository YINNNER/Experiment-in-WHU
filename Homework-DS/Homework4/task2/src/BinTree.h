//
// Created by yiner on 26/11/2017.
//

#ifndef DS_EX4_BINTREE_H
#define DS_EX4_BINTREE_H

#include <iostream>
#include <cassert>
#include "Stack.h"


using namespace std;

template<class Type>
class BinTreeNode;

template<class Type>
class LevelOrderIterator;

template<class Type>
class BinTree {
    friend class LevelOrderIterator<Type>;
private:
    BinTreeNode<Type> *root;
public:
    //constructor
    BinTree() : root(nullptr) {}
    BinTree(BinTreeNode<Type> *root) : root(root) {}


    BinTreeNode<Type> *GetRoot() const {
        return root;
    }


    //Find the node according to its data
    BinTreeNode<Type> &Find(const Type &item) const {
        //!!注意：stack里面的元素类型是BinTreeNode<Type>*
        Stack<BinTreeNode<Type> *> stack;
        BinTreeNode<Type> *p = root;
        do {
            //访问左子树
            while (p) {
                //入栈
                stack.Push(p);
                //访问左孩子
                p = p->leftChild;
            }
            if (!stack.IsEmpty()) {
                //得到栈顶元素并出栈
                p = stack.GetTop();
                stack.Pop();
                //访问自己/栈顶元素
                if (item == p->data)
                    return *p;
                //访问右子树
                p = p->rightChild;
            }

        } while (p || !stack.IsEmpty());

        exit(1);
    }


    void InOrderTraverse() { InOrderTraverse(root); }
    void InOrderTraverse(BinTreeNode<Type> *t) {
        //!!注意：stack里面的元素类型是BinTreeNode<Type>*
        Stack<BinTreeNode<Type> *> stack;
        BinTreeNode<Type> *p = t;
        do {
            //访问左子树
            while (p) {
                //入栈
                stack.Push(p);
                //访问左孩子
                p = p->leftChild;
            }
            if (!stack.IsEmpty()) {
                //得到栈顶元素并出栈
                p = stack.GetTop();
                stack.Pop();
                //访问自己/栈顶元素
                cout << p->data << " ";
                //访问右子树
                p = p->rightChild;
            }

        } while (p || !stack.IsEmpty());
        cout << endl;
    }

};

template<class Type>
class BinTreeNode {
    friend class BinTree<Type>;

    friend class LevelOrderIterator<Type>;

private:
    BinTreeNode *leftChild, *rightChild;
    Type data;
public:
    BinTreeNode() : leftChild(nullptr), rightChild(nullptr) {}

    BinTreeNode(Type data, BinTreeNode *leftChild = nullptr, BinTreeNode *rightChild = nullptr)
            : leftChild(leftChild), rightChild(rightChild), data(data) {}

    //setter
    void SetLeft(BinTreeNode<Type> *L) { leftChild = L; }

    void SetRight(BinTreeNode<Type> *R) { rightChild = R; }

    void SetData(const Type &item) { data = item; }

    //getter
    BinTreeNode *GetLeftChild() const { return leftChild; }

    BinTreeNode *GetRightChild() const { return rightChild; }

    Type GetData() const { return data; }


};

#endif //DS_EX4_BINTREE_H
