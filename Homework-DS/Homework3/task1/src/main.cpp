#include <iostream>
#include "Stack.h"
using namespace std;

//思路：将入栈看为左子树，出栈看为右子树
void f(int seq[],int length,Stack<int> &stk){
    //入栈元素次序固定，用i记录目前轮到哪个元素入栈
    //j记录所有出栈的元素，方便打印
    //m记录刚出栈元素，方便回退
    static int i=0;
    static int j=0;
    static int m=0;

    //boundary condition 边界条件：未处理的元素为0
    if(i>=length){
        int tmp[length];
        //the size of the stack
        int stkSize=stk.GetSize();
        //保存现场
        for (int k = 0; k <stkSize ; ++k) {
            tmp[k]=stk.Pop();
            //print the output sequence
            cout<<tmp[k]<<" ";
        }
        cout<<endl;

        //恢复现场！
        for (int n =stkSize-1 ; n >=0 ; --n) {
            stk.Push(tmp[n]);
        }

        //end
        return;
    }

    //先访问左子树
    //push 入栈，若无未处理不能入栈且到边界条件
    stk.Push(seq[i++]);
    f(seq,length,stk);

    //退回当前节点
    stk.Pop();
    i--;


    static int tmp[4];
    static int pushBack[4];

    //再访问右子树
    //pop 出栈，栈内必须非空，若栈内是空的，不能出栈，直接不访问右子树，结束该次递归
    if (!stk.IsEmpty()){


        pushBack[m++]=tmp[j]=stk.Pop();

        for (int k = 0; k <=j; ++k) {
            cout<<tmp[k]<<" "<<flush;
        }

        j++;
        f(seq,length,stk);

        //退回当前节点
        stk.Push(pushBack[--m]);
        j--;
    }
}


int main() {
    int seq[4]={1,2,3,4};
    const int length= sizeof(seq)/ sizeof(seq[0]);
    Stack<int> stk;
    cout<<"There are 14 out sequences. "<<endl;
    cout<<"All the possibilities of the out sequence: "<<endl;
    f(seq,length,stk);
    return 0;
}