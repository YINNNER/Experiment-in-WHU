#include <iostream>
using namespace std;

//(3)
void sort(int &i,int &j,int &k){
    if(i>j){
        int tmp=j;
        j=i;
        i=tmp;
        if(j>k){
            tmp=k;
            k=j;
            j=tmp;
        }
        if(i>j){
            int tmp=j;
            j=i;
            i=tmp;
        }
    }
    else{
        int tmp;
        if(j>k){
            tmp=k;
            k=j;
            j=tmp;
        }
        if(j<i){
            tmp=j;
            j=i;
            i=tmp;
        }

    }

}

int main(){
    //(3)
    
    int i=5;
    int j=2;
    int k=1;
    sort(i,j,k);
    cout<<i<<" "<<j<<" "<<k<<endl;
}