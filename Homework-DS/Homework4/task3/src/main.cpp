#include <iostream>
#include "BinTree.h"
using namespace std;

int main() {
    cout<<"Please enter an array, and the application will turn it into a complete binary tree stored in a doubly-linked list."<<endl;
    cout<<"Please enter the length of the array: "<<endl;
    int length;
    cin>>length;
    BinTreeNode<char> * arr = new BinTreeNode<char> [length];
    cout<<"Please enter all the elements(char) of array,like this:\"a b 3 4 c\": "<<endl;
    for (int i = 0; i <length ; ++i) {
        char s;
        cin>>s;
        arr[i].setData(s);
    }
    for (int j = 0; j <length ; ++j) {
        if(2*j+1<length) arr[j].setLeft(&arr[2*j+1]);
        if(2*j+2<length) arr[j].setRight(&arr[2*j+2]);
    }
    BinTree<char> tree(&arr[0]);
    cout<<"The inorder traversal sequence of the complete binary tree is: "<<endl;
    tree.InOrderTraverse();
}