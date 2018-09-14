#include <iostream>
#include "BinTree.h"
using namespace std;

int main() {
    const int size=14;
    BinTreeNode<int> arr[size];
    cout<<"A sequence will be stored in a binary tree: "<<endl;
    for (int i = 0; i <size ; ++i) {
        cout<<3*i<<" ";
        arr[i].setData(3*i);
        if(2*i+1<size) arr[i].setLeft(&arr[2*i+1]);
        if(2*i+2<size) arr[i].setRight(&arr[2*i+2]);
    }
    cout<<endl;
    BinTree<int> tree(&arr[0]);
    cout<<"The inorder traversal sequence is: "<<endl;
    tree.InOrderTraverse();
}