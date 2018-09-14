//
// Created by yiner on 29/11/2017.
//

#ifndef DS_EX5_BTNODE_H
#define DS_EX5_BTNODE_H

#include <iostream>
#include "Stack.h"

template <class Type> struct BTNode{
    BTNode *left;
    Type data;
    BTNode *right;
    BTNode(Type x){
        data=x;
        left=right=NULL;
    }
};

template <class Type> class PostOrder;

template <class Type> class BinaryTree{
private:
    BTNode<Type> *root;
    friend class PostOrder<Type>;
public:
    BinaryTree(BTNode<Type>*t){root=t;}
};

//Base class for BT Iterator
template <class Type> class TreeIterator {
protected:
    const BinaryTree <Type> & T; //BT
    const BTNode<Type> *current;
public:
    TreeIterator ( const BinaryTree <Type> & BT )
            : T (BT), current (NULL) { }
    virtual ~TreeIterator ( ) { }
    virtual void First ( ) = 0;
    virtual void operator ++ ( ) = 0;
    operator bool(){return current!=NULL;}
    const Type operator()()const{
        if(current)
            return current->data;
        return (Type)0;
    }
};

template <class Type> struct StkNode {
//Stack node definition
    const BTNode <Type> *Node;  //Node Address
    int PopTime;                                        //Counter
    StkNode ( BTNode <Type> *N = NULL ) : Node (N), PopTime (0) { }
};

template <class Type> class PostOrder : public TreeIterator <Type> {
    bool renew;
public:
    PostOrder ( const BinaryTree <Type> & BT ):TreeIterator<Type>(BT){renew=false;}
    ~PostOrder ( ) { }
    void First ( );
    //Seek to the first node in postorder traversal
    void operator ++ ( );
    //Seek to the successor
protected:
    Stack < StkNode<Type> > st;     //Active record stack
};

template <class Type>
void PostOrder<Type>::First(){
    this->current = this->T.root;
    st.clear();
    renew=true;
    operator++();
}

template <class Type>
void PostOrder<Type>::operator ++(){
    if(!renew && this->current==this->T.root && st.isEmpty()){
        this->current=NULL;
        return;
    }
    renew = false;//renew仅用于++()函数开始跳过if判断
    const BTNode<Type> *p = this->current;
    StkNode<Type> w;
    do{
        //终止的判断条件
        if(w.PopTime==2){  //PopTime为2得到current的后继，更新current，return
            this->current=w.Node;
            return;
        }

        //开始的操作
        if (p==this->T.root){  //若为根结点，直接将根结点push入栈
            w.Node=p;
            st.push(w);
        }
        else if(p==this->current){ //若为除根结点之外的结点，刚进来直接pop栈顶元素
            w=st.pop();
            w.PopTime++;
            if(w.PopTime!=2)//若PopTime为2得到current的后继；若不为2，将其再次放入栈中
                st.push(w);
        }

        if (w.PopTime==0){  //PopTime为0，将左孩子压入栈，更新w和p
            if (w.Node->left!= nullptr){
                StkNode<Type> tmp(w.Node->left);
                st.push (tmp);
                w=tmp;
                p=tmp.Node;
            }
            else{   //左孩子为空，将栈顶元素(当前结点)出栈后入栈，更新w和p
                w=st.pop();
                w.PopTime++;
                p=w.Node;
                st.push(w);
            }

        }
        if (w.PopTime==1){  //PopTime为1，将右孩子压入栈，更新w和p

            if (w.Node->right!= nullptr){
                StkNode<Type> tmp(w.Node->right);
                st.push (tmp);
                w=tmp;
                p=tmp.Node;
            }
            else{     //右孩子为空，将栈顶元素(当前结点)出栈，更新w和p
                w=st.pop();
                w.PopTime++;
                p=w.Node;
            }
        }

    }
    while( p || !st.isEmpty( ));
}


#endif //DS_EX5_BTNODE_H

