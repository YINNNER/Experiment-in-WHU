//
// Created by yiner on 26/11/2017.
//

#ifndef DS_EX4_BINTREE_H
#define DS_EX4_BINTREE_H

#include <iostream>
#include "Stack.h"
using namespace std;

template <class Type>class BinTreeNode;
template <class Type>class LevelOrderIterator;

template <class Type>
class BinTree{
    friend class LevelOrderIterator<Type>;
private:
    BinTreeNode<Type> *root;
public:
    //constructor
    BinTree():root(nullptr){}
    BinTree(BinTreeNode<Type> *root):root(root){}
    //getter
    BinTreeNode<Type> *GetRoot() const { return root; }
    //setter
    void SetRoot(BinTreeNode<Type> *root) { BinTree::root = root; }

    //Compute the height/depth of BT, starts from 1
    int Depth(const BinTreeNode<Type> *t) const {
        if(t== nullptr) return 0;
        else return 1+max(Depth(t->GetLeft()),Depth(t->GetRight()));
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


};

template <class Type>
class BinTreeNode{
    friend class BinTree<Type>;
    friend class LevelOrderIterator<Type>;
private:
    BinTreeNode *leftChild, *rightChild;
    Type data;
    //!!level
    int level;
public:
    //set default level=1
    BinTreeNode():leftChild(nullptr), rightChild(nullptr),level(1){}
    BinTreeNode(Type data,BinTreeNode *leftChild= nullptr, BinTreeNode *rightChild= nullptr)
            :leftChild(leftChild), rightChild(rightChild), data(data),level(1) {}
    //setter
    void SetLeft(BinTreeNode<Type> *L){
        leftChild=L;
        //!!set child's level
        leftChild->SetLevel(this->GetLevel()+1);
    }
    void SetRight(BinTreeNode<Type> *R){
        rightChild=R;
        //!!set child's level
        rightChild->SetLevel(this->GetLevel()+1);
    }

    void SetData(const Type& item){ data=item;}

    //!!set level
    void SetLevel(int level) { this->level=level; }

    //getter
    BinTreeNode<Type> *GetLeft ( ) const { return leftChild; }
    BinTreeNode<Type> *GetRight ( ) const { return rightChild; }
    Type GetData() const { return data; }
    int GetLevel() const { return level; }

};

#endif //DS_EX4_BINTREE_H
