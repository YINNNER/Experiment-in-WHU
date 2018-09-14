//
// Created by yiner on 26/11/2017.
//

#ifndef DS_EX4_BINTREE_H
#define DS_EX4_BINTREE_H

#include <iostream>
#include <cmath>
#include "Stack.h"
using namespace std;

template <class Type>class BinTreeNode;

template <class Type>
class BinTree{
protected:
    BinTreeNode<Type> *root;
public:
    //constructor
    BinTree():root(nullptr){}
    BinTree(BinTreeNode<Type> *root):root(root){}
    //getter
    BinTreeNode<Type> *GetRoot() const {
        return root;
    }
    //setter
    void SetRoot(BinTreeNode<Type> *root) {
        BinTree::root = root;
    }
    //height starts from 0
    int height(const BinTreeNode<Type> *p) const{
        if (p== nullptr)
            return -1;
        return max(height(p->GetLeftChild()),height(p->GetRightChild()))+1;
    }
    //find the corresponding leaf node to the weight
    BinTreeNode<Type> * find(char c, Type& data) const{ return find(c,data,root);}
    BinTreeNode<Type> * find(char c,Type& data,BinTreeNode<Type> *t) const{
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
                if (p->GetData()==data&&(p->GetC()==c)&&(!p->GetLeftChild()&&!p->GetRightChild()))
                    return p;
                //访问右子树
                p=p->rightChild;
            }

        }while (p||!stack.IsEmpty());

        return nullptr;
    }

    //break tree
    //!!PostOrderTraverse需要考虑二次入栈
    typedef struct StackNode{
        enum{L,R} tag;
        BinTreeNode<Type>* ptr;
    }StackNode;
    void breakTree(BinTreeNode<Type> *t) {
        //!!注意：这里stack的type应该为BinTreeNode<Type> *
        Stack<StackNode> stack;
        stack.MakeEmpty();
        BinTreeNode<Type> *p=t;
        //存入栈的是StackNode,比单纯的p多了一个状态tag来指示此时访问的情况
        StackNode w;
        do{
            //一直访问p的左子树直到最下面
            while (p){
                w.ptr=p;
                //访问左子树状态为L
                w.tag=w.L;
                //入栈
                stack.Push(w);
                //访问左孩子
                p=p->leftChild;
            }
            //用于退出循环，来访问右子树
            int continues=1;
            while (continues&&!stack.IsEmpty()){
                //得到栈顶元素
                w=stack.GetTop();
                p=w.ptr;
                //出栈
                stack.Pop();
                //判断此时状态来决定访问右子树还是自己
                switch (w.tag){
                    //访问右子树，状态为R
                    case w.L:
                        w.tag=w.R;
                        stack.Push(w);
                        //用于退出循环，来访问右子树
                        continues=0;
                        p=p->rightChild;
                        break;
                        //访问自己
                    case w.R:
                        delete p;
                        p= nullptr;
                }
            }


        }while (p||!stack.IsEmpty());//循环条件：p不空或stack不空
        //！！注意：此处是或"||"
        //若p空，stack不空说明走到某条右子树的尽头，但是还没有遍历完整个二叉树。
        //当p空并且stack空时才说明遍历完整个二叉树
    }


};

template <class Type> class MinimumHeap;
template <class Type>
class BinTreeNode{
    friend class BinTree<Type>;
    friend class MinimumHeap<Type>;
private:
    BinTreeNode *leftChild, *rightChild;
    BinTreeNode *parent;
    Type data;
    char c;

public:
    BinTreeNode():leftChild(nullptr), rightChild(nullptr),parent(nullptr),data(Type(0)),c('\0'){}
    BinTreeNode(char c ,Type data,BinTreeNode *leftChild= nullptr, BinTreeNode *rightChild= nullptr,BinTreeNode*parent= nullptr)
            :leftChild(leftChild), rightChild(rightChild),parent(parent), data(data),c(c) {}
    //setter
    void setLeft(BinTreeNode<Type> *L){ leftChild=L;}
    void setRight(BinTreeNode<Type> *R){ rightChild=R;}
    void setData(const Type& item){ data=item;}
    void setParent(BinTreeNode *parent) {
        BinTreeNode::parent = parent;
    }

    //getter
    BinTreeNode *GetLeftChild() const {
        return leftChild;
    }
    BinTreeNode *GetRightChild() const {
        return rightChild;
    }
    BinTreeNode *GetParent() const {
        return parent;
    }
    Type GetData() const {
        return data;
    }
    char GetC() const {
        return c;
    }

};


//extended binary tree
template <class Type>
class ExtBinTree:public BinTree<Type>{
public:
    //constructor
    ExtBinTree();
    ExtBinTree(BinTreeNode<Type> *root);
    ExtBinTree(ExtBinTree<Type>& T1,ExtBinTree<Type>& T2);
    //destructor
    //~ExtBinTree();
    //overloading the type operator---change the ExBinTree object to double (weight), in order to compare weight directly
    operator Type()const{ return this->GetRoot()->GetData();}

};

//construct a new extended binary tree from two existed extended binary trees
template<class Type>
ExtBinTree<Type>::ExtBinTree(ExtBinTree<Type> &T1, ExtBinTree<Type> &T2) {
    //new a root node
    this->root=new BinTreeNode<Type>();
    //set left、right、parent
    this->root->setLeft(T1.root);
    this->root->setRight(T2.root);
    this->root->setData(T1.root->GetData()+T2.root->GetData());
    T1.root->setParent(this->root);
    T2.root->setParent(this->root);
}

template<class Type>
ExtBinTree<Type>::ExtBinTree(BinTreeNode<Type> *root):BinTree<Type>(root) {}

template<class Type>
ExtBinTree<Type>::ExtBinTree() {}

/*
template<class Type>
ExtBinTree<Type>::~ExtBinTree() {
    //delete this->root;
}*/


#endif //DS_EX4_BINTREE_H
