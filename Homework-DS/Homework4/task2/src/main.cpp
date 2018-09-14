#include <iostream>
#include "BinTree.h"
#include "LevelOrderIterator.h"

using namespace std;

//construct binary tree
void ConstructBT(string s, int size) {
    //control index of char in the string
    int i = 0;
    //new the root node and the tree
    BinTreeNode<char> *root = new BinTreeNode<char>(s[i++]);
    BinTree<char> *tree = new BinTree<char>(root);
    //char index increase
    i++;
    //declare the operated node's pointer and its parent's pointer
    BinTreeNode<char> *p;
    BinTreeNode<char> *parent;
    //traverse string s
    while (i + 3 < size) {
        //judge 3 cases
        switch (s[i + 3]) {
            case ')':
                p = new BinTreeNode<char>(s[i]);
                parent = &tree->Find(s[i + 2]);
                if (parent->GetLeftChild() == nullptr)
                    parent->SetLeft(p);
                else
                    parent->SetRight(p);
                //char index increase
                i += 5;
                break;
            case 'L':
                p = new BinTreeNode<char>(s[i]);
                parent = &tree->Find(s[i + 2]);
                parent->SetLeft(p);
                //char index increase
                i += 6;
                break;
            case 'R':
                p = new BinTreeNode<char>(s[i]);
                parent = &tree->Find(s[i + 2]);
                parent->SetRight(p);
                //char index increase
                i += 6;
                break;
        }
    }

    //traverse the tree and print all the nodes out
    cout << "The inorder traversal of the binary tree is: " << endl;
    tree->InOrderTraverse();

    //delete nodes
    LevelOrderIterator<char> iterator(*tree, root);
    iterator.Destroy(root);

    //delete tree
    delete tree;

}

int main() {
    //prompt
    cout << "Please enter a sequence of level order, with the parent node of each element." << endl;
    cout << "For example, the sequence: A B(A) C(A) D(BR) E(C) F(C) G(E) H(E)" << endl;
    cout << "D(BR) means that D is the mere right child of B." << endl;
    cout << "Enter here:";
    cout.flush();
    //The input string
    string s;
    getline(cin, s);
    //The size of the input string
    int size = s.size();

    //Construct binary tree
    ConstructBT(s, size);

    return 0;
}