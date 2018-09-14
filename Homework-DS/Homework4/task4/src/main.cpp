#include <iostream>
#include "LevelOrderIterator.h"
using namespace std;

//construct binary tree
void ConstructBT(string s, int size, BinTree<char> *tree) {
    //control index of char in the string
    int i = 0;
    //new the root node and the tree
    BinTreeNode<char> *root = new BinTreeNode<char>(s[i++]);
    tree->SetRoot(root);
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
                if (parent->GetLeft() == nullptr){
                    parent->SetLeft(p);
                    p->SetLevel(parent->GetLevel()+1);
                }
                else{
                    parent->SetRight(p);
                    p->SetLevel(parent->GetLevel()+1);
                }
                //char index increase
                i += 5;
                break;
            case 'L':
                p = new BinTreeNode<char>(s[i]);
                parent = &tree->Find(s[i + 2]);
                parent->SetLeft(p);
                p->SetLevel(parent->GetLevel()+1);
                //char index increase
                i += 6;
                break;
            case 'R':
                p = new BinTreeNode<char>(s[i]);
                parent = &tree->Find(s[i + 2]);
                parent->SetRight(p);
                p->SetLevel(parent->GetLevel()+1);
                //char index increase
                i += 6;
                break;
        }
    }
    
}

int main() {
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
    BinTree<char> *tree = new BinTree<char>();
    ConstructBT(s,size,tree);

    //print out the height of the tree
    int height=tree->Depth(tree->GetRoot());
    cout<<"Please enter the level i no more than the height "<<height<<" : "<<endl;
    int i;
    cin>>i;
    cout<<"The level order traversal sequence of the "<<i<<"th level of the tree is: "<<endl;
    LevelOrderIterator<char> iterator(*tree,tree->GetRoot());
    iterator.TraverseByLevel(i,height);

    //delete nodes
    iterator.Destroy(tree->GetRoot());

    //delete tree
    delete tree;

}