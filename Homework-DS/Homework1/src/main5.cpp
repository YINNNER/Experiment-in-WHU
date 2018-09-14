#include <iostream>
using namespace std;

//(5)
bool checkNone(int arr[],int n){
    for (int i = 0; i < n ; ++i) {
        if(arr[i]==1) return false;
    }
    cout<<"Nobody is in the ring now."<<endl;
    return true;
}

int del(int arr[], int r, int n){
    int count=1;
    int index=0;
    while(index<n&&r>0)
    {
        if(arr[index]){
            if(count==r)
            {
                arr[index]=0;
                cout<<"The "<<index+1<<"th (original number) person leave the ring."<<endl;
                if(checkNone(arr,n)) break;

            }
            count++;
        }
        else ;
        index++;
        if(index==n) index=0;
        if(count>r) count=1;
    }

    return 0;
}


int main(){
     //(5)
    const int n=6;
    int arr[n];
    for (int i = 0; i <n ; ++i) {
        arr[i]=1;
    }
    int r=5;
    del(arr,r,n);

}