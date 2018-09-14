#include <iostream>
using std::cout;
using std::endl;
class String{
    static int nCharArray;//字符数组个数
    char* str;//字符数组
    size_t _len;//字符串长度，不包括末尾'\0'
public:
    String();//空串
    String(char *p);//已有字符串
    String(const String &s);//拷贝构造函数
    //运算符重载
    char& operator[](unsigned int idx);
    String& operator=(const String &s);
    //析构函数
    ~String();
    //返回从下标为1开始的字符串
    const char* c_str(){
        return str+1;
    }
};

int String::nCharArray;//类外需再声明一次，不加static；全局变量，初始化为0

//初始化操作
String::String(){
    str=NULL;
    _len=0;
    cout << "in constructor,nCharArray=" << nCharArray << endl;
}

//传入指向字符串的指针来构造字符数组
String::String(char *p){
    _len = strlen(p);
    str = new char[_len+1+1];
    strcpy(str+1,p);//从数组下标1开始
    str[0]=1;//新的字符数组第一位存入1（为引用计数）
    nCharArray++;
    cout << "in constructor,nCharArray=" << nCharArray << endl;
}

//拷贝构造函数，传入一个已存在的字符串的引用
String::String(const String &s){
    str = s.str;//让字符数组指针指向传入的字符串的首地址，即两个指针共用一个地址
    _len = s._len;//长度等于传入字符串长度
    str[0]++;//引用计数，指有多少个指向相同地址的指针（多少个一样的字符数组）
    cout << "in constructor,nCharArray=" << nCharArray << endl;
}

//重载[]，传递下标idx，经过该函数，指向同一地址（字符数组）的该指针指向新的地址
char& String::operator[](unsigned int idx){
    //检查下标是否越界，越界则什么都不做直接返回0
    if(idx<0 || idx>_len || str==NULL){
        static char nullchar = 0;
        return nullchar;
    }
    //如果引用指数大于1，有不止一个指针指向同一个地址
    if(str[0]>1){
        char *buf=new char[_len+1+1];
        strcpy(buf+1,str+1);//将字符串的内容拷贝到新的字符数组buf中
        str[0]--;//引用计数减1
        str=buf;//str指向字符数组buf
        str[0]=1;//让str（新的，即buf）引用计数为1
        nCharArray++;//数组个数加1
    }
    cout << "in oprator[],nCharArray=" << nCharArray << endl;
    return str[1+idx];//返回的是字符数组下标为idx+1的元素
}

//重载=，传入一个字符串引用，先做判断是否为空针，然后再让原来指针指向传入的引用地址，指向同一个字符数组
String& String::operator=(const String &s){
    //原来调用的指针若为空针
    if(!str){
        _len=s._len;
        str=s.str;//让原来指针指向传入的引用地址
        s.str[0]++;//引用计数加1
    }
    //若原来调用的指针不为空针
    else{
        str[0]--;//引用计数减1
        if(!str[0]){ //若引用计数为0，即上一步以前为1
            delete[] str;//删除原来指针指向的字符数组，释放内存
            nCharArray--;//字符数组个数减1
        }
        //让原来指针指向传入的引用地址，且引用计数加1
        _len=s._len;
        str=s.str;
        str[0]++;
    }
    cout << "in operator=,nCharArray=" << nCharArray << endl;
    return *this;
}

String::~String(){

    if(str){    //先判断是否为空针，为空针则直接打印后析构
        str[0]--;//若不为空针，引用计数减1
        if(!str[0]){//若此时引用计数为0，即上一步为1（只有一个指针指向该数组）
            delete[] str;//删除字符数组，释放内存
            nCharArray--;//字符数组个数减1
        }
    }
    cout << "in destructor,nCharArray=" << nCharArray << endl;
}


int main(){
    String s1;
    //调用构造函数1，创建并初始化对象s1，s1为空针，此时没有创建字符数组，字符数组个数nCharArray为0
    String s2="abc";
    //构造函数2，创建并初始化对象s2，s2指向字符串"1abc"，引用计数为1，字符数组个数nCharArray为1
    String s3=s2;
    //拷贝构造函数，使s3与现有对象s2指向，s3，s2均指向同一字符串"2abc"，引用计数为2，
    // 由于指向同一个字符数组，字符数组个数nCharArray为1
    s3[0]='p';
    //让s3指向新创建的字符数组（新地址），此时字符数组个数nCharArray为2，
    // 并改变字符串第一个值为p，故s3指向字符串"1pbc"，s2指向字符串"1abc"
    cout << s2.c_str() << endl;
    //从下标为1开始打印字符串，即"abc"
    cout << s3.c_str() << endl;
    //从下标为1开始打印字符串"pbc"
    s1=s3;
    //让s1指向s3指的字符串，引用计数加1，，s1，s3均指向字符串"2pbc"，
    // 由于没有创建新的字符数组，此时字符数组个数nCharArray仍为2
    s2=s3;
    //由于s2对应字符串引用计数为1，删除原来s2指向的字符数组，释放内存，
    // 让s2指向s3指的字符串，引用计数加1，s1，s2，s3均指向字符串"3pbc"，
    // 由于删除了一个字符数组且没有新建，故此时字符数组个数nCharArray为1
    cout << s1.c_str() << endl;
    //从下标为1开始打印字符串
    cout << s2.c_str() << endl;
    //从下标为1开始打印字符串
    //然后依次析构字符数组s3,s2,s1
    //引用计数减1，为2，析构s3
    //引用计数减1，为1，析构s2
    //引用计数减1，为0，删除字符数组，释放内存，故此时字符数组个数nCharArray为0，析构s1
}