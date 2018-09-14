//
// Created by yiner on 19/10/2017.
//
#include <iostream>
#include <string>
using namespace std;

#include "Polynomial.h"

void Polynomial::inputPoly() {
    //display guidance statement
    cout<<"Please input a polynomial like this \"x^3+1-2x^2+3x^(-5)+2x\", and press Enter to end your input."<<endl;
    cout<<"The coefficient and the exponent can only be integer numbers from -9 to 9. "<<endl;
    cout<<"Input a polynomial: "<<endl;

    //get input
    char raw[30];
    //initial raw to null string
    for (int n = 0; n <30 ; ++n) {
        raw[n]='\0';
    }
    cin.getline(raw,30);

    //analyse input string and store them into corresponding items
    for (int i = 0; i < 30; ) {
        //add to the term list
        int termNumber=0;
        int termCoef=0;
        int termExp=0;
        //1.store coef

        //a.when occur '+',move to the next item to store coef
        if(raw[i]=='+') {
            //'+x'means the coef =1
            if (raw[i+1]=='x'){
                termCoef=1;
                if(raw[i+2]=='\0') insertTerm(1,1,termNumber);
                i++;
            }
            else{
                i++;
                termCoef=raw[i]-'0';
                i++;
            }


        }
        //b.when occur '-',move to the next item to store coef of the opposite number
        else if(raw[i]=='-'){
            //'-x'means the coef =-1
            if (raw[i+1]=='x'){
                termCoef=-1;
                if(raw[i+2]=='\0') insertTerm(1,1,termNumber);
                i++;
            }
            else{
                i++;
                int temp;
                temp=raw[i]-'0';
                termCoef=-temp;
                i++;
            }

        }
        //c.the first char is 'x',means the coef=1
        else if(i==0&&raw[i]=='x') {
            termCoef=1;
            if(raw[i+1]=='\0') {
                insertTerm(1,1,termNumber);
                break;
            }

        }
        //d.simply store number
        else{
            termCoef=raw[i]-'0';
            i++;
        }

        //2.store exp

        if(raw[i]=='x') {
            //the last char is 'x', means exp=1
            if(raw[i+1]=='\0'){
                termExp=1;
                i++;
                insertTerm(termCoef,termExp,termNumber);
                termNumber++;
                break;
            }

            i++;
            //a.when occur '^',skip to scan next char
            if(raw[i]=='^') {
                i++;
                //when occur '(', move to the next item to judge if exist a '-'
                //if exist a '-',move to the next item to store exp of the opposite number
                if(raw[i]=='('){
                    if(raw[++i]=='-'){
                        i++;
                        int temp;
                        temp=raw[i]-'0';
                        termExp=-temp;
                        i++;
                        insertTerm(termCoef,termExp,termNumber);
                        termNumber++;
                        //when occur ')',skip
                        if(raw[i]==')') i++;
                    }
                }
                //store positive exp
                else{
                    termExp=raw[i]-'0';
                    i++;
                    insertTerm(termCoef,termExp,termNumber);
                    termNumber++;
                }
            }
            //b.if directly occur '+' or '-', means the exp is 1
            else if (raw[i]=='+'||raw[i]=='-'){
                termExp=1;
                i++;
                insertTerm(termCoef,termExp,termNumber);
                termNumber++;
            }
        }
        else {
            insertTerm(termCoef,termExp,termNumber);
            termNumber++;
        }

        //end the loop
        if(raw[i]=='\0') {
            break;
        }

    }

}


void Polynomial::outputPoly() {
    sort();
    for (int j=0; j < getLength(); j++ ) {

        if(j>0&&findTerm(j)->coef>0){
            cout<<'+';
        }
        cout<<findTerm(j)->coef;
        if(findTerm(j)->exp==0) continue;
        cout<<'x';
        cout<<'^';
        if(findTerm(j)->exp<0)
        {
            cout<<'(';
            cout<<findTerm(j)->exp;
            cout<<')';
        }
        else cout<<findTerm(j)->exp;

    }

    cout<<endl;


}


Polynomial Polynomial::operator*(const Polynomial & bh) {
    Polynomial ch;
    int termNumber=0;
    int termCoef=0;
    int termExp=0;
    for (int i = 0; i < getLength(); ++i) {
        for (int j = 0; j <bh.getLength(); ++j) {
            //coef multiplication

            termCoef= this->findTerm(i)->coef * bh.findTerm(j)->coef;

            //exp multiplication
            termExp= this->findTerm(i)->exp + bh.findTerm(j)->exp;

            ch.insertTerm(termCoef,termExp,termNumber);
            termNumber++;
        }
    }

    ch.merge();

    ch.sort();

    return ch;
}


Polynomial& Polynomial::operator=(const Polynomial &ch) {
    int termNumber=0;
    int termCoef=0;
    int termExp=0;
    for (int i = 0; i <ch.getLength() ; ++i) {
        //coef assign

        termCoef= ch.findTerm(i)->coef;

        //exp assign
        termExp= ch.findTerm(i)->exp;

        this->insertTerm(termCoef,termExp,termNumber);
        termNumber++;
    }
    return *this;
}

//sort the Polynomial in ascending order
void Polynomial::sort() {
    for (int j=0;j<getLength()-1;j++) {
        for (int i=0;i<getLength()-1-j;i++){
            if(findTerm(i)->exp >= findTerm(i+1)->exp){
                int temp;
                //change exp
                temp=findTerm(i)->exp;
                findTerm(i)->exp=findTerm(i+1)->exp;
                findTerm(i+1)->exp=temp;
                //change coef
                temp=findTerm(i)->coef;
                findTerm(i)->coef=findTerm(i+1)->coef;
                findTerm(i+1)->coef=temp;
            }

        }
    }

}


//merge the term that has the same exponent
void Polynomial::merge() {
    for (int i = 0; i <getLength() ; ++i) {
        for (int j = 0; j <getLength() ; ++j) {
            //compare each term's exponent
            if (i==j) continue;
            //if euqal, add exp to the i-th term
            if (findTerm(i)->exp==findTerm(j)->exp){
                findTerm(i)->coef+=findTerm(j)->coef;
                removeTerm(j);
                j--;
            }
        }
    }

}



//functions to manipulate linked term list

Polynomial::Polynomial(){
    first = new Term();
}

Polynomial::~Polynomial() {
    makeEmpty();
    delete first;
}

//make the term list empty
void Polynomial::makeEmpty() {
    //delete the term that after the term 'first' pointed to
    Term* temp;
    while (first->link!= nullptr){
        temp=first->link;
        first->link=temp->link;
        delete temp;
    }

}

//get the length of the term list (the number of the terms)
//length i represents the last term of the list is the (i-1)th
int Polynomial::getLength() const {
    int count=0;
    Term* p=first->link;
    while (p!= nullptr){
        p=p->link;
        count++;
    }
    return count;
}

//find out the i-th term, and return it's address
//Notice: the dummy term is the -1th,the real first term is the 0th
Term *Polynomial::findTerm (int i) const {
    if (i<-1) return nullptr;
    if (i==-1) return first;
    Term* p=first->link;
    int j=0;
    while (p!= nullptr&&j<i){
        p=p->link;
        j++;
    }
    return p;
}


//insert a new term after the (i-1)th term in the term list,then the new term is the i-th term
// when succeed return true, while fail return false
//Notice: the dummy term is the -1th,the real first term is the 0th
bool Polynomial::insertTerm(int coef, int exp, int i) {
    Term* p = findTerm(i-1);
    if(p==nullptr) return false;
    Term* newnode = Term::newTerm(coef, exp,p->link);
    p->link=newnode;
    return true;
}


//remove the i-th term in the term list
// when succeed return true, while fail return false
//Notice: the dummy term is the -1th,the real first term is the 0th
bool Polynomial::removeTerm(int i) {
    Term* p = findTerm(i-1),*q;
    if (p== nullptr||p->link== nullptr) return 0;
    q=p->link;
    p->link=q->link;
    delete q;
}






