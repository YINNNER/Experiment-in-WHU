#include <iostream>
using namespace std;

//n在用户输入之后就是一个常数，不再改变它的值
static int n=0;
void f(int i, int* output,int* index);
bool ArrFull(int* output);
void InitalArr(int *arr,int length);

int main() {
    cout << "Please enter a integer no less than 3:" <<endl;
    cin>>n;
    cout << "All the possibilities sequences are:" <<endl;
    //打印用的数组
    int * output= new int [2*n];
    //记录每个数字插入的位置的数组,数字i插入的位置存放在index[i-1]中
    int * index=new int [n];
    //初始化数组
    InitalArr(output,2*n);
    InitalArr(index,n);
    //将1到n均在数组首位的情况都尝试一遍
    for (int i = n; i >0 ; --i) {
        //1.将i插入数组首位和另一个对应位置
        output[index[i-1]]=i;
        output[index[i-1]+i+1]=i;

        //2.插入剩下的2(n-1)个数字
        f(i-1, output, index);

        //3.还原数组
        InitalArr(index,n);
        InitalArr(output,2*n);
    }
    delete []index;
    delete []output;
    return 0;
}

/*!
 * 实现功能的主函数
 * @param i 现在操作的数字
 * @param output 用与插入及打印的数组
 * @param index 记录每个数字插入的位置的数组,数字i插入的位置存放在index[i-1]中
 */
void f(int i, int* output,int* index) {

    //由于j会变化，用一个临时但是不会变的值来记录插入时的位置
    static int tmp=0;
    //从非n的数开始要倒回来访问n
    if (0==i)i=n;

    //边界条件
    //成功则打印，返回上一层尝试其他情况
    if (ArrFull(output)){
        for (int k = 0; k <2*n ; ++k) {
            cout<<output[k]<<" ";
        }
        cout<<endl;
        //成功后也要恢复上一个数插入前的状态才回退到上一个函数
        //从n退回1要注意变化回去
        if (i==n) i=0;
        output[index[(i+1)-1]]=0;
        output[index[(i+1)-1]+(i+1)+1]=0;
        return;
    }

    //key step
    //遍历数组并插入
    for (int j = 1; j <=2*n-(i+2) ; ++j) {
        //判断能否插入：如果该位置和另一个对应位置已有数字，就跳过这个位置
        if ((0!=output[j])||(0!=output[j+i+1])) continue;
        //可以插入，则插入
        output[j]=i;
        output[j+i+1]=i;
        //记录插入的位置
        tmp=j;
        index[i-1]=tmp;
        //开始递归，插入下一个数
        f(i-1,output,index);
    }
    //遍历所有情况后失败，则要恢复上一个数---(i+1) 插入前的状态才回退到上一个函数
    //从n退回1要注意变化回去
    if (i==n) i=0;
    output[index[(i+1)-1]]=0;
    output[index[(i+1)-1]+(i+1)+1]=0;
}

/*!
 * 判断数组是否已满
 * @param output
 * @return
 */
bool ArrFull(int *output) {

    for (int i = 0; i <2*n ; ++i) {
        if (*output==0) return false;
        output++;
    }
    return true;
}

/*!
 * 用0初始化数组所有元素
 * @param arr
 */
void InitalArr(int *arr,int length) {
    for (int j = 0; j <length; ++j) {
        arr[j]=0;
    }
}

