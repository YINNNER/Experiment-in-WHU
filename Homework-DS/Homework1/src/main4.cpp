#include <iostream>
using namespace std;

//(4)
class test{
public:
    test(int t);
    ~test();
private:    
	int count;

};

test::test(int t) {
	count=t;
    cout<<"Call constructor "<<count<<endl;
}

test::~test() {
    cout<<"Call destructor "<<count<<endl;
}

test t1=test(1);

test t2=test(2);

int main(){
     //(4)
    
    cout<<"start main function"<<endl;
    test t3=test(3);
    test t4=test(4);

}