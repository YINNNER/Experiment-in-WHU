#include <iostream>
#include "BTNode.h"

int main() {
    BTNode<int> *p = new BTNode<int>(6);
    p->left = new BTNode<int>(4);
    p->right = new BTNode<int>(10);
    p->left->left = new BTNode<int>(2);
    p->right->left = new BTNode<int>(8);
    p->right->right = new BTNode<int>(12);
    BinaryTree<int> T(p);
    PostOrder<int> it(T);
    for(it.First();it;++it){
        std::cout << it() << std::endl;
    }
}