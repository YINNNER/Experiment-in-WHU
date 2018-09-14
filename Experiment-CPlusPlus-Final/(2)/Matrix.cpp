#include <iostream>
using namespace std;

double **Matrix;

int n;

double **allocMatrix(int n){

    Matrix = new double * [n];

    for(int i = 0; i < n; i++){

        if((Matrix[i]=new double [n])==NULL)

            exit(0);
    }

    cout<<"Enter " <<n*n<< " numbers: "<<endl;

    for (int i = 0; i < n; ++i) {

        for (int j = 0; j < n; ++j)

            cin>>Matrix[i][j];
    }

    cout<<"The matrix is: "<<endl;

    for (int i = 0; i < n; ++i) {

        for (int j = 0; j < n; ++j)

            cout<<Matrix[i][j]<<"\t";

        cout<<endl;
    }

    return Matrix;
}


void releaseMatrix(double **m){

    for (int i = 0; i < n; ++i)

        delete [] m[i];

    delete [] m;

    cout<<"The matrix has been deleted!"<<endl;

}

int main(){

    double **m;

    cout<<"Input matrix size n:"<<endl;

    cin>>n;

    m=allocMatrix(n);

    releaseMatrix(m);

    return 0;
}