//
// Created by yiner on 14/12/2017.
//

#ifndef DS_EX6_FINAL_HUFFMANTREE_H
#define DS_EX6_FINAL_HUFFMANTREE_H

#include "BinTree.h"

char * c;

//minimun heap, its elements(nodes) are ExtBinTree.
template <class Type>
class MinimumHeap : public BinTree<Type>{
private:
    BinTreeNode<Type>* heapNode;
    int size;
public:
    //constructor---initialize the minimum heap with the extended trees
    MinimumHeap(Type *nodes,int size);
    ~MinimumHeap();
    void createHeap();
    void adjustDown(int r, int j);
    //more efficient way to this function
    void removeRoot(Type *first, Type *second);
    //more general way
   //void adjustUp(int j);
    void removeRoot(Type *node);
    void insertRoot(Type *node);
};

//new heap nodes
template<class Type>
MinimumHeap<Type>::MinimumHeap(Type *nodes, int size) {
    heapNode=new BinTreeNode<Type>[size];
    this->size=size;
    for (int i = 0; i <size ; ++i) {
        heapNode[i].setData(nodes[i]);
        if (2*i+1<size)
            heapNode[i].setLeft(&heapNode[2*i+1]);
        if (2*i+2<size)
            heapNode[i].setRight(&heapNode[2*i+2]);
    }
}

//delete heap nodes
template<class Type>
MinimumHeap<Type>::~MinimumHeap() {
    delete []heapNode;
}

//create minimum heap
template<class Type>
void MinimumHeap<Type>::createHeap() {
    //adjust down from the last no-leaf node to the root
    for (int i = (size-2)/2; i>-1 ; --i) {
        adjustDown(i,size-1);
    }
}

//!!key function
//adjust down the r-th node
//from the r+1-th node to the j-th node(the last node), they already met the minimum heap condition---each node is smaller than its 2 child nodes
template<class Type>
void MinimumHeap<Type>::adjustDown(int r,int j) {
    //left child
    int child=2*r+1;
    BinTreeNode<Type> tmp=heapNode[r];
    //compare the r-th node(tmp) with its child nodes first, maybe even its descendant nodes
    //terminal condition: has no more child nodes-------left child<=j

    //start loop
    while (child<=j){

        //compare with both left and right child
        //if right child is the smallest, switch to the right child
        if(child+1<=j){
            if(heapNode[child].GetData()>heapNode[child+1].GetData()) child++;
        }
        //terminal condition: the tmp is smaller than its specific child
        if (tmp.GetData()<heapNode[child].GetData()) break;
        //if not, switch to the specific child's child node
        //tmp is bigger than its specific child, then swap them
        heapNode[(child-1)/2].setData(heapNode[child].GetData());
        //update next child node index
        child=2*child+1;
    }
    //since terminate because the tmp is smaller than its specific child, then assign the specific child's parent node with tmp
    heapNode[(child-1)/2].setData(tmp.GetData());

}

//Assign the root to the node(first/second) and remove the root from the heap
template<class Type>
void MinimumHeap<Type>::removeRoot(Type *node) {
    //1.get root and assign it to node
    *node=heapNode[0].GetData();

    //2.delete the previous node by cover it with the last(size-1-th) nodes and then size--
    heapNode[0]=heapNode[--size];

    //3.adjust down
    adjustDown(0,size-1);

}

//Assign the root with the node(newTree)
template<class Type>
void MinimumHeap<Type>::insertRoot(Type *node) {
    //1. assign the root with node
    heapNode[0].setData(*node);

    //2.adjust down
    adjustDown(0,size-1);
}

template<class Type>
void MinimumHeap<Type>::removeRoot(Type *first, Type *second) {

    //1.get root and assign it to first
    *first=heapNode[0].GetData();

    //2.delete the previous node by cover it with the last(size-1-th) nodes and then size--
    heapNode[0].setData(heapNode[--size].GetData());

    //3.adjust down
    adjustDown(0,size-1);

    //4.get root and assign it to second
    *second=heapNode[0].GetData();


}







//key function
void HuffmanCode(double* weights, int size){

    //initalize n huffman trees with only the root nodes and specific weights
    ExtBinTree<double>* nodes=new ExtBinTree<double>[size];
    for (int i = 0; i <size ; ++i) {
        nodes[i].SetRoot(new BinTreeNode<double>(c[i],weights[i]));
    }

    //declare minimum heap and two operated extended binary trees
    //add the trees to the minimum heap
    MinimumHeap<ExtBinTree<double>>heap(nodes,size);
    ExtBinTree<double> *first, *second;
    ExtBinTree<double>* newTree;

    double *w=new double[size];
    for(int i=0;i<size;i++){
        w[i]=weights[i];
    }

    char * ch=new char[size];
    for (int i1 = 0; i1 <size ; ++i1) {
        ch[i1]=c[i1];
    }


    //create heap
    heap.createHeap();

    //start loop:
    //since one binary tree will leave in the heap at last, terminal condition is j=size-1
    for (int j = 0; j <size-1 ; ++j) {

        //select and delete the minimum two trees (weight) from  the heap
        heap.removeRoot(first,second);

        //create new trees from the two selected trees
        newTree=new ExtBinTree<double>(*first,*second);
        //add the new trees to the heap
        heap.insertRoot(newTree);

    }

    //get required huffman tree

    heap.removeRoot(newTree);
    //get height----longest path/code length
    int codeLength=newTree->height(newTree->GetRoot());

    char**hcodes;

    hcodes=new char*[size];
    for (int m = 0; m <size ; ++m) {
        hcodes[m]=new char[codeLength];
    }



    //traversal the huffman tree and encoding
    BinTreeNode<double>* childNode;
    BinTreeNode<double>* parentNode;
    for (int n = 0; n <size ; ++n) {
        childNode=newTree->find(ch[n],w[n]);
        parentNode=childNode->GetParent();
        int i=0;
        for (; i <codeLength&&parentNode!= nullptr ; ++i) {
            if (childNode==parentNode->GetLeftChild())
                hcodes[n][i]='0';
            else
                hcodes[n][i]='1';

            childNode=parentNode;
            parentNode=parentNode->GetParent();

        }
        hcodes[n][i]='\0';

    }

    //output the huffman tree
    for (int k = 0; k <size ; ++k) {
        cout<<ch[k]<<" : ";
        cout<<"weight "<<w[k]<<" code ";
        //'\0' means the code is ending
        //code is read from the last to the first
        int i=codeLength-1;
        while (hcodes[k][i]=='\0')
            i--;
        for (int j = i; j >-1; --j) {
            char a=hcodes[k][j];
            /*printf("%c",a);*/
            cout<<a;
        }
        printf("\n");

    }

    //end

    //delete hcodes[m]
    for (int m = 0; m <size ; ++m) {
        delete hcodes[m];
    }

    //delete hcodes
    delete hcodes;

    //delete EXtBinTree nodes
    newTree->breakTree(newTree->GetRoot());
    //delete EXtBinTree trees
    heap.breakTree(heap.GetRoot());

    //delete w、ch
    delete[] w;

    delete[] ch;


}




#endif //DS_EX6_FINAL_HUFFMANTREE_H
