#include <iostream>
#include "HuffTree.h"
using namespace std;

int main() {
    cout<<"Please enter the number of the weights/character that you need:"<<endl;
    int size;
    cin>>size;
    double * weights=new double[size];
    cout<<"Please enter "<<size<<" weights separated by white space:"<<endl;
    for (int i = 0; i <size ; ++i) {
        cin>>weights[i];
    }
    c=new char[size];
    cout<<"Please enter "<<size<<" characters separated by white space, whichi are corresponding to the above weights:"<<endl;
    for (int i = 0; i <size ; ++i) {
        cin>>c[i];
    }

    HuffmanCode(weights,size);


    delete []weights;
    delete []c;

    return 0;
}